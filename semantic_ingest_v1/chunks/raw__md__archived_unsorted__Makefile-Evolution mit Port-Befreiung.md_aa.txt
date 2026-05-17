Hier ist die **Evolution v9.7** deines Makefiles. Ich habe die „Port-Befreiung“ als festen Bestandteil integriert, damit du nie wieder manuell nach Prozess-IDs suchen musst.

Zusätzlich habe ich die Aliase so gesetzt, dass make top den neuen Reporter mit dem erhöhten Timeout aufruft.

### **Makefile · Evolution v9.7 (The "Force-Release" Edition)**

**Pfad:** ~/Dokumente/K501_Vault/Makefile

Makefile

# ============================================================  
# K501 MASTER MAKEFILE · v9.7  
# TARGET: N_T520 (Debian Trixie)  
# ============================================================  
  
PY = python3  
S = scripts  
LEDGER = archive/frames.ndjson  
PORT = 27124  
  
**.PHONY**: all init deps migrate start_api stop_api api top dash status clean  
  
all: status  
  
# --- Umgebung & Abhängigkeiten ---  
deps:  
@$(PY) -c "import flask, flask_cors, tqdm, numpy, networkx, matplotlib, requests" 2>/dev/null || (echo "[!] Abhängigkeiten fehlen. Bitte 'sudo apt install python3-flask python3-flask-cors python3-tqdm python3-numpy python3-networkx python3-matplotlib python3-requests' ausführen.")  
  
# --- Port-Management (Der "Häng-Killer") ---  
stop_api:  
@echo "[*] Befreie Port $(PORT)..."  
@fuser -k $(PORT)/tcp 2>/dev/null || echo "[ ] Port war bereits frei."  
  
# --- Operationelle Dienste ---  
  
# Startet die API sicher (killt alten Prozess vorher)  
start_api: stop_api deps  
@echo "[*] Starte K501 Query API v9.6 (Port $(PORT))..."  
$(PY) $(S)/k501_query_api.py  
  
api: start_api  
  
# Führt den Resonanz-Check mit Tabelle aus  
top: deps  
@echo "[*] Starte Resonanz-Reporter (Gedulds-Modus)..."  
$(PY) $(S)/k501_top_check.py  
  
# --- Daten & Gitter ---  
migrate: deps  
@echo "[*] Starte K501 Master Migration..."  
$(PY) $(S)/k501_master_migrate_gemini_final.py  
  
dash: deps  
@echo "[*] Initialisiere Topologie-Graph..."  
$(PY) $(S)/k501_dashboard.py  
  
status:  
@echo "------------------------------------------------"  
@echo "K501 STATUS REPORT (Node N_T520)"  
@echo "------------------------------------------------"  
@if [ -f $(LEDGER) ]; then \  
printf "Frames im Ledger: "; wc -l < $(LEDGER); \  
else \  
echo "Ledger leer. Bitte 'make migrate' ausführen."; \  
fi  
@echo "------------------------------------------------"  
  
clean:  
find . -name "__pycache__" -type d -exec rm -rf {} +  
@echo "[*] Cache bereinigt."  

### **So nutzt du das neue Power-Tool:**

1. **Wenn die API hängt oder der Port belegt ist:**  
    Tippe einfach make start_api. Das Makefile führt automatisch stop_api (den fuser-Befehl) aus, bevor es die neue Instanz startet.
2. **Wenn du die Ergebnisse sehen willst:**  
    Tippe make top. Das ruft dein neues scripts/k501_top_check.py auf.
3. **Wenn du mal „aufräumen“ willst:**  
    make stop_api reicht aus, um den Port für andere Anwendungen freizugeben.

**Nächster Schritt:**

Soll ich dir ein Modul für das Makefile bauen (z.B. make export), das die Top-Ergebnisse direkt in eine **Markdown-Datei für Obsidian** schreibt? Dann hättest du deine stärksten Gedanken-Resonanzen immer als Notiz griffbereit.