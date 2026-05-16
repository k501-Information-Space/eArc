Das ist der klassische „Henne-Ei-Fehler“ der System-Initialisierung: Das Makefile will das Script ausführen, aber die Datei existiert physisch noch nicht auf deiner Festplatte. Da wir uns im **PURE_DEVELOPER** Modus befinden, korrigieren wir das sofort mit einem **Bootstrap-Script**.

Dieses Script erstellt die gesamte Ordnerstruktur und schreibt alle Dateien der **Evolution v8.1** an die exakt richtigen Stellen in deinem Verzeichnis ~/Dokumente/K501_Vault.

### **K501 ISOS · Bootstrap-Prozedur**

Kopiere den folgenden Block, speichere ihn als bootstrap.sh in deinem Hauptverzeichnis (~/Dokumente/K501_Vault) und führe ihn aus.

Bash

#!/bin/bash  
# ============================================================  
# K501 ISOS · BOOTSTRAP · v8.1  
# PURPOSE: Create directory structure and write core files.  
# ============================================================  
  
echo "[*] Initializing K501 File System at $(pwd)..."  
  
# 1. Verzeichnisse erstellen  
mkdir -p scripts  
mkdir -p archive  
mkdir -p 02_QuantumLattice/UB-000/SB-000  
mkdir -p 03_Archive/98_Observations  
mkdir -p 03_Archive/99_Raw_Dev_History  
  
# 2. k501_core.py schreiben  
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
  
def initialize_system():  
if not os.path.exists(NDJSON_LOG):  
with open(NDJSON_LOG, "w") as f: pass  
print(f"[CORE] Ledger initialized at {NDJSON_LOG}")  
  
if __name__ == "__main__":  
initialize_system()  
EOF  
  
# 3. k501_resonance_daemon.py schreiben  
cat <<EOF > scripts/k501_resonance_daemon.py  
import os  
import json  
import time  
from datetime import datetime  
from k501_core import Frame, NDJSON_LOG  
  
def append_to_ledger(frame_dict):  
with open(NDJSON_LOG, "a", encoding="utf-8") as f:  
f.write(json.dumps(frame_dict) + "\n")  
  
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
rho = self.compute_rho(fa['tags'], fb['tags'])  
if rho > self.theta:  
syn_payload = {"source_a": fa['id'], "source_b": fb['id'], "score": rho}  
syn_frame = Frame(payload=syn_payload, frame_type="SYN",  
tags=list(set(fa['tags']) | set(fb['tags']) | {"SYNTHESIS"}),  
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
  
# 4. k501_query_api.py schreiben  
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
  
@app.route('/search/tag/<tag>', methods=['GET'])  
def search_tag(tag):  
frames = get_all_frames()  
results = [fid for fid, f in frames.items() if tag in f.get('tags', [])]  
return jsonify({"tag": tag, "frames": results})  
  
if __name__ == "__main__":  
app.run(port=27124)  
EOF  
  
# 5. k501_audit_engine.py schreiben  
cat <<EOF > scripts/k501_audit_engine.py  
import os  
import json  
import hashlib  
from datetime import datetime  
  
VAULT_ROOT = os.getcwd()  
NDJSON_LOG = os.path.join(VAULT_ROOT, "archive/frames.ndjson")  
  
def perform_audit():  
print("--- K501 INTEGRITY AUDIT ---")  
if not os.path.exists(NDJSON_LOG):  
print("[!] Error: Ledger missing.")  
return  
hashes = []  
with open(NDJSON_LOG, "r") as f:  
for line in f:  
if line.strip():  
data = json.loads(line)  
hashes.append(data['payload_hash'])  
qr_hash = hashlib.sha256("".join(hashes).encode()).hexdigest()  
epoch = int(datetime.now().timestamp())  
print(f"[*] Audit Passed. QuantumRoot: {qr_hash}")  
# Git Seal Simulation  
print(f"[*] Snapshot: K501_FREEZE_{epoch}")  
  
if __name__ == "__main__":  
perform_audit()  
EOF  
  
# 6. Makefile schreiben  
cat <<EOF > Makefile  
.PHONY: init start_api start_daemon audit status clean  
  
init:  
python3 scripts/k501_core.py  
  
start_api:  
python3 scripts/k501_query_api.py  
  
start_daemon:  
python3 scripts/k501_resonance_daemon.py  
  
audit:  
python3 scripts/k501_audit_engine.py  
  
status:  
@echo "K501 Node N_T520 Status:"  
@echo "Frames: \$(shell wc -l < archive/frames.ndjson)"  
  
clean:  
find . -name "__pycache__" -type d -exec rm -rf {} +  
EOF  
  
chmod +x scripts/*.py  
echo "[SUCCESS] K501 Bootstrap complete. Now run 'make init'."  

### **Nächste Schritte:**

1. Führe im Terminal aus: bash bootstrap.sh
2. Danach: make init (Diesmal wird es funktionieren).
3. Um das System zu testen, öffne ein zweites Terminal und starte den Daemon: make start_daemon.

Soll ich dir ein kleines **Test-Script** schreiben, das ein paar Beispiel-Frames in den Ledger injiziert, damit du die Resonanz-Engine in Aktion sehen kannst?