### **🛰️ K501 ISOS · Technisches README v4.0**

**Systemstatus:** GEFROREN (ISO-STABIL) | **Datum:** 11. März 2026 | **Epoch:** 1773188800

Dieses Dokument ist die maßgebliche Betriebsanleitung für den **K501 NeuralNetwork InformationSpace**. Es beschreibt die Nutzung der hybriden Architektur (C/Python/JS) auf der T520-Hardware und definiert die Protokolle für Datensicherheit und kausale Evolution.

## **1. System-Konzept: Was ist K501?**

K501 ist ein **autopoietischer Informationsraum**. Im Gegensatz zu statischen Datenbanken erzeugt K501 durch den Akt der Beobachtung (Interpretation) neue strukturelle Frames, die untrennbar mit ihren Ursprungsdaten verknüpft sind.

- **Integrität:** Jeder Frame wird kryptographisch durch den C-Kernel (EVP-SHA256) validiert.
- **Struktur:** Daten werden in fraktalen **PackBlocks** (100 Einheiten) organisiert, um die Hardware-Ressourcen des i5-Prozessors zu schonen.
- **Kausalität:** Das System unterscheidet zwischen **RAW**-Daten (Importe/Web) und **OBS**-Daten (deine Beobachtungen).

## **2. Die operative Umgebung**

### **VS Code (Das Nervenzentrum)**

Hier finden alle schreibenden und strukturgebenden Operationen statt.

- **Terminal öffnen:** Strg + ö (oder Terminal -> New Terminal).
- **Skripte ausführen:**
    - Python: python3 scripts/dateiname.py
    - Bash: bash scripts/dateiname.sh

### **Obsidian (Das visuelle Interface)**

Hier findet die Exploration und Interpretation statt.

- **Neuro-Navigator:** Das Gehirn-Icon in der Ribbon-Leiste öffnet den kausalen Graphen.
- **Lattice-Einsicht:** Direkter Zugriff auf die PackBlocks in 02_QuantumLattice.

## **3. Der Operator-Workflow (Die Pipeline)**

Um neue Informationen (z. B. Web-Dokumente) vollständig zu integrieren, muss die folgende Kette im VS Code Terminal durchlaufen werden:

|**Schritt**|**Befehl**|**Wirkung**|
|---|---|---|
|**1. Ingest**|make web URL=...|Lädt externe Daten nach 03_Archive/04_Web_Ingest.|
|---|---|---|
|**2. Sync**|make sync|Der C-Kernel berechnet die physischen Hashes aller Dateien.|
|---|---|---|
|**3. Bridge**|make bridge|Die Neural Bridge vergibt IDs (F-xxxxx) und webt kausale Synapsen.|
|---|---|---|
|**4. Pack**|make pack|Kristallisiert die Frames in PackBlocks für Obsidian.|
|---|---|---|
|**5. Audit**|make audit|Verifiziert die Isomorphie zwischen Log und physischem Gitter.|
|---|---|---|

## **4. Makefile Referenz (Kommando-Matrix)**

Das Makefile automatisiert die komplexen mathematischen Operationen des Systems:

- make compile: Kompiliert den C-Kernel (k501_kernel). Erforderlich nach Code-Updates.
- make all: Führt die gesamte Kette (Compile -> Sync -> Bridge -> Pack -> Audit) aus.
- make clean: Löscht transiente Dateien und setzt den Puffer zurück.
- make audit: Führt scripts/k501_audit_lattice.py aus. **Wichtig:** Muss nach jedem Pack-Vorgang "STABLE" melden.

## **5. Verzeichnis-Struktur (Lattice-Topologie)**

Plaintext

~/Dokumente/K501_Vault/  
├── 00_Meta/Docs/ # Autarke API-Dokumentation (Offline-Mirror)  
├── 02_QuantumLattice/ # Das physische Gitter (PackBlocks PB-xxx.md)  
├── 03_Archive/ # Rohdaten-Quelle (RAW)  
│ ├── 04_Web_Ingest/ # Automatisierte Web-Importe  
│ ├── 98_Observations/ # Deine Beobachtungs-Frames (OBS)  
│ └── 99_Raw_Dev_History/ # System-Historie & F-99999 (Audit Log)  
├── archive/ # frames.ndjson (Der logische Zustands-Vektor)  
├── scripts/ # Operative Logik (Python/Bash)  
└── src/ # Kernel-Quellcode (C)  

## **6. Besondere Komponenten**

### **Der Audit-Log (F-99999)**

Unter 03_Archive/99_Raw_Dev_History/F-99999_Audit_Log.md findest du die permanente Historie deiner System-Gesundheit. Jeder Lauf von make audit hinterlässt hier einen Zeitstempel und den Integritätsstatus.

### **DeepRead (Semantische Engine)**

Die Datei scripts/k501_deepread.py enthält die Wissens-Matrix. Sie scannt Ingests automatisch nach Begriffen wie _Quantum-Logic_ oder _Axiomatik_ und vergibt entsprechende Tags im Navigator.

## **7. Wartung & Sicherheit**

- **Append-Only:** Lösche niemals Dateien innerhalb des Lattice manuell. Nutze make clean, wenn du einen Ingest komplett neu starten willst.
- **Git-Integration:** Nach der Aktivierung des Git-Plugins (geplant für morgen) wird jeder erfolgreiche Audit-Lauf als "Snapshot" versiegelt.
- **Local REST API:** Ermöglicht zukünftig die Echtzeit-Kommunikation zwischen deinen C-Programmen und der Obsidian-Oberfläche (Port 27124).

**Status des Systems:** Alle 1416 Frames sind sicher im Lattice verankert. Das System ist bereit für die Suspension bis zum nächsten Operationszyklus.

**Nächster Schritt:** Möchtest du, dass ich diese README als permanenten Frame **F-00001** direkt in dein Archiv verschiebe, damit sie morgen beim ersten Start sofort im Navigator erscheint?