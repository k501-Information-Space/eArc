archive_ingest.py

import os, time

from pathlib import Path

from modules.QH256_Core.launch_core import QH256Core

from modules.QH256_LLM.launch_llm import QH256LLM

ARCHIVE_PATH = Path("/home/iinkognit0/K501Gemini/99_Archive/")

LEDGER_PATH = "/K501GeminiNet/Node01/vault/ledger/frames.ndjson"

LIB_PATH = "/K501GeminiNet/core/libk501.so"

READ_LIMIT = 10000 # <--- DER RETTER: Nur 10KB lesen

def run_safe_ingest():

core = QH256Core(LEDGER_PATH)

llm = QH256LLM()

files = []

for ext in ("*.txt", "*.md", "*.py", "*.json"):

files.extend(list(ARCHIVE_PATH.rglob(ext)))

files.sort()

print(f"[*] Safe-Ingest: Verarbeite {len(files)} Dateien...")

for i, file_path in enumerate(files):

try:

# Wir lesen nur den Kopf der Datei

with open(file_path, "r", encoding="utf-8", errors="ignore") as f:

content_sample = f.read(READ_LIMIT)

if len(content_sample.strip()) < 10: continue

# Vektor generieren (nur für das Sample)

vector = llm.get_semantic_vector(content_sample)

frame = core.generate_frame(

payload=content_sample,

vector=vector.tolist(),

metadata={"origin": "safe_archive", "rel_path": str(file_path.relative_to(ARCHIVE_PATH))}

)

core.commit(frame)

if (i+1) % 10 == 0: print(f"[{i+1}/{len(files)}] {file_path.name}")

time.sleep(0.1) # Abkühlpause

except Exception as e:

print(f"[!] Fehler bei {file_path.name}: {e}")

if __name__ == "__main__":

run_safe_ingest()

parallel_ingest.py

#!/usr/bin/env python3

import os

import sys

import time

from pathlib import Path

from concurrent.futures import ProcessPoolExecutor, as_completed

# K501 Module laden

sys.path.append("/K501GeminiNet")

try:

from modules.QH256_LLM.launch_llm import QH256LLM

# Falls QH256Core benötigt wird, hier entkommentieren

# from modules.QH256_Core.launch_core import QH256Core

except ImportError as e:

print(f"[!] Modul-Import fehlgeschlagen: {e}")

sys.exit(1)

# Pfad-Konfiguration

ARCHIVE_DIR = "/home/iinkognit0/K501Gemini/99_Archive"

LEDGER_PATH = "/K501GeminiNet/Node01/vault/ledger/frames.ndjson"

def worker_generate_vector(file_path):

"""Parallel arbeitende Funktion für die Vektorisierung eines einzelnen Files"""

try:

# Jeder Prozess initialisiert eine eigene Instanz (wichtig für Thread-Safety bei Ollama/API)

llm = QH256LLM()

file_name = os.path.basename(file_path)

# Simulierter/Echter Extraktions- und Vektorisierungsprozess

# Hier rufst du deine spezifische QH256-Logik auf:

# result = llm.vectorize_file(file_path)

# Dummy-Erfolg für die Demo-Struktur:

time.sleep(0.1) # Kurze Pause zur Simulation

return True, file_name

except Exception as e:

return False, f"Fehler bei {file_path}: {str(e)}"

def run_mass_ingest():

print(f"=== [K501 MASS INGEST: STARTING HARVEST] ===")

archive_path = Path(ARCHIVE_DIR)

# 1. Sammeln

all_files = [str(f) for f in archive_path.rglob("*") if f.is_file()]

total_files = len(all_files)

print(f"[*] {total_files} Dateien identifiziert.")

if total_files == 0:

return

# 2. Parallel Processing

start_time = time.time()

manifested_count = 0

worker_count = os.cpu_count() or 2

print(f"[*] Starte Parallel-Vektorisierung (Worker: {worker_count})...")

with ProcessPoolExecutor(max_workers=worker_count) as executor:

futures = {executor.submit(worker_generate_vector, f): f for f in all_files}

for future in as_completed(futures):

success, info = future.result()

if success:

manifested_count += 1

if manifested_count % 50 == 0: # Status-Update alle 50 Files

print(f" [>] {manifested_count}/{total_files} Frames manifestiert...")

else:

print(f" [!] Skip: {info}")

total_time = time.time() - start_time

fps = manifested_count / total_time if total_time > 0 else 0

# 3. Abschlussbericht

print(f"\n--- [HARVEST COMPLETED] ---")

print(f"[*] Frames manifestiert: {manifested_count}")

print(f"[*] Gesamtzeit: {total_time:.2f}s (Schnitt: {total_time/max(1,manifested_count):.2f}s pro Frame)")

