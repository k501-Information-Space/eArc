#!/usr/bin/env python3

import os

import json

from pathlib import Path

# ---------------------------

# Konfiguration

# ---------------------------

BASE_PATH = Path("/K501GeminiNet")

LEDGER_FILE = BASE_PATH / "Node01/vault/ledger/frames_repaired.ndjson"

OUTPUT_REPORT = BASE_PATH / "Node01/vault/ledger/deepread_prepare_report.json"

MISSING_DIR = BASE_PATH / "Node01/vault/ledger/missing_frames"

# Sicherstellen, dass Ordner für fehlende Frames existiert

MISSING_DIR.mkdir(parents=True, exist_ok=True)

# ---------------------------

# Hilfsfunktionen

# ---------------------------

def check_file_exists(frame):

"""Prüft, ob die referenzierte Datei im Frame existiert."""

try:

file_path = Path(frame.get("file_path", ""))

if not file_path.is_absolute():

file_path = BASE_PATH / file_path

exists = file_path.exists()

return exists, str(file_path)

except Exception as e:

return False, f"ERROR: {e}"

def prepare_deepread_structure(frame):

"""Legt die Basis-Struktur für Deep-Read vor."""

file_path = frame.get("file_path")

if file_path is None:

return None

# Wir können hier z.B. den Pfad normalisieren und alle Unterpfade listen

p = Path(file_path)

if not p.is_absolute():

p = BASE_PATH / p

# Nur existierende Pfade für Deep-Read

if not p.exists():

return None

if p.is_file():

return {"type": "file", "path": str(p)}

elif p.is_dir():

# Liste rekursiv alle Dateien

files = [str(f) for f in p.rglob("*") if f.is_file()]

return {"type": "dir", "path": str(p), "files": files}

return None

# ---------------------------

# Hauptlogik

# ---------------------------

def main():

print("[*] Starte Pfad-Integritäts- und Deep-Read-Vorbereitung...")

report = {"frames_checked": 0, "missing_files": [], "deepread_ready": []}

try:

with open(LEDGER_FILE, "r") as f:

for idx, line in enumerate(f, 1):

if not line.strip():

continue

try:

frame = json.loads(line)

except json.JSONDecodeError:

report["missing_files"].append({

"line": idx,

"error": "Invalid JSON",

"frame_raw": line.strip()

})

continue

report["frames_checked"] += 1

exists, abs_path = check_file_exists(frame)

if not exists:

report["missing_files"].append({

"line": idx,

"file_path": abs_path,

"frame_id": frame.get("id", "Unknown")

})

# Kopiere ungültige Frames für Review

missing_file_path = MISSING_DIR / f"frame_line_{idx}.json"

with open(missing_file_path, "w") as mf:

json.dump(frame, mf, indent=2)

deepread_info = prepare_deepread_structure(frame)

if deepread_info:

report["deepread_ready"].append({

"line": idx,

"frame_id": frame.get("id", "Unknown"),

"structure": deepread_info

})

except FileNotFoundError:

print(f"[!] Ledger Datei nicht gefunden: {LEDGER_FILE}")

return

except Exception as e:

print(f"[!] Fehler beim Verarbeiten des Ledgers: {e}")

return

# Report speichern

with open(OUTPUT_REPORT, "w") as out:

json.dump(report, out, indent=2)

print(f"[*] Fertig. Frames geprüft: {report['frames_checked']}")

print(f"[*] Fehlende Dateien: {len(report['missing_files'])}")

print(f"[*] Deep-Read-ready Frames: {len(report['deepread_ready'])}")

print(f"[*] Report gespeichert unter: {OUTPUT_REPORT}")

if __name__ == "__main__":

main()