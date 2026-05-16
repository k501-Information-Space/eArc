iinkognit0@K501:/K501GeminiNet$ sudo apt update

[sudo] Passwort für iinkognit0:

OK:1 http://security.debian.org/debian-security trixie-security InRelease

OK:2 http://deb.debian.org/debian trixie InRelease

Holen:3 http://deb.debian.org/debian trixie-updates InRelease [47,3 kB]

Holen:4 http://deb.debian.org/debian trixie-backports InRelease [54,0 kB]

OK:5 https://download.vscodium.com/debs vscodium InRelease

OK:6 https://packages.microsoft.com/repos/code stable InRelease

OK:7 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Es wurden 101 kB in 1 s geholt (120 kB/s).

Alle Pakete sind aktuell.

iinkognit0@K501:/K501GeminiNet$ #!/usr/bin/env python3

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

main()_ == "__main__":bgeschlossen. Report geschrieben: {OUTPUT_FILE}")", "

bash: from: Kommando nicht gefunden.

bash: BASE_PATH: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: try:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »chunk«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: except: Kommando nicht gefunden.

bash: return: fERROR: {e}: Ein numerischer Parameter ist erforderlich.

bash: return: »Return« ist nur aus einer Funktion oder einem mit »source« ausgeführten Skript möglich.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: try:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: return: {: Ein numerischer Parameter ist erforderlich.

bash: return: »Return« ist nur aus einer Funktion oder einem mit »source« ausgeführten Skript möglich.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: size_bytes:: Kommando nicht gefunden.

bash: sha256:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »}«

bash: except: Kommando nicht gefunden.

bash: return: {: Ein numerischer Parameter ist erforderlich.

bash: return: »Return« ist nur aus einer Funktion oder einem mit »source« ausgeführten Skript möglich.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »}«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: files_info: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »:«

bash: Syntaxfehler beim unerwarteten Symbol »collect_file_info«

bash: return: files_info: Ein numerischer Parameter ist erforderlich.

bash: return: »Return« ist nur aus einer Funktion oder einem mit »source« ausgeführten Skript möglich.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: frames_info: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: return: {error:: Ein numerischer Parameter ist erforderlich.

bash: return: »Return« ist nur aus einer Funktion oder einem mit »source« ausgeführten Skript möglich.

bash: try:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »line«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: continue: nur in einer for-, while- oder until-Schleife sinnvoll.

bash: try:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »{«

bash: line:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: valid:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »}«

bash: except: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »{«

bash: line:: Kommando nicht gefunden.

bash: error:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »}«

bash: return: frames_info: Ein numerischer Parameter ist erforderlich.

bash: return: »Return« ist nur aus einer Funktion oder einem mit »source« ausgeführten Skript möglich.

bash: except: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »"[*] Starte K501 GeminiNet Diagnose..."«

bash: Syntaxfehler beim unerwarteten Symbol »"[*] Scanne Dateisystem..."«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »"[*] Analysiere Ledger..."«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: report: Kommando nicht gefunden.

bash: base_path:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: files:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: ledger_frames:: Kommando nicht gefunden.

bash: Syntaxfehler beim unerwarteten Symbol »}«

bash: Syntaxfehler beim unerwarteten Symbol »(«

bash: Syntaxfehler beim unerwarteten Symbol »report,«

bash: Syntaxfehler beim unerwarteten Symbol »f"[*] Diagnose abgeschlossen. Report geschrieben: {OUTPUT_FILE}"«

>

> ^C