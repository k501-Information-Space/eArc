#!/usr/bin/env python3

import os

import json

from pathlib import Path

from urllib.parse import urlparse

import requests

from bs4 import BeautifulSoup # Für HTML Parsing

import hashlib

# ---------------------------

# Konfiguration

# ---------------------------

BASE_PATH = Path("/K501GeminiNet")

PREPARE_REPORT = BASE_PATH / "Node01/vault/ledger/deepread_prepare_report.json"

DEEPREAD_LEDGER = BASE_PATH / "Node01/vault/ledger/frames_deepread.ndjson"

BATCH_SIZE = 20 # Für Multipass / Batch Processing

USER_AGENT = "K501-DeepRead/1.0"

# ---------------------------

# Hilfsfunktionen

# ---------------------------

def file_sha256(path: Path):

h = hashlib.sha256()

with open(path, "rb") as f:

for chunk in iter(lambda: f.read(4096), b""):

h.update(chunk)

return h.hexdigest()

def read_file(path: Path):

try:

with open(path, "r", encoding="utf-8") as f:

return f.read()

except Exception as e:

return f"ERROR: {e}"

def read_url(url: str):

try:

headers = {"User-Agent": USER_AGENT}

r = requests.get(url, headers=headers, timeout=10)

r.raise_for_status()

return r.text

except Exception as e:

return f"ERROR: {e}"

def extract_links(html: str, base_url: str):

"""Extrahiert relative und absolute Links für rekursives Crawlen"""

soup = BeautifulSoup(html, "html.parser")

links = set()

for a in soup.find_all("a", href=True):

href = a["href"]

parsed = urlparse(href)

if parsed.scheme in ["http", "https"]:

links.add(href)

elif href.startswith("/"):

# Relativer Pfad → absolut

parsed_base = urlparse(base_url)

links.add(f"{parsed_base.scheme}://{parsed_base.netloc}{href}")

return list(links)

def process_local_path(path_info):

"""Rekursives Einlesen lokaler Dateien"""

path_type = path_info["type"]

path = Path(path_info["path"])

frames = []

if path_type == "file":

content = read_file(path)

frames.append({

"type": "file",

"path": str(path),

"size_bytes": path.stat().st_size,

"sha256": file_sha256(path),

"content_snippet": content[:1024] # Vorschau

})

elif path_type == "dir":

for f in path.rglob("*"):

if f.is_file():

content = read_file(f)

frames.append({

"type": "file",

"path": str(f),

"size_bytes": f.stat().st_size,

"sha256": file_sha256(f),

"content_snippet": content[:1024]

})

return frames

def process_url_path(url_path_info):

"""Einlesen von URLs, optional rekursiv"""

url = url_path_info["path"]

html = read_url(url)

frames = []

if not html.startswith("ERROR"):

frames.append({

"type": "url",

"url": url,

"content_snippet": html[:2048] # Vorschau

})

# Option: Links extrahieren für Multipass-Crawl

links = extract_links(html, url)

for l in links:

html_link = read_url(l)

if not html_link.startswith("ERROR"):

frames.append({

"type": "url",

"url": l,

"content_snippet": html_link[:2048]

})

else:

frames.append({"type": "url", "url": url, "error": html})

return frames

# ---------------------------

# Hauptlogik Multipass

# ---------------------------

def main():

print("[*] Starte Deep-Read Multipass...")

try:

with open(PREPARE_REPORT, "r") as f:

prepare_report = json.load(f)

except Exception as e:

print(f"[!] Fehler beim Laden des Prepare Reports: {e}")

return

deepread_frames = []

for idx, frame_info in enumerate(prepare_report.get("deepread_ready", []), 1):

print(f"[*] Verarbeite Frame {idx}/{len(prepare_report['deepread_ready'])} ID: {frame_info.get('frame_id')}")

structure = frame_info.get("structure")

if not structure:

continue

if structure["type"] == "file" or structure["type"] == "dir":

frames = process_local_path(structure)

elif structure["type"] == "url":

frames = process_url_path(structure)

else:

continue

deepread_frames.extend(frames)

# Batch-write optional für große Datenmengen

if idx % BATCH_SIZE == 0:

with open(DEEPREAD_LEDGER, "a") as df:

for d in frames:

df.write(json.dumps(d) + "\n")

# Restliche Frames schreiben

with open(DEEPREAD_LEDGER, "a") as df:

for d in deepread_frames:

df.write(json.dumps(d) + "\n")

print(f"[*] Fertig. Deep-Read Multipass abgeschlossen.")

print(f"[*] Deep-Read Ledger gespeichert unter: {DEEPREAD_LEDGER}")

print(f"[*] Frames verarbeitet: {len(deepread_frames)}")

if __name__ == "__main__":

main()