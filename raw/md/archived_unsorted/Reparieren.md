#!/usr/bin/env python3

import json

from pathlib import Path

import shutil

import hashlib

# === Konfiguration ===

BASE_PATH = Path("/K501GeminiNet/Node01/vault/ledger")

LEDGER_FILE = BASE_PATH / "frames.ndjson"

BACKUP_FILE = BASE_PATH / "frames_backup.ndjson"

REPAIR_FILE = BASE_PATH / "frames_repaired.ndjson"

# === Hilfsfunktionen ===

def compute_hash(frame):

"""SHA256 Hash über Payload + Vector"""

h = hashlib.sha256()

payload = frame.get("payload", "")

vector = frame.get("vector", [])

h.update(payload.encode('utf-8'))

for v in vector:

h.update(float(v).hex().encode('utf-8'))

return h.hexdigest()

def is_valid_frame(frame):

"""Validierungslogik: Hash stimmt, Vector-Länge = 32, Payload existiert"""

if "hash" not in frame or "vector" not in frame or "payload" not in frame:

return False

if len(frame["vector"]) != 32:

return False

computed = compute_hash(frame)

return computed == frame["hash"]

# === Backup erstellen ===

shutil.copy2(LEDGER_FILE, BACKUP_FILE)

print(f"[*] Backup erstellt: {BACKUP_FILE}")

# === Ledger einlesen ===

with open(LEDGER_FILE, "r", encoding="utf-8") as f:

lines = f.readlines()

frames = [json.loads(line) for line in lines if line.strip()]

# === Identifikation der letzten 2 Frames ===

last_frames = frames[-2:]

print(f"[*] Letzte 2 Frames zur Prüfung: Indizes {len(frames)-2} und {len(frames)-1}")

# === Prüfen und Reparieren ===

repaired_frames = frames[:-2] # bisherige valide Frames

for i, frame in enumerate(last_frames):

idx = len(frames) - 2 + i

if not is_valid_frame(frame):

print(f"[!] Frame {idx} ungültig. Hash/Vector prüfen oder korrigieren.")

# Option 1: Hash neu berechnen und setzen

frame["hash"] = compute_hash(frame)

print(f"[+] Frame {idx} Hash neu gesetzt.")

repaired_frames.append(frame)

# === Repaired Ledger schreiben ===

with open(REPAIR_FILE, "w", encoding="utf-8") as f:

for frame in repaired_frames:

json.dump(frame, f)

f.write("\n")

print(f"[*] Repaired Ledger geschrieben: {REPAIR_FILE}")

print(f"[*] Fertig. Backup bleibt erhalten, Repair abgeschlossen.")