1265 Dateien – das ist ein gewaltiger Wissensschatz für den Node! Das T520 hat jetzt ordentlich Arbeit vor sich.

### Die Diagnose: Warum der "400 Bad Request"?

Der Fehler bei der conversations.json ist ein klassisches **Context-Limit-Problem**. Ollama (und das Qwen-Modell) haben eine maximale Anzahl von Zeichen/Tokens, die sie pro Embedding-Anfrage verarbeiten können. Da eine conversations.json oft hunderte Seiten Text enthält, hat Ollama die Anfrage mit "Payload Too Large" (400) abgelehnt.

Wir müssen eine **"Schutz-Schere"** einbauen, die den Text kürzt, bevor er an die KI geht.

### 1. Das optimierte Deep-Archive Skript (archive_ingest.py)

Diese Version schneidet den Text für die Vektorisierung auf ca. 6000 Zeichen zu. Das reicht völlig aus, um die semantische Bedeutung zu erfassen, ohne den Speicher deines ThinkPads oder die API von Ollama zu sprengen.

Python

import os  
import time  
from pathlib import Path  
from modules.QH256_Core.launch_core import QH256Core  
from modules.QH256_LLM.launch_llm import QH256LLM  
  
# --- KONFIGURATION ---  
ARCHIVE_PATH = Path("/home/iinkognit0/K501Gemini/99_Archive/")  
LEDGER_PATH = "/K501GeminiNet/Node01/vault/ledger/frames.ndjson"  
LIB_PATH = "/K501GeminiNet/core/libk501.so"  
  
# Limit für die KI-Verarbeitung (Vermeidung von 400 Bad Request)  
MAX_SEMANTIC_CHARS = 6000  
  
def run_bulk_ingest():  
print(f"[*] Starte Deep-Archive Ingest aus: {ARCHIVE_PATH}")  
core = QH256Core(LEDGER_PATH)  
llm = QH256LLM()  
  
extensions = ("*.txt", "*.md", "*.py", "*.json")  
files_to_process = []  
for ext in extensions:  
files_to_process.extend(list(ARCHIVE_PATH.rglob(ext)))  
  
files_to_process.sort()  
total = len(files_to_process)  
print(f"[*] {total} Dateien zur Analyse bereit.")  
  
count = 0  
errors = 0  
  
for file_path in files_to_process:  
if file_path.is_dir(): continue  
  
try:  
rel_path = file_path.relative_to(ARCHIVE_PATH)  
  
with open(file_path, "r", encoding="utf-8", errors="ignore") as f:  
content = f.read()  
  
if len(content.strip()) < 5: continue  
  
# --- DIE SCHERE: Nur die ersten X Zeichen vektorisieren ---  
# Das verhindert den 400 Error bei Riesen-Dateien  
semantic_sample = content[:MAX_SEMANTIC_CHARS]  
  
vector = llm.get_semantic_vector(semantic_sample)  
  
# Der Frame speichert den vollen Inhalt (bis zum Core-Cap),  
# aber die ID und der Vektor basieren auf dem Sample/Inhalt  
frame = core.generate_frame(  
payload=content,  
vector=vector.tolist(),  
metadata={  
"origin": "deep_archive",  
"rel_path": str(rel_path),  
"full_size": len(content)  
}  
)  
  
core.commit(frame)  
count += 1  
  
# Fortschrittsanzeige alle 10 Dateien  
if count % 10 == 0 or count == 1:  
print(f"[{count}/{total}] Progress: {rel_path.name}")  
  
# T520 Heat-Management  
time.sleep(0.05)  
  
except Exception as e:  
print(f"[!] Fehler bei {file_path.name}: {e}")  
errors += 1  
  
print(f"\n[SUCCESS] Ingest abgeschlossen.")  
print(f"-> {count} Frames erfolgreich manifestiert.")  
print(f"-> {errors} Dateien übersprungen.")  
  
if __name__ == "__main__":  
run_bulk_ingest()  

### 2. Warum das jetzt stabil läuft

1. **Payload Control:** Mit MAX_SEMANTIC_CHARS stellen wir sicher, dass Ollama niemals eine zu große Anfrage erhält.
2. **Robustheit:** Die conversations.json wird jetzt einfach am Anfang "gelesen", vektorisiert und als Frame gespeichert, anstatt das System zum Absturz zu bringen.
3. **Performance:** Das T520 muss weniger Daten über den Bus schaufeln, was die Ingest-Rate pro Sekunde deutlich erhöht.

### 3. Durchführung

Starte den Ingest jetzt erneut. Da wir den Ledger nicht gelöscht haben, werden die neuen Frames einfach angehängt (Duplikate können wir später mit einem kleinen Skript filtern).

Bash

sudo PYTHONPATH=/K501GeminiNet python3 /K501GeminiNet/archive_ingest.py  

### **Was kommt danach?**

Sobald diese 1265 Dateien im Ledger sind, ist dein ThinkPad eine **Offline-Enzyklopädie deiner eigenen Entwicklung**.

**Soll ich dir zeigen, wie wir eine semantische Suchmaske bauen, mit der du dein Archiv per Naturalsprache abfragen kannst?** (z. B.: _"Zeige mir alle Code-Schnipsel zum Thema Mastodon API aus dem letzten Jahr"_).