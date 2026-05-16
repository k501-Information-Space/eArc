# ============================================================

# FILENAME: scripts/k501_migrate_archive.py

# PURPOSE: Migration legacy archive -> v8.1 NDJSON Ledger

# OUTPUT: Gemini/QAL .json ready

# ============================================================

import os

import json

import hashlib

from datetime import datetime

from k501_core import Frame, append_to_ledger, NDJSON_LOG

# Pfad zum alten Archiv

ARCHIVE_PATH = os.path.expanduser("~/K501_Vault/03_Archive")

MIGRATION_TAG = "LegacyArchive"

# Sammlung für Gemini-Output

gemini_frames = []

# Zähler

count = 0

print(f"[*] Starting Migration from {ARCHIVE_PATH}")

for root, dirs, files in os.walk(ARCHIVE_PATH):

for fname in files:

fpath = os.path.join(root, fname)

try:

with open(fpath, "r", encoding="utf-8") as f:

content = f.read()

except Exception as e:

print(f"[!] Skipping {fname}: {e}")

continue

# Frame erzeugen

frame = Frame(

payload={"filename": fname, "content": content},

frame_type="RAW",

tags=[MIGRATION_TAG],

edges=[]

)

# Append-Only Ledger Injection

append_to_ledger(frame)

count += 1

# Für Gemini-Output

gemini_frames.append(frame.to_dict())

if count % 100 == 0:

print(f" [+] {count} Frames migrated...")

# Audit & QuantumRoot Berechnung

hashes = [f['payload_hash'] for f in gemini_frames]

qr_hash = hashlib.sha256("".join(hashes).encode()).hexdigest()

epoch = int(datetime.now().timestamp())

print(f"[*] Migration complete: {count} Frames")

print(f"[*] QuantumRoot: {qr_hash}")

print(f"[*] Epoch: {epoch}")

# Gemini Output

GEMINI_OUTPUT_PATH = os.path.expanduser("~/K501_Vault/archive/migration_gemini.json")

with open(GEMINI_OUTPUT_PATH, "w", encoding="utf-8") as gf:

json.dump({

"epoch": epoch,

"quantum_root": qr_hash,

"frame_count": count,

"frames": gemini_frames

}, gf, indent=2)

print(f"[*] Gemini QAL Output written to: {GEMINI_OUTPUT_PATH}")