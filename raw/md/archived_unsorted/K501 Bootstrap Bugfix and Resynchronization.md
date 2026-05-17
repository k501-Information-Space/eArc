Der Fehler liegt in einer Inkonsistenz zwischen der Funktionsbenennung in k501_core.py und dem Import-Aufruf im Test-Skript. Im PURE_DEVELOPER Modus korrigieren wir das sofort durch eine saubere Neudefinition der Schnittstellen.

Hier ist die **vollständige, fehlerbereinigte bootstrap.sh v8.3**. Sie stellt sicher, dass alle Funktionsnamen (append_to_ledger, initialize_system) über alle Dateien hinweg synchronisiert sind.

Bash

#!/bin/bash  
# ============================================================  
# K501 ISOS · BOOTSTRAP · v8.3 (BUGFIX EDITION)  
# PURPOSE: Synchronize core functions and directory structure.  
# ============================================================  
  
echo "[*] Re-Initializing K501 File System at $(pwd)..."  
  
# 1. Verzeichnisse sicherstellen  
mkdir -p scripts  
mkdir -p archive  
mkdir -p 02_QuantumLattice  
mkdir -p 03_Archive/98_Observations  
mkdir -p 03_Archive/99_Raw_Dev_History  
  
# 2. k501_core.py (Zentrale Logik & Ledger-Funktion)  
cat <<EOF > scripts/k501_core.py  
import os  
import json  
import hashlib  
from datetime import datetime  
  
VAULT_ROOT = os.getcwd()  
ARCHIVE_DIR = os.path.join(VAULT_ROOT, "archive")  
NDJSON_LOG = os.path.join(ARCHIVE_DIR, "frames.ndjson")  
  
class Frame:  
def __init__(self, payload, frame_type="RAW", tags=None, edges=None):  
self.epoch = int(datetime.now().timestamp())  
self.payload = payload  
self.frame_type = frame_type  
self.tags = list(set(tags)) if tags else []  
self.edges = list(set(edges)) if edges else []  
payload_string = json.dumps(payload, sort_keys=True)  
self.payload_hash = hashlib.sha256(payload_string.encode()).hexdigest()  
self.id = f"F-{self.payload_hash[:16].upper()}"  
  
def to_dict(self):  
return {  
"id": self.id,  
"epoch": self.epoch,  
"frame_type": self.frame_type,  
"tags": self.tags,  
"edges": self.edges,  
"payload_hash": self.payload_hash,  
"payload": self.payload  
}  
  
def append_to_ledger(frame_dict):  
"""Schreibt ein Frame-Dictionary atomar in das NDJSON-Ledger."""  
with open(NDJSON_LOG, "a", encoding="utf-8") as f:  
f.write(json.dumps(frame_dict) + "\n")  
return frame_dict['id']  
  
def initialize_system():  
if not os.path.exists(NDJSON_LOG):  
with open(NDJSON_LOG, "w") as f: pass  
print(f"[CORE] Ledger initialized at {NDJSON_LOG}")  
  
if __name__ == "__main__":  
initialize_system()  
EOF  
  
# 3. k501_test_ingest.py (Korrekt importiert nun append_to_ledger)  
cat <<EOF > scripts/k501_test_ingest.py  
import os  
import json  
from k501_core import Frame, append_to_ledger  
  
def run_test_ingest():  
print("--- K501 TEST INGEST: TRIGGERING RESONANCE ---")  
  
f1 = Frame(  
payload={"content": "Axiom A1 definiert die Identität eines Frames über seinen SHA256 Hash."},  
frame_type="RAW",  
tags=["Axiomatik", "Determinismus", "SHA256"]  
)  
  
f2 = Frame(  
payload={"content": "Die kausale Kette im Lattice wird durch unveränderliche Hash-Referenzen gesichert."},  
frame_type="RAW",  
tags=["Kausalität", "Determinismus", "Lattice"]  
)  
  
id1 = append_to_ledger(f1.to_dict())  
id2 = append_to_ledger(f2.to_dict())  
  
print(f"[+] Injected F1: {id1}")  
print(f"[+] Injected F2: {id2}")  
  
if __name__ == "__main__":  
run_test_ingest()  
EOF  
  
