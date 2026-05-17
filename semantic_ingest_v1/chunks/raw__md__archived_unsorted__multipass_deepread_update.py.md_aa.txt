#!/usr/bin/env python3

import os

import json

import hashlib

from pathlib import Path

import time

# ---------------------------

# Pfad-Konfiguration

# ---------------------------

ARCHIVE_PATH = Path("/home/iinkognit0/K501Gemini/99_Archive/")

BASE_PATH = Path("/K501GeminiNet")

LEDGER_FILE = BASE_PATH / "Node01/vault/ledger/frames.ndjson"

REPAIRED_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_repaired.ndjson"

OUTPUT_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_updated.ndjson"

PREPARE_FILE = BASE_PATH / "Node01/vault/prepare_paths.json"

BATCH_SIZE = 50 # Batchgröße für IO

VECTOR_SLICE = 32 # Slice-Länge für LLM Vektor

# ---------------------------

# Module laden

# ---------------------------

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

llm = QH256LLM()

algebra = QH256Algebra(str(BASE_PATH / "core/libk501.so"))

# ---------------------------

# Hilfsfunktionen

# ---------------------------

def file_sha256(path: Path):

h = hashlib.sha256()

with open(path, "rb") as f:

for chunk in iter(lambda: f.read(4096), b""):

h.update(chunk)

return h.hexdigest()

def generate_frame(source_path: str):

"""Generiert einen Frame aus lokalem Pfad oder URL."""

try:

if source_path.startswith(("http://", "https://")):

import requests

resp = requests.get(source_path, timeout=10)

content = resp.text

else:

with open(source_path, "r", encoding="utf-8", errors="ignore") as f:

content = f.read()

vector = llm.get_semantic_vector(content)[:VECTOR_SLICE]

frame_id = hashlib.sha256((source_path + str(vector)).encode()).hexdigest()

return {

"id": frame_id,

"path": source_path,

"vector": vector,

"payload": content[:512],

"valid": True

}

except Exception as e:

return {"id": None, "path": source_path, "valid": False, "error": str(e)}

def load_existing_ids(*ledger_files):

ids = set()

for ledger_file in ledger_files:

if ledger_file.exists():

with open(ledger_file, "r", encoding="utf-8") as f:

for line in f:

try:

frame = json.loads(line)

if "id" in frame:

ids.add(frame["id"])

except:

continue

return ids

def load_paths_from_ledgers(*ledger_files):

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

# ---------------------------

# Multipass Deep Read

# ---------------------------

def multipass_deep_read():

print("[*] Starte Multipass Deep Read mit Integration reparierter Frames...")

# Bestehende Frame-IDs laden

existing_ids = load_existing_ids(LEDGER_FILE, REPAIRED_LEDGER)

print(f"[*] Gefundene existierende Frames (Ledger + Repaired): {len(existing_ids)}")

# Alle Pfade aus Ledger und Repaired sammeln

sources = load_paths_from_ledgers(LEDGER_FILE, REPAIRED_LEDGER)

# Fallback auf prepare_paths.json

if not sources and PREPARE_FILE.exists():

with open(PREPARE_FILE, "r", encoding="utf-8") as f:

sources = list(json.load(f).keys())

# Fallback auf komplettes Archiv

if not sources:

print("[INFO] Keine Pfade in Ledger/Prepare JSON. Scanne Archivverzeichnis...")

sources = [str(f) for f in ARCHIVE_PATH.rglob("*") if f.is_file()]

if not sources:

print("[WARN] Keine Quellen gefunden. Multipass Deep Read beendet.")

return

print(f"[*] Quellen zum Einlesen: {len(sources)}")

updated_count = 0

batch = []

start_time = time.time()

for idx, src in enumerate(sources, 1):

frame = generate_frame(src)

if frame.get("id") and frame["id"] not in existing_ids:

batch.append(frame)

existing_ids.add(frame["id"])

updated_count += 1

elif not frame.get("valid"):

print(f"[WARN] Ungültiger Frame: {src} | Fehler: {frame.get('error')}")

# Batch schreiben

if len(batch) >= BATCH_SIZE:

with open(OUTPUT_LEDGER, "a", encoding="utf-8") as out_f:

for f in batch:

out_f.write(json.dumps(f) + "\n")

batch = []

if idx % 50 == 0:

print(f" [>] {idx}/{len(sources)} Quellen verarbeitet...")

# Restliche Frames schreiben

if batch:

with open(OUTPUT_LEDGER, "a", encoding="utf-8") as out_f:

for f in batch:

out_f.write(json.dumps(f) + "\n")

total_time = time.time() - start_time

print(f"[*] Multipass Deep Read abgeschlossen. Neue Frames hinzugefügt: {updated_count}")

print(f"[*] Ledger aktualisiert: {OUTPUT_LEDGER}")

print(f"[*] Gesamtzeit: {total_time:.2f}s")

if __name__ == "__main__":

multipass_deep_read()