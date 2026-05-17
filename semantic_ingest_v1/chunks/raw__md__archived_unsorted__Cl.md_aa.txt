Alles klar. Hier ist das komplette k501_evolve.py Script – modular, robust, ready-to-run auf dem T520. Es erstellt die Zielstruktur, verschiebt die Dateien gemäß Inventur, prüft C-Dateien und erzeugt ein optionales Reporting.

#!/usr/bin/env python3

# -*- coding: utf-8 -*-

"""

k501_evolve.py

Hardcore-Streamline Migrations-Script

Aufgabe: Physische Organisation aller K501-Komponenten in sauberen Layern

Ready-to-run auf T520

"""

import os

import shutil

import subprocess

import json

from pathlib import Path

# === Konfiguration ===

ROOT_DIR = Path.cwd()

REPORT_FILE = ROOT_DIR / "k501_migration_report.json"

LAYER_FOLDERS = {

"core": [

"qh256.c",

"qh256_algebra.c",

"k501_frame.py",

"k501_core.py",

"k501-core.py",

"k501_quantum_packer.py"

],

"ingest": [

"k501_ingest.c",

"k501_ingest.py",

"k501_deepread.py",

"k501_deepread_parser.py",

"k501_master_migrate.py",

"k501_bridge_ingest.py",

"k501_web_ingest.py",

"k501_priority_ingest.py",

"k501_full_sync.py",

"get-docs.sh",

"k501_test_ingest.py"

],

"engine": [

"k501_resonance_daemon.py",

"k501_query_api.py",

"k501_neural_inference.py",

"k501_path_analyzer.py",

"k501_weave_tags.py",

"k501_discovery.py"

],

"interface": [

"k501_dashboard.py"

],

"audit": [

"k501_archive_scanner.c",

"k501_audit_engine.py",

"k501_audit_lattice.py",

"k501_stats.py",

"k501_top_check.py",

"k501_debug.c"

]

}

# === Hilfsfunktionen ===

def ensure_folder(path: Path):

if not path.exists():

path.mkdir(parents=True, exist_ok=True)

print(f"[MIGRATE] Ordner erstellt: {path}")

def move_file(src: Path, dst: Path):

if not src.exists():

print(f"[WARN] Datei nicht gefunden: {src}")

return False

if dst.exists():

# Backup bestehender Datei

dst_backup = dst.with_suffix(dst.suffix + ".bak")

shutil.move(str(dst), str(dst_backup))

print(f"[MIGRATE] Datei existiert, Backup erstellt: {dst_backup}")

shutil.move(str(src), str(dst))

print(f"[MIGRATE] Datei verschoben: {src} → {dst}")

return True

def check_c_file(file_path: Path):

if not file_path.exists():

return False, "Nicht gefunden"

# Einfache Kompilierungsprüfung

try:

result = subprocess.run(

["gcc", "-fsyntax-only", str(file_path)],

capture_output=True,

text=True

)

if result.returncode != 0:

return False, result.stderr.strip()

return True, "OK"

except Exception as e:

return False, str(e)

# === Migration ===

migration_report = {}

for layer, files in LAYER_FOLDERS.items():

folder_path = ROOT_DIR / layer

ensure_folder(folder_path)

migration_report[layer] = {"moved": [], "c_check": {}}

for file_name in files:

src_path = ROOT_DIR / file_name

dst_path = folder_path / file_name

moved = move_file(src_path, dst_path)

if moved:

migration_report[layer]["moved"].append(file_name)

# C-Dateien prüfen

if file_name.endswith(".c"):

ok, msg = check_c_file(dst_path)

migration_report[layer]["c_check"][file_name] = {"ok": ok, "msg": msg}

# === Reporting ===

with open(REPORT_FILE, "w", encoding="utf-8") as f:

json.dump(migration_report, f, indent=4)

print(f"[REPORT] Migrationsreport erstellt: {REPORT_FILE}")

print("[MIGRATE] Migration abgeschlossen. Alle Layer sind bereit für Code-Review & Aussortieren.")

Features / Highlights:

1. Erstellt alle Layer-Ordner (core, ingest, engine, interface, audit) automatisch.  
    
2. Verschiebt alle 30 Dateien gemäß funktionaler Rolle.  
    
3. Backup existierender Dateien mit .bak Endung, um Legacy-Drift zu vermeiden.  
    
4. Prüft alle .c Dateien auf Syntax/Compile-Fehler via gcc -fsyntax-only.  
    
5. Generiert einen JSON-Report k501_migration_report.json mit Status aller Dateien.  
    
6. Vollständig T520-kompatibel, nutzt nur Python-Standardbibliothek + GCC für C-Prüfung.  
    

Wenn du willst, kann ich im nächsten Schritt ein k501_post_migrate.py Script erstellen, das automatisch die JSON-LD Validatoren, Resonanz-Init und Chromium-Bridge Testläufe vorbereitet – quasi das Setup für die Hardcore-Streamline Phase.

Willst du, dass ich das vorbereite?