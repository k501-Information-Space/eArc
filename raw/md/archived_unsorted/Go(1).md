#!/usr/bin/env python3

import os

import json

import hashlib

import time

from pathlib import Path

from tqdm import tqdm

# ---------------------------

# Pfade / Konfiguration

# ---------------------------

BASE_PATH = Path("/K501GeminiNet")

ARCHIVE_PATH = Path("/home/iinkognit0/K501Gemini/99_Archive/")

LEDGER_FILE = BASE_PATH / "Node01/vault/ledger/frames.ndjson"

REPAIRED_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_repaired.ndjson"

OUTPUT_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_updated.ndjson"

PREPARE_FILE = BASE_PATH / "Node01/vault/prepare_paths.json"

VECTOR_SLICE = 32

LLM_TIMEOUT = 60 # Sekunden

# ---------------------------

# Setup LLM & Algebra

# ---------------------------

from modules.QH256_Algebra.launch_algebra import QH256Algebra

from modules.QH256_LLM.launch_llm import QH256LLM

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

if str(source_path).startswith(("http://", "https://")):

import requests

resp = requests.get(str(source_path), timeout=LLM_TIMEOUT)

content = resp.text

else:

with open(source_path, "r", encoding="utf-8", errors="ignore") as f:

content = f.read()

vector = llm.get_semantic_vector(content)[:VECTOR_SLICE]

frame = {

"id": hashlib.sha256((str(source_path) + str(vector)).encode()).hexdigest(),

"path": str(source_path),

"vector": vector,

"payload": content[:512],

"valid": True

}

return frame

except Exception as e:

return {"id": None, "path": str(source_path), "valid": False, "error": str(e)}

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

return list(set(paths))

# ---------------------------

# Multipass Deep Read

# ---------------------------

def multipass_deep_read():

print("[*] Starte Multipass Deep Read mit Integration reparierter Frames...")

# Bestehende IDs laden

existing_ids = load_existing_ids(LEDGER_FILE, REPAIRED_LEDGER)

print(f"[*] Gefundene existierende Frames (Ledger + Repaired): {len(existing_ids)}")

# Alle Pfade sammeln

sources = load_paths_from_ledgers(LEDGER_FILE, REPAIRED_LEDGER)

if not sources and PREPARE_FILE.exists():

with open(PREPARE_FILE, "r", encoding="utf-8") as f:

sources = list(json.load(f).keys())

if not sources:

# Fallback: Archivverzeichnis

sources = [str(f) for f in ARCHIVE_PATH.rglob("*") if f.is_file()]

print(f"[*] Quellen zum Einlesen: {len(sources)}")

updated_count = 0

start_time = time.time()

with open(OUTPUT_LEDGER, "a", encoding="utf-8") as out_f:

for src in tqdm(sources, desc="DeepRead Multipass", unit="Frame"):

frame = generate_frame(src)

if frame.get("id") and frame["id"] not in existing_ids:

out_f.write(json.dumps(frame) + "\n")

updated_count += 1

total_time = time.time() - start_time

print(f"[*] Multipass Deep Read abgeschlossen.")

print(f"[*] Neue Frames hinzugefügt: {updated_count}")

print(f"[*] Ledger aktualisiert: {OUTPUT_LEDGER}")

print(f"[*] Gesamtzeit: {total_time:.2f}s, Durchschnitt: {total_time/max(1, updated_count):.2f}s pro Frame")

# ---------------------------

# Ausführung

# ---------------------------

if __name__ == "__main__":

multipass_deep_read()