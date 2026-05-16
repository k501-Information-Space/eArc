#!/usr/bin/env python3

# -*- coding: utf-8 -*-

"""

Multipass Deep Read – Auto-Ledger Edition

- Liest automatisch alle existierenden Frames im Ledger

- Kein prepare_paths.json notwendig

- Aktualisiert Vektoren / Hashes bei Änderungen

- Logging für jeden Schritt

"""

import os

import json

import hashlib

from pathlib import Path

# ---------------------------

# Pfade

# ---------------------------

BASE_PATH = Path("/K501GeminiNet")

NODE_VAULT = BASE_PATH / "Node01/vault"

LEDGER_FILE = NODE_VAULT / "ledger/frames.ndjson"

OUTPUT_LEDGER = NODE_VAULT / "ledger/frames_updated.ndjson"

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

def load_existing_ids_and_paths(ledger_file):

"""Lädt IDs und Pfade bereits vorhandener Frames."""

ids = set()

paths = []

if ledger_file.exists():

with open(ledger_file, "r", encoding="utf-8") as f:

for line in f:

try:

frame = json.loads(line)

ids.add(frame["id"])

paths.append(frame["path"])

except json.JSONDecodeError:

continue

return ids, paths

# ---------------------------

# Multipass Deep Read

# ---------------------------

def multipass_deep_read():

print("[*] Starte Multipass Deep Read – Auto-Ledger Version...")

existing_ids, sources = load_existing_ids_and_paths(LEDGER_FILE)

print(f"[*] Gefundene existierende Frames: {len(existing_ids)}")

if not sources:

print("[WARN] Keine Frames im Ledger gefunden. Nichts zu verarbeiten.")

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

# ---------------------------

# Main

# ---------------------------

if __name__ == "__main__":

multipass_deep_read()