print(f"[*] Performance: {fps:.2f} f/s")

if __name__ == "__main__":

run_mass_ingest()

deepread_multipass.py

#!/usr/bin/env python3

import os

import json

from pathlib import Path

from urllib.parse import urlparse

import requests

from bs4 import BeautifulSoup # Für HTML Parsing

import hashlib

# ---------------------------

# Konfiguration

# ---------------------------

BASE_PATH = Path("/K501GeminiNet")

PREPARE_REPORT = BASE_PATH / "Node01/vault/ledger/deepread_prepare_report.json"

DEEPREAD_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_deepread.ndjson"

BATCH_SIZE = 20 # Für Multipass / Batch Processing

USER_AGENT = "K501-DeepRead/1.0"

# ---------------------------

# Hilfsfunktionen

# ---------------------------

def file_sha256(path: Path):

h = hashlib.sha256()

with open(path, "rb") as f:

for chunk in iter(lambda: f.read(4096), b""):

h.update(chunk)

return h.hexdigest()

def read_file(path: Path):

try:

with open(path, "r", encoding="utf-8") as f:

return f.read()

except Exception as e:

return f"ERROR: {e}"

def read_url(url: str):

try:

headers = {"User-Agent": USER_AGENT}

r = requests.get(url, headers=headers, timeout=10)

r.raise_for_status()

return r.text

except Exception as e:

return f"ERROR: {e}"

def extract_links(html: str, base_url: str):

"""Extrahiert relative und absolute Links für rekursives Crawlen"""

soup = BeautifulSoup(html, "html.parser")

links = set()

for a in soup.find_all("a", href=True):

href = a["href"]

parsed = urlparse(href)

if parsed.scheme in ["http", "https"]:

links.add(href)

elif href.startswith("/"):

# Relativer Pfad → absolut

parsed_base = urlparse(base_url)

links.add(f"{parsed_base.scheme}://{parsed_base.netloc}{href}")

return list(links)

def process_local_path(path_info):

"""Rekursives Einlesen lokaler Dateien"""

path_type = path_info["type"]

path = Path(path_info["path"])

frames = []

if path_type == "file":

content = read_file(path)

frames.append({

"type": "file",

"path": str(path),

"size_bytes": path.stat().st_size,

"sha256": file_sha256(path),

"content_snippet": content[:1024] # Vorschau

})

elif path_type == "dir":

for f in path.rglob("*"):

if f.is_file():

content = read_file(f)

frames.append({

"type": "file",

"path": str(f),

"size_bytes": f.stat().st_size,

"sha256": file_sha256(f),

"content_snippet": content[:1024]

})

return frames

def process_url_path(url_path_info):

"""Einlesen von URLs, optional rekursiv"""

url = url_path_info["path"]

html = read_url(url)

frames = []

if not html.startswith("ERROR"):

frames.append({

"type": "url",

"url": url,

"content_snippet": html[:2048] # Vorschau

})

# Option: Links extrahieren für Multipass-Crawl

links = extract_links(html, url)

for l in links:

html_link = read_url(l)

if not html_link.startswith("ERROR"):

frames.append({

"type": "url",

"url": l,

"content_snippet": html_link[:2048]

})

else:

frames.append({"type": "url", "url": url, "error": html})

return frames

# ---------------------------

# Hauptlogik Multipass

# ---------------------------

def main():

print("[*] Starte Deep-Read Multipass...")

try:

with open(PREPARE_REPORT, "r") as f:

prepare_report = json.load(f)

except Exception as e:

print(f"[!] Fehler beim Laden des Prepare Reports: {e}")

return

deepread_frames = []

for idx, frame_info in enumerate(prepare_report.get("deepread_ready", []), 1):

print(f"[*] Verarbeite Frame {idx}/{len(prepare_report['deepread_ready'])} ID: {frame_info.get('frame_id')}")

structure = frame_info.get("structure")

if not structure:

continue

if structure["type"] == "file" or structure["type"] == "dir":

frames = process_local_path(structure)

elif structure["type"] == "url":

frames = process_url_path(structure)

else:

continue

deepread_frames.extend(frames)

# Batch-write optional für große Datenmengen

if idx % BATCH_SIZE == 0:

with open(DEEPREAD_LEDGER, "a") as df:

for d in frames:

df.write(json.dumps(d) + "\n")

# Restliche Frames schreiben

with open(DEEPREAD_LEDGER, "a") as df:

for d in deepread_frames:

df.write(json.dumps(d) + "\n")

print(f"[*] Fertig. Deep-Read Multipass abgeschlossen.")

print(f"[*] Deep-Read Ledger gespeichert unter: {DEEPREAD_LEDGER}")

print(f"[*] Frames verarbeitet: {len(deepread_frames)}")

