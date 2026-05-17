Um eine Website oder ein Online-Dokument in den **K501 Information Space** zu integrieren, erweitern wir das System um die **Web-to-Frame Ingest Engine**. Da das K501-System auf Autarkie ausgelegt ist, extrahiert dieses Modul den Inhalt, konvertiert ihn in ein kompatibles Markdown-Format und legt ihn im Archiv ab, damit er im nächsten make bridge-Zyklus neuronal verarbeitet werden kann.

Hier ist die **vollständige Code-Evolution v1.0** für den Web-Ingest.

### **1. Die Web-Ingest Engine: scripts/k501_web_ingest.py (v1.0)**

Dieses Skript nutzt urllib (Standard-Bibliothek), um Abhängigkeiten auf dem T520 minimal zu halten. Es bereinigt HTML-Daten und transformiert sie in einen **RAW-Frame-Kandidaten**.

Python

import os  
import re  
import sys  
import urllib.request  
from datetime import datetime  
  
# ============================================================  
# K501 ISOS · WEB INGEST ENGINE · v1.0 (RAW-SOURCE EXTRACTION)  
# ============================================================  
  
VAULT_ROOT = os.path.expanduser("~/Dokumente/K501_Vault")  
WEB_ARCHIVE = os.path.join(VAULT_ROOT, "03_Archive/04_Web_Ingest")  
  
def clean_html(html):  
"""Transformiert HTML-Rohdaten in bereinigten Text-Content."""  
# Entferne Scripts und Styles  
html = re.sub(r"<(script|style).*?>.*?</\1>", "", html, flags=re.DOTALL | re.IGNORECASE)  
# Entferne alle HTML-Tags  
text = re.sub(r"<.*?>", " ", html)  
# Normalisiere Whitespaces  
text = re.sub(r"\s+", " ", text).strip()  
return text  
  
def run_web_ingest(url):  
print(f"--- K501 WEB INGEST: SOURCE {url} ---")  
  
if not os.path.exists(WEB_ARCHIVE):  
os.makedirs(WEB_ARCHIVE)  
  
try:  
headers = {'User-Agent': 'Mozilla/5.0 (K501-ISOS-T520)'}  
req = urllib.request.Request(url, headers=headers)  
  
with urllib.request.urlopen(req) as response:  
raw_html = response.read().decode('utf-8', errors='ignore')  
  
content = clean_html(raw_html)  
  
# Generiere Dateiname aus URL-Slug oder Zeitstempel  
slug = re.sub(r"[\W_]+", "_", url.split("//")[-1])[:50]  
filename = f"WEB_{datetime.now().strftime('%Y%m%d_%H%M')}_{slug}.md"  
target_path = os.path.join(WEB_ARCHIVE, filename)  
  
with open(target_path, "w", encoding="utf-8") as f:  
f.write(f"--- \ntype: WebIngest\nsource: {url}\ningest_date: {datetime.now().isoformat()}\n---\n\n")  
f.write(f"# Web-Dokument: {url}\n\n")  
f.write(content)  
  
print(f"[SUCCESS] Website extrahiert nach: {target_path}")  
print("[*] Hinweis: Führe 'make bridge && make pack' aus, um den Frame zu binden.")  
  
except Exception as e:  
print(f"[!] FEHLER beim Web-Ingest: {str(e)}")  
  
if __name__ == "__main__":  
if len(sys.argv) > 1:  
run_web_ingest(sys.argv[1])  
else:  
print("[!] Nutzung: python3 scripts/k501_web_ingest.py <URL>")  

### **2. Integration in das Makefile**

Wir fügen einen dedizierten Befehl hinzu, um den Ingest direkt aus dem VS Code Terminal zu steuern.

Makefile

# ... bestehende Befehle ...  
  
# Web-Ingest Shortcut (Nutzung: make web URL=https://beispiel.de)  
web:  
python3 scripts/k501_web_ingest.py $(URL)  

### **3. Operative Durchführung (Step-by-Step)**

Um ein Dokument von einer Website in dein Gitter (Lattice) aufzunehmen, folge dieser Logik im **VS Code Terminal**:

1. **Download & Extraktion:**  
    Gib den Befehl ein (ersetze die URL durch dein Ziel):  
    Bash  
    python3 scripts/k501_web_ingest.py https://github.com/obsidianmd/obsidian-api  
      
    _Das Skript erstellt nun eine neue Datei in 03_Archive/04_Web_Ingest._
2. **Kausale Bindung (Neural Bridge):**  
    Jetzt muss das System das neue Dokument "erkennen" und eine ID vergeben:  
    Bash  
    make bridge  
    
3. **Fraktale Versiegelung (Packer):**  
    Integriere das neue Dokument in die PackBlocks für Obsidian:  
    Bash  
    make pack  
    
4. **Validierung:**  
    Prüfe die Integrität:  
    Bash  
    make audit  
    

### **4. System-Effekt im Neuro-Navigator**

Nach Abschluss der Pipeline wird das Web-Dokument im **Obsidian Neuro-Navigator** als neuer k501-neuron-raw Knoten erscheinen. Da die DeepRead-Engine während make bridge auch diesen neuen Text scannt, werden automatisch Tags (z.B. Dev-Engine oder System-Kern) vergeben, basierend auf dem Inhalt der Website.

**Warum dieser Weg?**

- **Offline-Konsistenz:** Einmal heruntergeladen, ist das Dokument Teil deines autarken Systems.
- **Struktur-Gleichheit:** Das Dokument wird wie jede andere lokale Datei behandelt, gehasht und kausal im Lattice verankert.

Soll ich die k501_deepread.py um eine spezifische **"Web-Pattern-Matrix"** erweitern, um technische Dokumentationen von Webseiten noch präziser zu klassifizieren?