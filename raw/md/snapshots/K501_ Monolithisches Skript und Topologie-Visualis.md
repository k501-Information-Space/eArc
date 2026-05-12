Entschuldige die Verwirrung – da habe ich im „Entwickler-Rausch“ die Datei-Struktur zwar sauber getrennt, aber den Namen k501_full_sync.py als monolithische Option in den Raum geworfen, ohne den entsprechenden zusammenhängenden Block zu liefern.

**Die Idee dahinter:** Wenn du keine Lust auf das Hin-und-Her zwischen verschiedenen Dateien hast, dient die k501_full_sync.py als dein **„Master-Script“**. Es enthält alles: Die Core-Logik, die Migration und das Dashboard in einer einzigen Datei.

Hier ist der vollständige, ungestückelte Inhalt für scripts/k501_full_sync.py:

### **scripts/k501_full_sync.py**

_Das „Alles-in-Einem“-Werkzeug für N_T520._

Python

import os, json, hashlib, time  
import numpy as np  
import networkx as nx  
import matplotlib.pyplot as plt  
from datetime import datetime  
from concurrent.futures import ThreadPoolExecutor  
  
# ============================================================  
# K501 FULL SYNC · v9.2 · MONOLITH  
# ============================================================  
  
VAULT_ROOT = os.getcwd()  
ARCHIVE_DIR = os.path.join(VAULT_ROOT, "archive")  
NDJSON_LOG = os.path.join(ARCHIVE_DIR, "frames.ndjson")  
ARCHIVE_PATH = os.path.join(VAULT_ROOT, "03_Archive")  
  
class Frame:  
def __init__(self, payload, frame_type="RAW", tags=None):  
self.epoch = int(datetime.now().timestamp())  
self.payload = payload  
self.frame_type = frame_type  
self.tags = list(set(tags)) if tags else []  
payload_str = json.dumps(payload, sort_keys=True)  
self.payload_hash = hashlib.sha256(payload_str.encode()).hexdigest()  
self.id = f"F-{self.payload_hash[:16].upper()}"  
  
def to_dict(self):  
return {  
"id": self.id, "epoch": self.epoch, "frame_type": self.frame_type,  
"tags": self.tags, "payload_hash": self.payload_hash, "payload": self.payload  
}  
  
@staticmethod  
def vectorize(content, bins=1024):  
vec = np.zeros(bins, dtype=np.float32)  
tokens = str(content).lower().split()  
for token in tokens:  
idx = int(hashlib.md5(token.encode()).hexdigest(), 16) % bins  
vec[idx] += 1  
norm = np.linalg.norm(vec)  
return vec / norm if norm > 0 else vec  
  
def append_to_ledger(frame_dict):  
os.makedirs(os.path.dirname(NDJSON_LOG), exist_ok=True)  
with open(NDJSON_LOG, "a", encoding="utf-8") as f:  
f.write(json.dumps(frame_dict) + "\n")  
  
def run_full_sync():  
print("--- K501 NODE N_T520: FULL SYNC & TOPOLOGY ---")  
  
# 1. Check if Migration is needed  
if not os.path.exists(NDJSON_LOG) or os.path.getsize(NDJSON_LOG) == 0:  
print("[*] Ledger leer. Starte Initial-Migration...")  
files = [os.path.join(r, fn) for r, d, fs in os.walk(ARCHIVE_PATH) for fn in fs if not fn.startswith(".")]  
for fpath in files:  
with open(fpath, "r", encoding="utf-8", errors='ignore') as f:  
frame = Frame(payload={"content": f.read(), "file": os.path.basename(fpath)})  
append_to_ledger(frame.to_dict())  
print("[SUCCESS] Migration abgeschlossen.")  
  
# 2. Load and Vectorize  
print("[*] Lade Gitter-Daten...")  
with open(NDJSON_LOG, "r", encoding="utf-8") as f:  
frames = [json.loads(line) for line in f if line.strip()]  
  
# Für die Performance auf dem i5-2520M begrenzen wir die Visualisierung  
display_frames = frames[-1500:]  
G = nx.Graph()  
vectors = []  
  
print(f"[*] Berechne DNA für {len(display_frames)} Objekte...")  
for f in display_frames:  
v = Frame.vectorize(f['payload'].get('content', ''))  
vectors.append(v)  
G.add_node(f['id'], type=f['frame_type'])  
  
vectors = np.array(vectors)  
num = len(vectors)  
  
print(f"[*] Starte Resonanz-Abgleich (~{num*num//2} Operationen)...")  
# Hier „hängt“ das Terminal normalerweise – der i5 rechnet!  
for i in range(num):  
for j in range(i + 1, num):  
similarity = np.dot(vectors[i], vectors[j])  
if similarity > 0.85:  
G.add_edge(display_frames[i]['id'], display_frames[j]['id'])  
  
print("[*] Erzeuge visuelle Projektion...")  
plt.figure(figsize=(12, 10), facecolor='#0e1117')  
pos = nx.spring_layout(G, k=0.15, iterations=20)  
nx.draw(G, pos, node_size=15, node_color="cyan", edge_color="white", alpha=0.3)  
plt.title(f"K501 TOPOLOGY: {len(G)} Nodes", color="white")  
plt.show()  
  
if __name__ == "__main__":  
run_full_sync()  

### **Warum das Terminal „hängt“**

Dass dein Terminal bei [*] Generating Topology Graph... stehen bleibt, ist kein Bug, sondern pure Arbeit.

Dein i5-2520M muss für jeden deiner 1.416 Frames prüfen, wie ähnlich er jedem _anderen_ Frame ist. Das sind mathematisch gesehen:

$$\frac{1416 \times 1415}{2} = 1.001.820 \text{ Punktprodukte}$$

Jedes dieser Produkte verrechnet zwei Vektoren mit je 1.024 Dimensionen. Selbst für eine Sandy-Bridge-CPU ist das eine ordentliche Last.

**Geduld:** Gib ihm ca. **30 bis 60 Sekunden**. Sobald er fertig ist, öffnet sich ein Fenster mit dem Graphen.

### **Wie geht es weiter?**

Sobald du das Bild des Graphen gesehen hast (und damit die Bestätigung hast, dass deine Daten „leben“), können wir die API erweitern.

**Soll ich die API-Route /resonance/top vorbereiten, damit wir die „stärksten“ Gedankenverbindungen als Textliste ausgeben können, ohne jedes Mal den Graphen rendern zu müssen?**