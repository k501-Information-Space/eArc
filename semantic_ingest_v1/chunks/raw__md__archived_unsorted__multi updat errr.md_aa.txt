#!/usr/bin/env python3

import os

import json

import hashlib

from pathlib import Path

# Prüfen, ob die Datei existiert

if not os.path.exists(PREPARE_FILE):

print(f"[INFO] {PREPARE_FILE} existiert nicht. Erstelle leeres JSON...")

# Stelle sicher, dass das Verzeichnis existiert

os.makedirs(os.path.dirname(PREPARE_FILE), exist_ok=True)

# Leere JSON-Datei erzeugen

with open(PREPARE_FILE, "w") as f:

json.dump({}, f, indent=4)

print(f"[INFO] {PREPARE_FILE} wurde erstellt.")

else:

print(f"[INFO] {PREPARE_FILE} existiert bereits. Weiter geht's...")

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

# Pfade

BASE_PATH = Path("/K501GeminiNet")

LEDGER_FILE = BASE_PATH / "Node01/vault/ledger/frames.ndjson"

PREPARE_FILE = BASE_PATH / "Node01/vault/prepare_paths.json"

OUTPUT_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_updated.ndjson"

# Setup LLM & Algebra

llm = QH256LLM()

algebra = QH256Algebra(str(BASE_PATH / "core/libk501.so"))

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

"payload": content[:512], # nur Auszug

"valid": True

}

return frame

except Exception as e:

return {"id": None, "path": source_path, "valid": False, "error": str(e)}

def load_existing_ids(ledger_file):

ids = set()

if ledger_file.exists():

with open(ledger_file, "r") as f:

for line in f:

try:

frame = json.loads(line)

ids.add(frame["id"])

except:

continue

return ids

def multipass_deep_read():

print("[*] Starte Multipass Deep Read...")

existing_ids = load_existing_ids(LEDGER_FILE)

print(f"[*] Gefundene existierende Frames: {len(existing_ids)}")

with open(PREPARE_FILE, "r") as f:

sources = json.load(f)

updated_count = 0

with open(OUTPUT_LEDGER, "a") as out_f:

for src in sources:

frame = generate_frame(src)

if frame.get("id") and frame["id"] not in existing_ids:

out_f.write(json.dumps(frame) + "\n")

updated_count += 1

print(f"[*] Multipass Deep Read abgeschlossen. Neue Frames hinzugefügt: {updated_count}")

print(f"[*] Ledger aktualisiert: {OUTPUT_LEDGER}")

if __name__ == "__main__":

multipass_deep_read()