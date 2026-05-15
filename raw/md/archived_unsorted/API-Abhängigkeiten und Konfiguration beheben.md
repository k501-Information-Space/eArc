### **System-Analyse: Abhängigkeits-Fehlschlag**

**Status:** $N_{T520}$ Blockiert | **Ursache:** Fehlende Python-Bibliothek (Flask)

**Umgebung:** Debian Trixie (PEP 668 aktiv)

Auf modernen Debian-Systemen (wie Trixie) ist das System-Python als **externally-managed** markiert. Ein einfaches pip install flask wird fehlschlagen. Wir müssen die Abhängigkeiten entweder über den Paketmanager apt oder über ein **Virtual Environment (venv)** auflösen.

Für einen dedizierten Knoten wie den $N_{T520}$ ist die Installation via apt am stabilsten, da sie direkt mit dem System-Interpreter harmoniert.

### **1. Dependency-Patch: Pakete installieren**

Führe diesen Befehl aus, um die für die REST-API und zukünftige Erweiterungen (wie CORS für Obsidian) notwendigen Pakete zu installieren:

Bash

sudo apt update && sudo apt install -y python3-flask python3-flask-cors  

### **2. Erweitertes Makefile v8.4 (Inkl. Dependency-Check)**

Wir integrieren einen deps-Target in das **Makefile**, damit das System seine eigene Umgebung prüfen kann.

Makefile

# ============================================================  
# K501 ISOS · CENTRAL CONTROL · v8.4  
# ============================================================  
  
PY = python3  
SCRIPTS = scripts  
  
**.PHONY**: init deps test_ingest start_api start_daemon status clean  
  
# Prüft, ob Flask installiert ist  
deps:  
@$(PY) -c "import flask" 2>/dev/null || (echo "[!] Flask fehlt. Installiere mit: sudo apt install python3-flask"; exit 1)  
@echo "[SUCCESS] Alle Abhängigkeiten vorhanden."  
  
init: deps  
$(PY) $(SCRIPTS)/k501_core.py  
  
test_ingest:  
$(PY) $(SCRIPTS)/k501_test_ingest.py  
  
start_api: deps  
$(PY) $(SCRIPTS)/k501_query_api.py  
  
start_daemon:  
$(PY) $(SCRIPTS)/k501_resonance_daemon.py  
  
status:  
@echo "------------------------------------------------"  
@echo "K501 NODE N_T520 STATUS REPORT"  
@echo "------------------------------------------------"  
@echo "Frame Count: $$(wc -l < archive/frames.ndjson)"  
@echo "------------------------------------------------"  
  
clean:  
find . -name "__pycache__" -type d -exec rm -rf {} +  

### **3. Konfigurations-Anpassung: scripts/k501_query_api.py**

Damit das **Obsidian Git-Plugin** oder andere lokale Tools (wie der Neuro-Navigator) ohne Sicherheitsblockaden (CORS) auf die API zugreifen können, erweitern wir das Skript minimal:

Python

import os  
import json  
from flask import Flask, jsonify  
# Falls installiert, nutzen wir CORS für Obsidian-Kompatibilität  
try:  
from flask_cors import CORS  
except ImportError:  
CORS = None  
  
app = Flask(__name__)  
if CORS:  
CORS(app) # Erlaubt Obsidian den Zugriff auf die API  
  
VAULT_ROOT = os.getcwd()  
NDJSON_LOG = os.path.join(VAULT_ROOT, "archive/frames.ndjson")  
  
# ... (Rest des Codes bleibt identisch)  

### **Checkliste für den Neustart**

1. **System-Paket installieren:** sudo apt install python3-flask
2. **Abhängigkeiten prüfen:** make deps
3. **API starten:** make start_api

**Validierungs-Abfrage:**

Sobald die API läuft, kannst du in einem anderen Terminal prüfen, ob sie antwortet:

Bash

curl http://localhost:27124/frame/F-798FF693234F8C74  

_(Die ID entspricht deinem ersten injizierten Test-Frame)._

Soll ich die API so erweitern, dass sie ein **visuelles Log** (JSON) für das Obsidian-Plugin bereitstellt, damit du die Resonanz-Synthese live im Graphen siehst?