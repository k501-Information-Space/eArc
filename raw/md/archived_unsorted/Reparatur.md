/K501GeminiNet/Node01/vault/ledger/repair_frames.py

#!/usr/bin/env python3

import json

from pathlib import Path

import shutil

import hashlib

# === Konfiguration ===

BASE_PATH = Path("/K501GeminiNet/Node01/vault/ledger")

LEDGER_FILE = BASE_PATH / "frames.ndjson"

BACKUP_FILE = BASE_PATH / "frames_backup.ndjson"

REPAIRED_FILE = BASE_PATH / "frames_repaired.ndjson"

INVALID_FRAMES_FILE = BASE_PATH / "frames_invalid.ndjson"

REPAIR_HASH = True # Wenn True, werden ungültige Hashes automatisch korrigiert

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

"""Validierung: Hash korrekt, Vector-Länge = 32, Payload vorhanden"""

if "hash" not in frame or "vector" not in frame or "payload" not in frame:

return False

if len(frame["vector"]) != 32:

return False

return compute_hash(frame) == frame["hash"]

# === Backup erstellen ===

shutil.copy2(LEDGER_FILE, BACKUP_FILE)

print(f"[*] Backup erstellt: {BACKUP_FILE.name}")

# === Ledger einlesen ===

with open(LEDGER_FILE, "r", encoding="utf-8") as f:

lines = f.readlines()

frames = [json.loads(line) for line in lines if line.strip()]

repaired_frames = []

invalid_frames = []

# === Prüfen und optional reparieren ===

for idx, frame in enumerate(frames):

valid = is_valid_frame(frame)

if not valid:

print(f"[!] Ungültiger Frame: Zeile {idx+1}, Dateiname: {frame.get('path', 'Unknown')}")

invalid_frames.append(frame)

if REPAIR_HASH:

frame["hash"] = compute_hash(frame)

print(f"[+] Frame Zeile {idx+1} Hash neu gesetzt.")

repaired_frames.append(frame)

# === Repaired Ledger schreiben ===

with open(REPAIRED_FILE, "w", encoding="utf-8") as f:

for frame in repaired_frames:

json.dump(frame, f)

f.write("\n")

# === Invalid Frames separat speichern ===

if invalid_frames:

with open(INVALID_FRAMES_FILE, "w", encoding="utf-8") as f:

for frame in invalid_frames:

json.dump(frame, f)

f.write("\n")

print(f"[*] Ungültige Frames separat gespeichert: {INVALID_FRAMES_FILE.name}")

else:

print("[*] Keine ungültigen Frames gefunden.")

print(f"[*] Repaired Ledger geschrieben: {REPAIRED_FILE.name}")

print("[*] Fertig. Backup bleibt erhalten, Repair abgeschlossen.")