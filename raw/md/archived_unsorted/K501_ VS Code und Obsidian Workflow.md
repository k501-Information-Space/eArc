Hier ist die offizielle **README.md** für deinen K501 Information Space. Sie ist so konzipiert, dass sie sowohl in **VS Code** (als technisches Handbuch) als auch in **Obsidian** (als System-Übersicht) perfekt funktioniert.

# 🛰️ K501 ISOS · README

**Information Space Operating System (v4.0)**

**Target:** ThinkPad T520 | **OS:** Debian Trixie | **Kernel:** C/qh256

## 1. Was ist K501?

K501 ist kein einfaches Notizbuch, sondern ein **autopoietischer Informationsraum**. Es transformiert ungeordnete Dateien in ein strukturell integriertes **Lattice** (Gitter).

- **Kernel-Sicherheit:** Nutzt C-Code und OpenSSL (EVP-SHA256), um die physische Integrität deiner Daten zu garantieren.
- **Kausale Logik:** Unterscheidet zwischen Rohdaten (**RAW**) und deinen Beobachtungen (**OBS**).
- **Performance:** Optimiert für die T520-Hardware durch fraktale Kompression in PackBlocks (100 Frames pro Datei), was Obsidian-Lags eliminiert.

## 2. Setup & Workflow

Die Arbeit mit K501 findet in der Symbiose zwischen **VS Code** (Entwicklung/Ingest) und **Obsidian** (Betrachtung/Navigation) statt.

### A. VS Code (Das Kontrollzentrum)

Nutze das integrierte Terminal (Strg + ö oder Terminal -> New Terminal), um das System zu steuern.

**Ausführen von Skripten:**

- **Python-Skripte:** python3 scripts/name_des_skripts.py
- **Shell-Skripte:** bash scripts/name_des_skripts.sh

**Die Standard-Pipeline (Sequenz):**

Führe diese Befehle nacheinander aus, um neue Daten in das System zu integrieren:

1. make sync – Kernel-Scan der physischen Dateien.
2. make bridge – Semantische Analyse und Vergabe von IDs.
3. make pack – Erzeugung der PackBlocks für Obsidian.
4. make audit – Validierung der Isomorphie (Log vs. Gitter).

### B. Obsidian (Das Interface)

In Obsidian nutzt du den **K501 Neuro-Navigator** (Plugin), um durch das Lattice zu gleiten.

- **Navigation:** Klicke auf das Gehirn-Icon, um den Gitter-Graphen zu sehen.
- **Beobachtung:** Nutze den "Observe"-Button im Navigator, um neue Erkenntnisse zu einem Frame zu speichern.

## 3. Makefile Referenz

Das Makefile im Hauptverzeichnis ist dein primäres Steuerinstrument.

|**Befehl**|**Aktion**|
|---|---|
|make compile|Kompiliert den C-Kernel neu (benötigt nach Code-Änderungen in src/).|
|---|---|
|make sync|Startet den C-Kernel zur Hash-Validierung des Archivs.|
|---|---|
|make bridge|Führt den Neural-Ingest (v3.8) aus und webt kausale Pointer.|
|---|---|
|make pack|Komprimiert 1.415+ Frames in 15+ PackBlocks.|
|---|---|
|make audit|Prüft, ob Log und Gitter zu 100% übereinstimmen.|
|---|---|
|make clean|Entfernt transiente Dateien und bereitet einen frischen Ingest vor.|
|---|---|

## 4. Skript-Verzeichnis (Internal API)

### scripts/get-docs.sh

- **Zweck:** Spiegelt externe Obsidian-APIs und deinen eigenen K501-Quellcode in 00_Meta/Docs.
- **Nutzen:** Ermöglicht es dem **Copilot-Plugin**, dein System offline zu verstehen.

### scripts/k501_deepread.py

- **Zweck:** Das "Auge" des Systems. Analysiert Texte auf Schlüsselwörter (Quanten-Logik, Axiomatik etc.).

### scripts/k501_priority_ingest.py

- **Zweck:** Schneller Ingest für spezifische Dateitypen oder neue Beobachtungen.

## 5. Sicherheitshinweise für den Operator

1. **Append-Only:** Lösche niemals manuell Dateien aus 02_QuantumLattice. Das System baut sich durch make pack immer wieder neu auf.
2. **Kernel-Integrität:** Wenn make audit Fehler meldet, ist die kausale Kette unterbrochen. Führe sofort einen Full-Sync durch.
3. **Offline-Modus:** Das System benötigt kein Internet. Alle Dokumentationen befinden sich lokal im Mirror.

**Was ist dein nächster Schritt?** Soll ich dir zeigen, wie du eine **Desktop-Verknüpfung** auf deinem T520 erstellst, die das Obsidian-Vault und das VS Code-Verzeichnis mit einem Doppelklick gleichzeitig öffnet?