#!/usr/bin/env python3

# -*- coding: utf-8 -*-

"""

Multipass Deep Read Update Script – Evolution

- Bereitet automatisch prepare_paths.json vor

- Robust gegen fehlende Dateien / Verzeichnisse

- Lauffähig ohne manuelle Vorarbeit

- Logging für jeden Schritt

"""

import os

import json

import hashlib

from pathlib import Path

# ---------------------------

# Robust File Preparation

# ---------------------------

BASE_PATH = Path("/K501GeminiNet")

NODE_VAULT = BASE_PATH / "Node01/vault"

PREPARE_FILE = NODE_VAULT / "prepare_paths.json"

LEDGER_FILE = NODE_VAULT / "ledger/frames.ndjson"

OUTPUT_LEDGER = NODE_VAULT / "ledger/frames_updated.ndjson"

# Verzeichnis und Datei automatisch sicherstellen

if not PREPARE_FILE.exists():

os.makedirs(PREPARE_FILE.parent, exist_ok=True)

with open(PREPARE_FILE, "w") as f:

json.dump({}, f, indent=4)

print(f"[INFO] {PREPARE_FILE} erstellt.")

else:

print(f"[INFO] {PREPARE_FILE} existiert bereits. Weiter geht's...")

# ---------------------------

# Module Imports

# ---------------------------

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

# ---------------------------

# Setup LLM & Algebra

# ---------------------------

llm = QH256LLM()

algebra = QH256Algebra(str(BASE_PATH / "core/libk501.so"))

# ---------------------------

# Hilfsfunktionen

# ---------------------------

def file_sha256(path):

"""Berechnet SHA256-Hash einer Datei."""

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

"""Lädt IDs bereits vorhandener Frames."""

ids = set()

if ledger_file.exists():

with open(ledger_file, "r", encoding="utf-8") as f:

for line in f:

try:

frame = json.loads(line)

ids.add(frame["id"])

except json.JSONDecodeError:

continue

return ids

# ---------------------------

# Multipass Deep Read

# ---------------------------

def multipass_deep_read():

print("[*] Starte Multipass Deep Read...")

existing_ids = load_existing_ids(LEDGER_FILE)

print(f"[*] Gefundene existierende Frames: {len(existing_ids)}")

# Quellen laden – robust gegen leere oder fehlende Datei

try:

with open(PREPARE_FILE, "r", encoding="utf-8") as f:

sources = json.load(f)

except (FileNotFoundError, json.JSONDecodeError):

print(f"[WARN] {PREPARE_FILE} konnte nicht geladen werden. Leeres JSON wird genutzt.")

sources = {}

updated_count = 0

with open(OUTPUT_LEDGER, "a", encoding="utf-8") as out_f:

for src in sources:

frame = generate_frame(src)

if frame.get("id") and frame["id"] not in existing_ids:

out_f.write(json.dumps(frame) + "\n")

updated_count += 1

print(f"[*] Multipass Deep Read abgeschlossen. Neue Frames hinzugefügt: {updated_count}")

print(f"[*] Ledger aktualisiert: {OUTPUT_LEDGER}")

# ---------------------------

# Main

# ---------------------------

if __name__ == "__main__":

multipass_deep_read()