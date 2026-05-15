#!/usr/bin/env python3

import os

import json

import hashlib

from pathlib import Path

# Konfiguration

BASE_PATH = "/K501GeminiNet"

LEDGER_FILE = Path(BASE_PATH) / "Node01/vault/ledger/frames.ndjson"

OUTPUT_FILE = Path(BASE_PATH) / "diagnose_report.json"

# Hilfsfunktionen

def file_sha256(path):

h = hashlib.sha256()

try:

with open(path, "rb") as f:

for chunk in iter(lambda: f.read(4096), b""):

h.update(chunk)

return h.hexdigest()

except Exception as e:

return f"ERROR: {e}"

def collect_file_info(path: Path):

try:

size = path.stat().st_size

sha = file_sha256(path)

return {

"path": str(path),

"size_bytes": size,

"sha256": sha,

"exists": path.exists()

}

except Exception as e:

return {

"path": str(path),

"error": str(e)

}

# Diagnose-Funktionen

def scan_directory(base_path):

files_info = []

for path in Path(base_path).rglob("*"):

if path.is_file():

files_info.append(collect_file_info(path))

return files_info

def analyze_ledger(ledger_path):

frames_info = []

if not ledger_path.exists():

return {"error": "Ledger file not found"}

try:

with open(ledger_path, "r") as f:

for line_num, line in enumerate(f, start=1):

if not line.strip():

continue

try:

frame = json.loads(line)

frame_valid = all(k in frame for k in ["id", "prev_hash", "vector", "payload"])

frames_info.append({

"line": line_num,

"frame_id": frame.get("id"),

"prev_hash": frame.get("prev_hash"),

"valid": frame_valid,

"vector_len": len(frame.get("vector", [])),

"payload_len": len(frame.get("payload", "")),

})

except json.JSONDecodeError:

frames_info.append({

"line": line_num,

"error": "JSONDecodeError"

})

return frames_info

except Exception as e:

return {"error": str(e)}

def main():

print("[*] Starte K501 GeminiNet Diagnose...")

# 1. Ordner- und Dateistruktur scannen

print("[*] Scanne Dateisystem...")

files_info = scan_directory(BASE_PATH)

# 2. Ledger analysieren

print("[*] Analysiere Ledger...")

ledger_info = analyze_ledger(LEDGER_FILE)

# 3. Zusammenfassung

report = {

"base_path": BASE_PATH,

"total_files": len(files_info),

"files": files_info,

"ledger_file": str(LEDGER_FILE),

"ledger_frames": ledger_info

}

# 4. Output schreiben

with open(OUTPUT_FILE, "w") as out_f:

json.dump(report, out_f, indent=2)

print(f"[*] Diagnose abgeschlossen. Report geschrieben: {OUTPUT_FILE}")

if __name__ == "__main__":

main()