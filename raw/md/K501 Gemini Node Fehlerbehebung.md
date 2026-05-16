Das ist der klassische "Last Mile"-Fehler. Ein IndentationError bedeutet meistens, dass Leerzeichen und Tabs gemischt wurden oder eine Zeile nach einem try-except oder if nicht korrekt eingerückt ist.

Wir führen jetzt die **Code-Evolution v3.0** durch. Ich korrigiere den Indentation-Fehler, integriere den stabilen Direkt-API-Call für Ollama und sorge dafür, dass die Pipeline sauber mit deinem Axiom-System zusammenarbeitet.

### 1. Korrektur: modules/QH256_LLM/launch_llm.py

Dieser Code behebt den IndentationError und nutzt den stabilen api/embed Endpunkt.

Python

import requests  
import numpy as np  
  
class QH256LLM:  
def __init__(self, model="nomic-embed-text"):  
self.base_url = "http://localhost:11434/api/embed"  
self.model = model  
  
def get_semantic_vector(self, text):  
try:  
# Safe-Read & Cleanup  
clean_text = str(text)[:5000].strip()  
if not clean_text:  
return np.zeros(32, dtype=np.float32)  
  
payload = {  
"model": self.model,  
"input": clean_text  
}  
  
response = requests.post(self.base_url, json=payload, timeout=10)  
  
if response.status_code == 200:  
full_vec = response.json()["embeddings"][0]  
# Reduziere auf 32 Dimensionen für K501 Core (Slicing)  
return np.array(full_vec[:32], dtype=np.float32)  
else:  
print(f"[!] Ollama Error {response.status_code}: {response.text}")  
return np.zeros(32, dtype=np.float32)  
  
except Exception as e:  
print(f"[!] LLM Exception: {e}")  
return np.zeros(32, dtype=np.float32)  

### 2. Korrektur: modules/Minimalpipeline/launch_pipeline.py

Hier ist die vollständige, harmonisierte Evolution deiner Duplex-Pipeline.

Python

import time  
import os  
import numpy as np  
from pathlib import Path  
  
from modules.QH256_Core.launch_core import QH256Core  
from modules.QH256_Communication.launch_comm import QH256_Communication  
from modules.QH256_Algebra.launch_algebra import QH256Algebra  
from modules.QH256_LLM.launch_llm import QH256LLM  
  
class K501DuplexPipeline:  
def __init__(self, config):  
print("\n--- [K501 EVOLUTION ENGINE ACTIVATED] ---")  
self.core = QH256Core(config['ledger'])  
self.algebra = QH256Algebra(config['lib'])  
self.comm = QH256_Communication(config['comm_config'])  
self.llm = QH256LLM()  
  
# Pfad für lokales Ingest-Monitoring  
self.src_path = Path("/K501GeminiNet/src")  
self.src_path.mkdir(parents=True, exist_ok=True)  
  
def process_local_ingest(self):  
# Scannt den /src Ordner nach neuen Inhalten  
for file_path in self.src_path.glob("*.txt"):  
try:  
print(f"[*] Ingesting Source: {file_path.name}")  
with open(file_path, "r", encoding="utf-8") as f:  
content = f.read()  
  
if not content.strip(): continue  
  
# Generiere Vektor (32-dim)  
vector = self.llm.get_semantic_vector(content)  
  
# Axiomatische Frame-Erstellung  
frame = self.core.generate_frame(  
payload=content,  
vector=vector.tolist(),  
metadata={  
"origin": "local_ingest",  
"file": file_path.name,  
"node": "NODE_K501_T520_01"  
}  
)  
  
self.core.commit(frame)  
file_path.unlink() # Axiom: Verarbeitet bedeutet transformiert  
print(f"[SUCCESS] Frame {frame['id'][:8]} manifestiert.")  
except Exception as e:  
print(f"[!] Ingest Error {file_path.name}: {e}")  
  
def handle_incoming_peer_frame(self, remote_frame):  
"""Verarbeitet Frames aus der Federation (P2P)"""  
print(f"[*] Peer-Signal empfangen: {remote_frame['id'][:8]}")  
  
local_frames = list(self.core.stream_frames())  
if not local_frames:  
print("[*] Erster Remote-Frame akzeptiert.")  
self.core.commit(remote_frame)  
return  
  
# AVX-Resonanzprüfung gegen die letzten 20 lokalen Frames  
local_vecs = [f['vector'] for f in local_frames[-20:]]  
resonances = self.algebra.compute_resonance(remote_frame['vector'], local_vecs)  
  
max_res = max(resonances) if len(resonances) > 0 else 0  
print(f"[*] Maximale Resonanz: {max_res:.4f}")  
  
# Schwelle für Synchronisation  
if max_res >= 0.92:  
print(f"[SYNC] Hohe Übereinstimmung! Frame wird in Ledger integriert.")  
self.core.commit(remote_frame)  
else:  
print("[SKIP] Resonanz zu gering für Auto-Sync.")  
  
def run(self):  
# Starte P2P Interface  
self.comm.start_duplex(self.handle_incoming_peer_frame)  
print("\n>>> K501 NODE IS LIVE AND LISTENING <<<\n")  
  
try:  
while True:  
self.process_local_ingest()  
time.sleep(2) # CPU-Schonung für T520  
except KeyboardInterrupt:  
print("\n[*] Fahre Node sauber herunter...")  
self.comm.stop_duplex()  
  
if __name__ == "__main__":  
cfg = {  
'ledger': '/K501GeminiNet/Node01/vault/ledger/frames.ndjson',  
'lib': '/K501GeminiNet/core/libk501.so',  
'comm_config': '/K501GeminiNet/Node01/schemas/QH256_Communication.json'  
}  
  
# Sicherstellen, dass die Verzeichnisse existieren  
Path(cfg['ledger']).parent.mkdir(parents=True, exist_ok=True)  
  
K501DuplexPipeline(cfg).run()  

### 3. Was hat sich geändert? (Evolution Highlights)

1. **Axiom-Integration:** Das Skript nutzt nun core.generate_frame, was sicherstellt, dass id, seq und prev automatisch nach deinen mathematischen Regeln berechnet werden.
2. **32-Dim Fix:** Da nomic-embed-text standardmäßig 768 Dimensionen liefert, dein T520 C-Kern aber auf 32 optimiert ist, schneidet full_vec[:32] den Vektor jetzt sauber ab. Das verhindert Abstürze in der libk501.so.
3. **Fehlertoleranz:** Der 400 Bad Request Fehler wird durch das Slicing des Textes ([:5000]) und die direkte JSON-Struktur im LLM-Modul verhindert.
4. **Zero-Drift:** Durch das Löschen der Datei im src Ordner nach dem Ingest (file_path.unlink()) stellen wir sicher, dass keine Duplikate entstehen und der Ledger die einzige Quelle der Wahrheit bleibt.

### Nächster Schritt:

Bevor du sudo ./start_node.sh erneut ausführst, stelle sicher, dass Ollama das neue Modell geladen hat:

Bash

ollama pull nomic-embed-text  

**Soll ich dir helfen, ein Test-Fragment in /K501GeminiNet/src/test.txt zu schreiben, um zu sehen, ob die Pipeline es jetzt ohne Fehler "frisst"?**