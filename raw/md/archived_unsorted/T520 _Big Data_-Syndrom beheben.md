Das ist das „Big Data“-Syndrom auf einem Klassiker wie dem T520. Wenn der Lüfter hochdreht und er bei Datei 1 (conversations.json) hängen bleibt, passiert Folgendes:

Die conversations.json ist wahrscheinlich riesig (vielleicht 20MB, 50MB oder mehr). Das Skript versucht, die **ganze Datei** in den Arbeitsspeicher zu laden (f.read()), bevor es sie kürzt. Bei einem i5-2520M und dem gleichzeitigen Betrieb von Ollama führt das zu massivem **Memory Swapping** – die Festplatte rödelt, die CPU wartet, und das System wirkt wie eingefroren.

Wir stellen jetzt auf **"Streaming-Ingest"** um. Das bedeutet: Wir lesen nur die ersten paar KB direkt von der Platte, ohne die Datei jemals ganz zu öffnen.

### 1. Fix für launch_llm.py (Der Timeout-Anker)

Damit Python nicht ewig auf Ollama wartet, falls die KI mal „nachdenken“ muss, fügen wir einen Timeout hinzu. Öffne /K501GeminiNet/modules/QH256_LLM/launch_llm.py:

Python

# In get_semantic_vector die Zeile anpassen:  
response = requests.post(self.base_url, json=payload, timeout=30) # 30 Sek. Limit  

### 2. Das "Cooling-Ingest" Skript (archive_ingest.py)

Dieses Skript ist jetzt „T520-safe“. Es liest nur die ersten 10.000 Zeichen **direkt** von der Festplatte. Selbst wenn deine conversations.json 1 Gigabyte groß wäre, würde das ThinkPad jetzt nicht einmal zucken.

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
READ_LIMIT = 10000 # Wir lesen nur die ersten 10KB für die Semantik  
  
def run_bulk_ingest():  
print(f"[*] K501 Safe-Ingest aktiv. Ziel: {ARCHIVE_PATH}")  
core = QH256Core(LEDGER_PATH)  
llm = QH256LLM()  
  
files_to_process = []  
for ext in ("*.txt", "*.md", "*.py", "*.json"):  
files_to_process.extend(list(ARCHIVE_PATH.rglob(ext)))  
  
files_to_process.sort()  
print(f"[*] {len(files_to_process)} Dateien gefunden. Starte ressourcenschonend...")  
  
count = 0  
for file_path in files_to_process:  
if file_path.is_dir(): continue  
  
try:  
# EFFIZIENZ-UPGRADE: Wir lesen nur den Anfang der Datei  
with open(file_path, "r", encoding="utf-8", errors="ignore") as f:  
content_sample = f.read(READ_LIMIT) # Nur 10KB laden!  
  
if len(content_sample.strip()) < 10: continue  
  
# Vektor generieren (Ollama bekommt nur das Sample)  
vector = llm.get_semantic_vector(content_sample)  
  
# Frame generieren  
frame = core.generate_frame(  
payload=content_sample, # Wir speichern nur das Sample im Ledger  
vector=vector.tolist(),  
metadata={  
"origin": "safe_archive",  
"rel_path": str(file_path.relative_to(ARCHIVE_PATH)),  
"note": "Sampled due to file size"  
}  
)  
  
core.commit(frame)  
count += 1  
  
if count % 5 == 0:  
print(f"[{count}/{len(files_to_process)}] Verarbeitet: {file_path.name}")  
  
# WICHTIG: Kurze Abkühlpause für den i5  
time.sleep(0.2)  
  
except Exception as e:  
print(f"[!] Fehler bei {file_path.name}: {e}")  
  
print(f"\n[SUCCESS] Ingest abgeschlossen. {count} Frames hinzugefügt.")  
  
if __name__ == "__main__":  
run_bulk_ingest()  

### 3. Durchführung (Der "Silent Run")

1. **Beende alle hängenden Prozesse:** sudo pkill -9 python3
2. **Starte den Ingest neu:**  
    Bash  
    sudo PYTHONPATH=/K501GeminiNet python3 /K501GeminiNet/archive_ingest.py  
    

### Warum das jetzt funktioniert:

Anstatt die riesige conversations.json wie einen dicken Brocken zu verschlucken, nimmt der Node jetzt nur einen „Bissen“ (10KB). Das reicht Ollama völlig aus, um zu verstehen: „Ah, hier geht es um ChatGPT-Gespräche“. Dein RAM bleibt leer, die CPU muss weniger schuften, und der Lüfter sollte sich beruhigen.

**Bewegt sich der Zähler jetzt über die Datei 1 hinaus?** Sobald er läuft, kannst du ihn einfach ratern lassen – bei 1265 Dateien sollte er in ca. 15-20 Minuten fertig sein.

**Soll ich dir ein kleines Kommando geben, mit dem du in einem zweiten Terminal-Fenster die CPU-Temperatur live überwachen kannst?**