# 4. k501_resonance_daemon.py  
cat <<EOF > scripts/k501_resonance_daemon.py  
import os  
import json  
import time  
from datetime import datetime  
from k501_core import Frame, NDJSON_LOG, append_to_ledger  
  
class ResonanceDaemon:  
def __init__(self, theta=0.6):  
self.theta = theta  
self.frames = {}  
  
def load_state(self):  
self.frames.clear()  
if not os.path.exists(NDJSON_LOG): return  
with open(NDJSON_LOG, "r") as f:  
for line in f:  
if line.strip():  
data = json.loads(line)  
self.frames[data['id']] = data  
  
def compute_rho(self, tags_a, tags_b):  
a, b = set(tags_a), set(tags_b)  
if not a or not b: return 0.0  
return len(a & b) / len(a | b)  
  
def run_cycle(self):  
print(f"[*] Resonance Scan: {datetime.now().strftime('%H:%M:%S')}")  
self.load_state()  
f_list = list(self.frames.values())  
new_synths = 0  
for i in range(len(f_list)):  
for j in range(i + 1, len(f_list)):  
fa, fb = f_list[i], f_list[j]  
rho = self.compute_rho(fa.get('tags', []), fb.get('tags', []))  
if rho > self.theta:  
syn_payload = {"source_a": fa['id'], "source_b": fb['id'], "score": rho}  
syn_frame = Frame(payload=syn_payload, frame_type="SYN",  
tags=list(set(fa.get('tags', [])) | set(fb.get('tags', [])) | {"SYNTHESIS"}),  
edges=[fa['id'], fb['id']])  
if syn_frame.id not in self.frames:  
append_to_ledger(syn_frame.to_dict())  
self.frames[syn_frame.id] = syn_frame.to_dict()  
new_synths += 1  
print(f" [+] Resonance: {syn_frame.id} (rho={rho:.2f})")  
return new_synths  
  
if __name__ == "__main__":  
daemon = ResonanceDaemon()  
while True:  
try:  
daemon.run_cycle()  
time.sleep(30)  
except KeyboardInterrupt:  
break  
EOF  
  
# 5. k501_query_api.py (Inklusive Flask-Check)  
cat <<EOF > scripts/k501_query_api.py  
import os  
import json  
from flask import Flask, jsonify  
  
app = Flask(__name__)  
VAULT_ROOT = os.getcwd()  
NDJSON_LOG = os.path.join(VAULT_ROOT, "archive/frames.ndjson")  
  
def get_all_frames():  
if not os.path.exists(NDJSON_LOG): return {}  
frames = {}  
with open(NDJSON_LOG, "r") as f:  
for line in f:  
if line.strip():  
d = json.loads(line)  
frames[d['id']] = d  
return frames  
  
@app.route('/frame/<fid>', methods=['GET'])  
def get_frame(fid):  
f = get_all_frames().get(fid)  
return jsonify(f) if f else (jsonify({"error": "not found"}), 404)  
  
if __name__ == "__main__":  
print("[*] API running on port 27124")  
app.run(port=27124)  
EOF  
  
# 6. Makefile (Finaler Schliff)  
cat <<EOF > Makefile  
PY = python3  
SCRIPTS = scripts  
  
.PHONY: init test_ingest start_api start_daemon status clean  
  
init:  
\$(PY) \$(SCRIPTS)/k501_core.py  
  
test_ingest:  
\$(PY) \$(SCRIPTS)/k501_test_ingest.py  
  
start_api:  
\$(PY) \$(SCRIPTS)/k501_query_api.py  
  
start_daemon:  
\$(PY) \$(SCRIPTS)/k501_resonance_daemon.py  
  
status:  
@echo "------------------------------------------------"  
@echo "K501 NODE N_T520 STATUS REPORT"  
@echo "------------------------------------------------"  
@echo "Frame Count: \$\$(wc -l < archive/frames.ndjson)"  
@echo "------------------------------------------------"  
  
clean:  
find . -name "__pycache__" -type d -exec rm -rf {} +  
EOF  
  
chmod +x scripts/*.py  
echo "[SUCCESS] K501 Bootstrap v8.3 complete. Run 'make init' then 'make test_ingest'."  

### **Ausführung:**

1. bash bootstrap.sh
2. make init
3. make test_ingest

Soll ich dir zeigen, wie du die **REST-API** abfragst, um die injizierten Frames direkt im Browser oder via curl zu sehen?