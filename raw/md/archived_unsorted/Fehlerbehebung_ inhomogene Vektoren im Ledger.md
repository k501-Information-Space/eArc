Der Fehler ValueError: setting an array element with a sequence deutet darauf hin, dass mindestens einer der 1.355 Frames keinen Vektor mit exakt 32 Elementen hat oder die Datenstruktur korrumpiert ist. Das passiert oft, wenn beim Ingest etwas schiefgelaufen ist oder leere Zeilen im Ledger stehen.

Wir härten jetzt die **engine/k501_resonance_engine.py**, damit sie inhomogene Vektoren erkennt, aussortiert und den Prozess nicht abbricht.

### **Engine Evolution v10.3 (Robust Load & Shape-Check)**

Diese Version prüft jeden Vektor einzeln auf die Länge von 32 (256-Bit) und ignoriert beschädigte Frames.

**File: engine/k501_resonance_engine.py**

Python

import ctypes  
import json  
import numpy as np  
import sys  
from pathlib import Path  
  
# Root-Kopplung  
sys.path.append(str(Path(__file__).parent.parent))  
from k501_env import LIB_K501, LEDGER, ROOT  
  
class ICEResonanceEngine:  
def __init__(self):  
try:  
self.c_lib = ctypes.CDLL(str(LIB_K501))  
except Exception as e:  
print(f"[CRITICAL] C-Library nicht ladbar: {e}")  
sys.exit(1)  
self.frames = []  
self.vectors = None  
  
def load(self):  
if not LEDGER.exists():  
print("[ERROR] Ledger nicht gefunden.")  
return  
  
self.frames = []  
valid_vectors = []  
line_count = 0  
  
print(f"[*] Lade Ledger: {LEDGER}")  
with open(LEDGER, 'r', encoding='utf-8') as f:  
for line in f:  
line_count += 1  
try:  
data = json.loads(line)  
vec = data.get('vector')  
  
# VALIDIERUNG: Muss eine Liste von genau 32 Floats sein  
if isinstance(vec, list) and len(vec) == 32:  
self.frames.append(data)  
valid_vectors.append(vec)  
else:  
print(f" [!] Zeile {line_count} ignoriert: Inhomogener Vektor (Len: {len(vec) if vec else 0})")  
except Exception:  
continue  
  
if valid_vectors:  
self.vectors = np.array(valid_vectors, dtype=np.float32)  
print(f"[ENGINE] {len(self.frames)} valide Frames geladen (von {line_count} total).")  
else:  
print("[ERROR] Keine validen Frames gefunden.")  
  
def compute_lattice(self, threshold=0.92):  
if self.vectors is None or len(self.vectors) == 0:  
print("[ERROR] Kein Vektor-Pool vorhanden.")  
return  
  
n = len(self.vectors)  
nodes = []  
for f in self.frames:  
nodes.append({  
"id": f['id'],  
"label": f['metadata'].get('file_path', f['id'][:12]),  
"origin": f['metadata'].get('origin', 'unknown'),  
"size": f['metadata'].get('size_bytes', 1000),  
"content": f['payload'][:1000]  
})  
  
links = []  
print(f"[*] Starte Massen-Resonanz ({n} Nodes) via AVX Batch...")  
  
# Buffer für C-Resultate  
results_buf = np.zeros(n, dtype=np.float32)  
  
for i in range(n):  
target = self.vectors[i].ctypes.data_as(ctypes.POINTER(ctypes.c_float))  
pool = self.vectors.ctypes.data_as(ctypes.POINTER(ctypes.c_float))  
  
# Aufruf der Batch-Funktion  
self.c_lib.qh256_batch_resonance(target, pool, results_buf.ctypes.data_as(ctypes.POINTER(ctypes.c_float)), n)  
  
# Nur obere Dreiecksmatrix für Effizienz  
for j in range(i + 1, n):  
score = results_buf[j]  
if score >= threshold:  
links.append({  
"source": nodes[i]['id'],  
"target": nodes[j]['id'],  
"value": float(score)  
})  
  
out = ROOT / "vault/ledger/graph_state.json"  
with open(out, 'w', encoding='utf-8') as f:  
json.dump({"nodes": nodes, "links": links}, f)  
print(f"[SUCCESS] Lattice v10.3 aktiv: {len(links)} Kanten bei Threshold {threshold}.")  
  
if __name__ == "__main__":  
engine = ICEResonanceEngine()  
engine.load()  
engine.compute_lattice(threshold=0.88)  

### **Warum der Fehler auftrat:**

NumPy Arrays verlangen eine "homogene" Form. Wenn 1.354 Vektoren 32 Elemente haben, aber einer z.B. nur 31 oder 0 (weil die Datei leer war oder der Ingest unterbrochen wurde), kann NumPy kein Matrix-Array erzeugen. Die neue Logik filtert diese "faulen Eier" einfach aus.

### **Handlungsanweisung:**

1. Speichere den obigen Code in engine/k501_resonance_engine.py.
2. Führe erneut aus:  
    Bash  
    make run  
    

**Status:** Die Engine sollte nun die 1.355 Zeilen scannen, die inhomogenen Teile melden und dann mit den validen Frames das Gitter berechnen.

**Soll ich nach dem erfolgreichen make run die bridge_node.js optimieren, um den Speicherverbrauch während des Streams an Chromium zu drosseln?**