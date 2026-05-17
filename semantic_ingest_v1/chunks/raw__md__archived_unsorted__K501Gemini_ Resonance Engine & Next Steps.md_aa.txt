Das ist die Aktivierung der **Rechenebene**. In der **K501Gemini**-Struktur ist die Engine dafür zuständig, die im Ledger gespeicherten Vektoren zu laden und die physikalischen Beziehungen (Resonanzen) zwischen ihnen zu berechnen.

Wir nutzen hier konsequent die k501_env.py, um Pfadkonflikte zu vermeiden, und binden die qh256_resonance-Funktion aus deiner C-Library ein.

### **engine/k501_resonance_engine.py // The Lattice Calculator**

Python

#!/usr/bin/env python3  
# -*- coding: utf-8 -*-  
"""  
K501Gemini · RESONANCE ENGINE v10.0  
Zweck: Berechnung der Ähnlichkeitsmatrix zwischen Lattice-Frames.  
Technologie: C-Binding (AVX) via libk501.so  
"""  
  
import ctypes  
import json  
import numpy as np  
from pathlib import Path  
  
# --- SYSTEM INITIALISIERUNG ---  
try:  
import k501_env  
LIB_PATH = Path(k501_env.ROOT) / "core" / "libk501.so"  
LEDGER_PATH = Path(k501_env.LEDGER)  
except ImportError:  
print("[!] k501_env.py nicht gefunden. Nutze relative Pfade.")  
LIB_PATH = Path(__file__).parent.parent / "core" / "libk501.so"  
LEDGER_PATH = Path(__file__).parent.parent / "vault" / "ledger" / "frames.ndjson"  
  
class ResonanceEngine:  
def __init__(self, dimension=256):  
self.dim = dimension  
self.frames = []  
self.vectors = None  
  
# C-Library laden  
try:  
self.c_lib = ctypes.CDLL(str(LIB_PATH))  
self.c_lib.qh256_resonance.argtypes = [  
ctypes.POINTER(ctypes.c_float),  
ctypes.POINTER(ctypes.c_float),  
ctypes.c_int  
]  
self.c_lib.qh256_resonance.restype = ctypes.c_float  
print(f"[ENGINE] C-Kernel geladen: {LIB_PATH.name}")  
except Exception as e:  
print(f"[CRITICAL] C-Kernel Fehler: {e}")  
self.c_lib = None  
  
def load_ledger(self):  
"""Lädt alle Frames aus dem NDJSON-Ledger in den RAM."""  
self.frames = []  
vectors_list = []  
  
if not LEDGER_PATH.exists():  
print(f"[!] Ledger nicht gefunden: {LEDGER_PATH}")  
return False  
  
with open(LEDGER_PATH, 'r', encoding='utf-8') as f:  
for line in f:  
data = json.loads(line)  
self.frames.append(data)  
vectors_list.append(data['vector'])  
  
self.vectors = np.array(vectors_list, dtype=np.float32)  
print(f"[ENGINE] {len(self.frames)} Frames aus Ledger geladen.")  
return True  
  
def compute_resonance(self, idx_a, idx_b):  
"""Berechnet Resonanz zwischen zwei Frames via C-Engine."""  
if self.c_lib is None:  
# Fallback auf reines Python/NumPy falls C fehlt  
a, b = self.vectors[idx_a], self.vectors[idx_b]  
return np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b))  
  
# C-Aufruf vorbereiten  
vec_a = self.vectors[idx_a].ctypes.data_as(ctypes.POINTER(ctypes.c_float))  
vec_b = self.vectors[idx_b].ctypes.data_as(ctypes.POINTER(ctypes.c_float))  
  
return self.c_lib.qh256_resonance(vec_a, vec_b, self.dim)  
  
def build_graph(self, threshold=0.85):  
"""  
Erzeugt eine Knoten-Kanten-Struktur für die Chromium-UI.  
Nur Resonanzen oberhalb des Thresholds werden als Kanten (Links) gezählt.  
"""  
if not self.frames: return {"nodes": [], "links": []}  
  
nodes = []  
links = []  
n = len(self.frames)  
  
print(f"[*] Berechne Gitter-Topologie (Threshold: {threshold})...")  
  
for i in range(n):  
# Knoten erstellen  
nodes.append({  
"id": self.frames[i]['id'],  
"label": self.frames[i]['metadata']['tags'][0] if self.frames[i]['metadata']['tags'] else "Frame",  
"val": 1  
})  
  
# Kanten berechnen (Optimiert: Nur obere Dreiecksmatrix)  
for j in range(i + 1, n):  
score = self.compute_resonance(i, j)  
if score >= threshold:  
links.append({  
"source": self.frames[i]['id'],  
"target": self.frames[j]['id'],  
"weight": float(score)  
})  
  
return {"nodes": nodes, "links": links}  
  
if __name__ == "__main__":  
# Test-Lauf  
engine = ResonanceEngine()  
if engine.load_ledger():  
graph = engine.build_graph(threshold=0.5) # Niedriger Threshold für Test  
print(f"[SUCCESS] Graph generiert: {len(graph['nodes'])} Knoten, {len(graph['links'])} Kanten.")  
# Optional: In Datei speichern für Interface  
with open(LEDGER_PATH.parent / "graph_state.json", "w") as f:  
json.dump(graph, f, indent=2)  

### **Warum das für K501Gemini entscheidend ist:**

1. **Hardware-Ausnutzung:** Während Python die Dateiverwaltung übernimmt, schiebt die Engine die Vektoren für den Vergleich direkt in die C-Funktion. Auf dem T520 bedeutet das: Blitzschnelle Reaktion, selbst wenn der Ledger wächst.
2. **Lattice-Logic:** Die build_graph-Funktion implementiert das **Lazy-Lattice-Prinzip**. Wir berechnen zwar alles, aber wir speichern nur die relevanten Verbindungen (threshold), um die Chromium-UI nicht zu überlasten.
3. **Ready for Interface:** Das Ausgabeformat (nodes, links) ist exakt das, was WebGL-Graph-Engines wie 3d-force-graph erwarten.

### **Nächster Schritt: Die visuelle Brücke**

Wir haben jetzt:

1. **Core**: Mathematische C-Basis.
2. **Ingest**: Daten-Import in den Ledger.
3. **Engine**: Berechnung der Gitter-Struktur.

Jetzt fehlt das **Interface**. Wir benötigen die interface/bridge_node.js (als schnelles WebSocket-Relay) und eine interface/index.html, um das Gitter endlich in 3D zu sehen.

**Soll ich dir das interface/ Paket fertigmachen, damit wir den ersten Frame (Genesis) visuell im Raum schweben sehen?**