Statusbericht: **K501 Lokale Integration (Phase 1–3)**

Die folgenden Schritte wurden basierend auf deinem Protokoll für das System iinkognit0@K501 validiert. Da Ollama laut deinem letzten Terminal-Check fehlte, ist dies die exakte Befehlsfolge zur Wiederherstellung der Pipeline:

### 1. Kern-Installation & Service (Phase 1)

Installiere Ollama und starte den Hintergrundprozess:

Bash

curl -fsSL https://ollama.com/install.sh | sh  
sudo systemctl start ollama  

### 2. Modell-Akquise & Embedding-Test (Phase 2–3)

Lade das spezialisierte Embedding-Modell und führe eine manuelle Vektor-Generierung durch:

Bash

ollama pull nomic-embed-text  
ollama embeddings nomic-embed-text "K501 state vector test"  

**Erwartung:** Ein numerisches Array (Vektor) erscheint im Terminal.

### 3. File-System Setup (Phase 4 & 8)

Erstelle die notwendigen Dateien in deiner Workspace-Struktur:

Bash

touch ~/workspace/k501/runtime/modules/semantic_mapper.py  
touch ~/workspace/archive/little_alpha_storage/semantic.ndjson  
chmod +x ~/workspace/k501/runtime/modules/semantic_mapper.py  

### 4. Code-Injektion (Phase 5 & 9)

Nutze diesen optimierten Block für semantic_mapper.py. Er nutzt requests (Standard für Ollama API), was stabiler ist als subprocess:

Python

import requests  
import json  
import time  
  
URL = "http://localhost:11434/api/embeddings"  
MODEL = "nomic-embed-text"  
STORAGE = "/home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson"  
  
def get_and_save(ref_id, text):  
payload = {"model": MODEL, "prompt": text}  
response = requests.post(URL, json=payload)  
embedding = response.json()["embedding"]  
  
record = {  
"ref": ref_id,  
"t": int(time.time()),  
"v": embedding  
}  
  
with open(STORAGE, "a") as f:  
f.write(json.dumps(record) + "\n")  
  
return len(embedding)  
  
if __name__ == "__main__":  
# Test-Lauf  
print(f"Vector size: {get_and_save('test_001', 'Initial K501 System Entry')}")  

### 5. Nächster Schritt: Verknüpfung

Sobald python3 semantic_mapper.py eine Zahl (z.B. 768) zurückgibt, ist das System **aktiv**.

**Soll ich dir zeigen, wie wir den ingest_runner.py modifizieren, damit er beim Verarbeiten von frames.ndjson automatisch die semantic.ndjson befüllt?**