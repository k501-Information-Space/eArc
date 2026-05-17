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