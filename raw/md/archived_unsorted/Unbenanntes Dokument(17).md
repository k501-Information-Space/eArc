Alles klar, wir gehen jetzt auf vollständigen, sauberen Boot-Ingest, bei dem alles neu eingelesen und verarbeitet wird. Strukturierte Umsetzung:

## **1. Zielsetzung**

- Clean Boot: Alle bisherigen Ledger-Frames ignorieren.  
    
- Vollständiger Ingest: Alle Dateien unter /K501GeminiNet/99.0/ werden gelesen.  
    
- Automatischer DeepRead: Direkt nach Ingest für alle Dokumente.  
    
- Indexing: Vollständiger Aufbau von Frame-Vektoren und Ledger.  
    
- Output: frames.ndjson + frames_updated.ndjson (DeepRead-Ergebnisse).  
    
- Keine manuelle prepare_paths.json nötig.  
    

## **2. Vorgehensweise**

1. Dateipfade sammeln  
    

from pathlib import Path

BASE_PATH = Path("/K501GeminiNet")

SOURCE_DIR = BASE_PATH / "99.0"

all_files = [str(f) for f in SOURCE_DIR.rglob("*") if f.is_file()]

print(f"[*] Gefundene Dateien zum Ingest: {len(all_files)}")

1. Ledger vorbereiten (neu)  
    

LEDGER_FILE = BASE_PATH / "Node01/vault/ledger/frames.ndjson"

OUTPUT_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_updated.ndjson"

# leere Ledger-Dateien erstellen / überschreiben

LEDGER_FILE.write_text("")

OUTPUT_LEDGER.write_text("")

1. Frame-Generierung & DeepRead direkt integrieren  
    

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

import hashlib

import json

llm = QH256LLM()

algebra = QH256Algebra(str(BASE_PATH / "core/libk501.so"))

def generate_frame(file_path):

with open(file_path, "r", encoding="utf-8") as f:

content = f.read()

vector = llm.get_semantic_vector(content)[:32]

frame = {

"id": hashlib.sha256((file_path + str(vector)).encode()).hexdigest(),

"path": file_path,

"vector": vector,

"payload": content[:512],

"valid": True

}

return frame

updated_count = 0

with open(LEDGER_FILE, "a") as ledger_f, open(OUTPUT_LEDGER, "a") as deepread_f:

for fpath in all_files:

frame = generate_frame(fpath)

ledger_f.write(json.dumps(frame) + "\n")

# direkt DeepRead (hier identisch zu Frame, aber kann zusätzliche Analysen enthalten)

deepread_f.write(json.dumps(frame) + "\n")

updated_count += 1

print(f"[*] Clean Boot Ingest + DeepRead abgeschlossen. Frames verarbeitet: {updated_count}")

## **4. Vorteile dieser Vorgehensweise**

- Clean Boot: Keine alten Ledger-Frames oder prepare_paths.json werden berücksichtigt.  
    
- Vollständig reproduzierbar: Jeder Pfad aus 99.0 wird als Frame erfasst.  
    
- DeepRead integriert: Vektoren, Payloads und ID-Generierung in einem Durchgang.  
    
- Bereit für Indexing: Output frames_updated.ndjson kann sofort in Indexierung und weitere Module eingespeist werden.  
    

Wenn du willst, kann ich dir direkt eine fertige multipass_deepread_clean.py schreiben, die alles in einem Durchgang erledigt, inkl. optionalem parallelen Ingest und Progress-Tracking, sodass die 900+ Dateien sauber und deterministisch verarbeitet werden.

Willst du, dass ich diese Version erstelle?