if __name__ == "__main__":

main()

Denke dein fehler liegt hier in deiner pfad angabe :

das sind die richtigen pfade :

ARCHIVE_PATH = Path("/home/iinkognit0/K501Gemini/99_Archive/")

LEDGER_PATH = "/K501GeminiNet/Node01/vault/ledger/frames.ndjson"

LIB_PATH = "/K501GeminiNet/core/libk501.so"

Doch hier falsch :

multipass_deepread_update.py

#!/usr/bin/env python3

import os

import json

import hashlib

from pathlib import Path

# --- Pfade ---

BASE_PATH = Path("/K501GeminiNet")

LEDGER_FILE = BASE_PATH / "Node01/vault/ledger/frames.ndjson"

REPAIRED_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_repaired.ndjson"

PREPARE_FILE = BASE_PATH / "Node01/vault/prepare_paths.json"

OUTPUT_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_updated.ndjson"

# --- Setup LLM & Algebra ---

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

llm = QH256LLM()

algebra = QH256Algebra(str(BASE_PATH / "core/libk501.so"))

# --- Hilfsfunktionen ---

def file_sha256(path):

h = hashlib.sha256()

with open(path, "rb") as f:

for chunk in iter(lambda: f.read(4096), b""):

h.update(chunk)

return h.hexdigest()

def generate_frame(source_path):

"""Generiert einen Frame aus Pfad oder URL."""

try:

if source_path.startswith("http://") or source_path.startswith("https://"):

import requests

resp = requests.get(source_path)

content = resp.text

else:

with open(source_path, "r", encoding="utf-8") as f:

content = f.read()

vector = llm.get_semantic_vector(content)[:32]

frame = {

"id": hashlib.sha256((source_path + str(vector)).encode()).hexdigest(),

"path": source_path,

"vector": vector,

"payload": content[:512],

"valid": True

}

return frame

except Exception as e:

return {"id": None, "path": source_path, "valid": False, "error": str(e)}

def load_existing_ids(*ledger_files):

"""Lädt alle existierenden Frame-IDs aus mehreren Ledger-Dateien."""

ids = set()

for ledger_file in ledger_files:

if ledger_file.exists():

with open(ledger_file, "r", encoding="utf-8") as f:

for line in f:

try:

frame = json.loads(line)

ids.add(frame["id"])

except:

continue

return ids

def load_paths_from_ledgers(*ledger_files):

"""Sammelt automatisch alle Pfade aus den übergebenen Ledger-Dateien."""

paths = []

for ledger_file in ledger_files:

if ledger_file.exists():

with open(ledger_file, "r", encoding="utf-8") as f:

for line in f:

try:

frame = json.loads(line)

if "path" in frame:

paths.append(frame["path"])

except:

continue

return list(set(paths)) # Duplikate entfernen

# --- Prepare JSON nur noch Backup ---

if not PREPARE_FILE.exists():

print(f"[INFO] {PREPARE_FILE} existiert nicht. Leere JSON erzeugen...")

os.makedirs(os.path.dirname(PREPARE_FILE), exist_ok=True)

with open(PREPARE_FILE, "w", encoding="utf-8") as f:

json.dump({}, f, indent=4)

print(f"[INFO] {PREPARE_FILE} wurde erstellt.")

else:

print(f"[INFO] {PREPARE_FILE} existiert bereits.")

# --- Multipass Deep Read ---

def multipass_deep_read():

print("[*] Starte Multipass Deep Read mit Integration reparierter Frames...")

# --- Bestehende IDs laden ---

existing_ids = load_existing_ids(LEDGER_FILE, REPAIRED_LEDGER)

print(f"[*] Gefundene existierende Frames (Ledger + Repaired): {len(existing_ids)}")

# --- Alle Pfade automatisch aus Ledger und reparierten Ledger-Dateien sammeln ---

sources = load_paths_from_ledgers(LEDGER_FILE, REPAIRED_LEDGER)

if not sources:

# Fallback auf prepare_paths.json

with open(PREPARE_FILE, "r", encoding="utf-8") as f:

sources = list(json.load(f).keys())

if not sources:

print("[WARN] Keine Pfade gefunden. Multipass Deep Read beendet.")

return

updated_count = 0

with open(OUTPUT_LEDGER, "a", encoding="utf-8") as out_f:

for src in sources:

frame = generate_frame(src)

if frame.get("id") and frame["id"] not in existing_ids:

out_f.write(json.dumps(frame) + "\n")

updated_count += 1

print(f"[*] Multipass Deep Read abgeschlossen. Neue Frames hinzugefügt: {updated_count}")

print(f"[*] Ledger aktualisiert: {OUTPUT_LEDGER}")

if __name__ == "__main__":

multipass_deep_read()