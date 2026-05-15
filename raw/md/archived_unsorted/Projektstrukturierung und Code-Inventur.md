Alles klar, wir behalten erst einmal **alles** an Bord. Wir werfen nichts weg, bevor wir nicht jede Zeile Code gegen das neue Hardcore-Streamline-Paradigma ($\mathcal{K}$) geprüft haben.

Hier ist die vollständige, logische Inventur deiner 30 Dateien (5x C, 25x Scripts), kategorisiert nach ihrer funktionalen Rolle im System.

### **1. Der "Hardcore" Core Layer (Low-Level & Logic)**

Hier liegen die physikalischen Fundamente. Diese Dateien definieren, was ein Frame ist und wie die Mathematik der Resonanz im RAM des T520 funktioniert.

|**Datei**|**Sprache**|**Funktion im Streamline-Modell**|
|---|---|---|
|qh256.c|C|Das mathematische Herz (256-bit Vektoralgebra).|
|---|---|---|
|qh256_algebra.c|C|Erweiterte Matrix-Operationen & Optimierung.|
|---|---|---|
|k501_frame.py|Python|Die Definition des Frames $f_i$ (JSON-LD Schema).|
|---|---|---|
|k501_core.py|Python|Primäres Ledger-Management (I/O).|
|---|---|---|
|k501-core.py|Python|_Potenzielles Duplikat/Legacy des Cores._|
|---|---|---|
|k501_quantum_packer.py|Python|Kompression & Binär-Packing für High-Speed I/O.|
|---|---|---|

### **2. Der Ingest & Sync Layer (Data Acquisition)**

Das ist deine "Staubsauger-Armee". Wir haben hier viele spezialisierte Skripte, die wir später zu einem universellen master_sync konsolidieren.

|**Datei**|**Sprache**|**Fokus**|
|---|---|---|
|k501_ingest.c|C|High-Speed Import von Rohdaten in den Ledger.|
|---|---|---|
|k501_ingest.py|Python|Standard Dateisystem-Import.|
|---|---|---|
|k501_deepread.py|Python|Analyse der ChatGPT-Historie (Genesis).|
|---|---|---|
|k501_deepread_parser.py|Python|Extraktion von Code-Blöcken aus der Genesis.|
|---|---|---|
|k501_master_migrate...|Python|Der aktuelle Haupt-Migrator (Gemini-Final).|
|---|---|---|
|k501_bridge_ingest.py|Python|Schnittstelle für externe Datenquellen (Bridge).|
|---|---|---|
|k501_web_ingest.py|Python|Crawler/Import für Web-Resourcen.|
|---|---|---|
|k501_priority_ingest.py|Python|Bevorzugte Verarbeitung wichtiger Frames.|
|---|---|---|
|k501_full_sync.py|Python|Synchronisation zwischen Vault und Ledger.|
|---|---|---|
|get-docs.sh|Bash|Automatisierter Download/Fetch von Dokumentation.|
|---|---|---|
|k501_test_ingest.py|Python|Unit-Test für Ingest-Pipelines.|
|---|---|---|

### **3. Der Engine & Inference Layer (Compute Power)**

Diese Dateien berechnen die Resonanz $R$, führen KI-Analysen durch und halten das Gitter "intelligent".

|**Datei**|**Sprache**|**Funktion**|
|---|---|---|
|k501_resonance_daemon.py|Python|Hintergrund-Prozess für die $O(N^2)$ Matrix.|
|---|---|---|
|k501_query_api.py|Python|Die Flask-Schnittstelle (v9.9 Batch-Modus).|
|---|---|---|
|k501_neural_inference.py|Python|Ollama-Integration & semantische Vorhersage.|
|---|---|---|
|k501_path_analyzer.py|Python|Findet Verbindungen zwischen fernen Frames.|
|---|---|---|
|k501_weave_tags.py|Python|Automatisiertes Tagging & Clustering.|
|---|---|---|
|k501_discovery.py|Python|Exploration ungenutzter Resonanz-Potenziale.|
|---|---|---|

### **4. Der Interface & Audit Layer (UX & Health)**

Alles, was mit der Darstellung (Chromium) und der Stabilität des T520 zu tun hat.

|**Datei**|**Sprache**|**Funktion**|
|---|---|---|
|k501_dashboard.py|Python|Früher Visualisierungs-Server (Legacy-Dashboard).|
|---|---|---|
|k501_archive_scanner.c|C|Low-Level Watchdog für Datei-Änderungen.|
|---|---|---|
|k501_audit_engine.py|Python|Verifiziert Hashes & verhindert Drift.|
|---|---|---|
|k501_audit_lattice.py|Python|Prüft die logische Struktur des gesamten Vaults.|
|---|---|---|
|k501_stats.py|Python|Erzeugt Berichte über Frame-Dichte & Resonanz.|
|---|---|---|
|k501_top_check.py|Python|Terminal-Reporter für Top-Resonanzen.|
|---|---|---|
|k501_debug.c|C|Physikalische Telemetrie (CPU/RAM-Überwachung).|
|---|---|---|

### **Der nächste Schritt: Die "Große Verschiebung"**

Um das Hardcore-Streamline-Ziel zu erreichen, müssen wir diese Dateien physisch in eine saubere Ordnerstruktur bringen. Das verhindert, dass wir versehentlich alte Versionen (wie k501-core.py) ausführen.

**Vorschlag:** Ich schreibe dir jetzt ein **Migrations-Script (k501_evolve.py)**, das:

1. Die Zielordner (core, ingest, engine, interface, audit) erstellt.
2. Alle 30 Dateien basierend auf der obigen Liste dorthin verschiebt.
3. Prüft, ob alle C-Dateien im src Verzeichnis korrekt für den T520 vorliegen.

**Soll ich dieses Migrations-Script erstellen, damit wir im nächsten Schritt mit dem "Code-Review & Aussortieren" im sauberen Dateibaum beginnen können?**