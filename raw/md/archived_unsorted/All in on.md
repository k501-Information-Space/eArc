# ============================================================

# FILENAME: scripts/k501_master_migrate_gemini_final.py

# PURPOSE: Final-Freeze End-to-End Migration & Auto-Load for Gemini

# - Live-Progress-Bar

# - Parallel Frame Ingestion (ThreadPool)

# - ResonanceDaemon Init

# - Audit Report + Gemini QAL JSON

# ============================================================

import os

import json

import hashlib

from datetime import datetime

from concurrent.futures import ThreadPoolExecutor, as_completed

from tqdm import tqdm

from k501_core import Frame, append_to_ledger, Gemini, ResonanceDaemon

# -----------------------------

# CONFIGURATION

# -----------------------------

ARCHIVE_PATH = os.path.expanduser("~/K501_Vault/03_Archive")

MIGRATION_TAG = "LegacyArchive"

GEMINI_OUTPUT_PATH = os.path.expanduser("~/K501_Vault/archive/migration_gemini.json")

MAX_WORKERS = 8 # ThreadPool parallelism

# -----------------------------

# HELPER FUNCTION

# -----------------------------

def process_file(fpath, fname):

"""Erzeugt Frame, injiziert ins Ledger, gibt Frame-Dict zurück."""

try:

with open(fpath, "r", encoding="utf-8") as f:

content = f.read()

except Exception as e:

return None, f"[!] Skipping {fname}: {e}"

frame = Frame(

payload={"filename": fname, "content": content},

frame_type="RAW",

tags=[MIGRATION_TAG],

edges=[]

)

append_to_ledger(frame)

return frame.to_dict(), None

# -----------------------------

# STEP 1: Discover Files

# -----------------------------

all_files = []

for root, dirs, files in os.walk(ARCHIVE_PATH):

for fname in files:

all_files.append(os.path.join(root, fname))

total_files = len(all_files)

print(f"[*] Found {total_files} files in {ARCHIVE_PATH}")

# -----------------------------

# STEP 2: Parallel Migration

# -----------------------------

gemini_frames = []

errors = []

with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:

futures = {executor.submit(process_file, fpath, os.path.basename(fpath)): fpath for fpath in all_files}

for future in tqdm(as_completed(futures), total=total_files, desc="Migrating Frames"):

frame_dict, err = future.result()

if frame_dict:

gemini_frames.append(frame_dict)

if err:

errors.append(err)

count = len(gemini_frames)

print(f"[*] Migration complete: {count} Frames")

if errors:

print(f"[!] {len(errors)} files skipped due to errors.")

# -----------------------------

# STEP 3: Audit & QuantumRoot

# -----------------------------

hashes = [f['payload_hash'] for f in gemini_frames]

qr_hash = hashlib.sha256("".join(hashes).encode()).hexdigest()

epoch = int(datetime.now().timestamp())

print(f"[*] QuantumRoot: {qr_hash}, Epoch: {epoch}")

# -----------------------------

# STEP 4: Gemini Auto-Load

# -----------------------------

print("[*] Initializing Gemini instance...")

gemini = Gemini()

resonance = ResonanceDaemon(gemini)

print(f"[*] Loading {count} frames into Gemini")

for frame_dict in tqdm(gemini_frames, desc="Ingesting Frames"):

gemini.ingest_frame(frame_dict)

print("[*] Starting ResonanceDaemon (Ledger sync)...")

resonance.start(sync=True)

status = gemini.status()

print(f"[*] Gemini Status: {status}")

# -----------------------------

# STEP 5: Export Gemini QAL JSON

# -----------------------------

os.makedirs(os.path.dirname(GEMINI_OUTPUT_PATH), exist_ok=True)

with open(GEMINI_OUTPUT_PATH, "w", encoding="utf-8") as gf:

json.dump({

"epoch": epoch,

"quantum_root": qr_hash,

"frame_count": count,

"frames": gemini_frames

}, gf, indent=2)

print(f"[*] Gemini QAL Output written to: {GEMINI_OUTPUT_PATH}")

print("[*] Final-Freeze End-to-End Migration & Auto-Load completed successfully.")