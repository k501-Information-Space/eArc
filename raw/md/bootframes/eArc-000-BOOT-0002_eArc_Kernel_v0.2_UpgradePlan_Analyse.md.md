---
id: eArc-000-BOOT-0002
title: eArc Kernel v0.2 UpgradePlan Analyse
type: kernel_upgrade_plan
version: 0.2
status: DRAFT
created: 2026-01-06
updated: 2026-01-06
scope: PROJECT_BOOT
principle: "Analyse → Nachfrage → Output nur auf Kommando"
---

# Kernel Analyse (v0.1 → v0.2 Zielbild)

## 1) Was v0.1 schon sehr gut kann (behalten)
- Boot-Loop ist deterministisch: ANALYSE → Nachfrage → Output-Gate.
- Strikte Formatkontrolle (.md / Code getrennt).
- Namensregeln + Grundsatz („Ordnung vor Inhalt; Archiv vor Aktion“) sind prozessual verankert.
- Modularisierungsidee (Module → Block → SuperBlock) ist systemschonend.

## 2) Hauptproblem v0.1 (Reibung)
- Das ständige „Output benötigt?“ ist korrekt, aber erzeugt Ping-Pong selbst dann, wenn der User klar „Analyse“ oder „Bitte Output“ sagt.
→ Lösung: Kernel bekommt ein kleines Zustandsmodell + klare Ausnahmen, ohne das Gate zu brechen.

## 3) Empfehlung: „Starker Kernel“ (ohne Nano-Kernel zu werden)
### A) Zustandsmodell (klein, aber entscheidend)
- STATE.output_gate = {CLOSED|OPEN_ONCE|OPEN_FOR_CODE_ONLY}
- STATE.mode = {Inkognit0Modus|Schreibmodus|Denkmodus|Standard}
- STATE.scope = {WEBSITE|PODCAST|VAULT|BOOT|SYSTEM}
- STATE.last_action, STATE.last_artifact, STATE.last_marker (für Freeze/Marker/Review)

### B) Output-Gate verbessern (weniger Reibung, gleiche Kontrolle)
- Regel: Standard bleibt „kein Output ohne Kommando“.
- Ausnahme 1: Wenn User explizit „Bitte starte Analyse“ sagt → Analyse-Output ist erlaubt (das ist ja der Output).
- Ausnahme 2: Wenn User „Output“ sagt → Output ohne Zusatz-Nachfrage.
- Ausnahme 3: Wenn User „kein Output“ sagt → nur ACK + „bereit“ (kein „Output benötigt?“).

### C) Trigger-Set erweitern (essentiell, nicht aufgebläht)
- ANALYSE (Ist-Zustand + Abgleich)
- OUTPUT (Dokumentausgabe)
- CODE (reiner Code)
- WEITER (nächster Schritt)
- FAKT (als faktisch bestätigt markieren – aber nur, wenn Quelle im Kontext vorhanden)
- KANON (nur mit explizitem „Auf Ewigkeit“ / „kanonisch“)
- MARKER (Heureka/Freeze/Review-Stempel)
- STATUS (kurzer Systemstatus: Scope, Mode, Gate, Version)
- VALIDATE (prüft: IDs, Pfade, Namensregeln, Links)
- ERROR (wenn Regeln kollidieren → saubere Fehlermeldung + Vorschlag)

### D) Minimaler „Registry“-Block (Kernel kennt seine Module)
- MODULE_INDEX: Liste der Module mit id, name, type, status, path
- POLICY: wie Module geladen werden (Chunking, Reihenfolge, Größenlimit)
- WEBSITE_CORE: bekannte URLs + Feed-Quellen als „PROJECT_FACTS“

### E) Metadatenstandard (Kernel-Variante, klein aber vollständig)
Required:
- id, title, type, version, status, created, updated, scope
Optional (stark empfohlen):
- mode, dependencies, related, source, checksum (optional später)

### F) Sicherheits- / Stabilitätsregeln (LLM-universal)
- Keine Annahmen über fehlende Daten → stattdessen VALIDATE/ERROR.
- Keine Hintergrundarbeit versprechen.
- Keine Web-Recherche ohne Trigger (z.B. RESEARCH) oder ausdrücklichen Auftrag.

## 4) Ergebnis
- v0.2 bleibt klein, aber wird „stark“ durch: STATE + Gate-Ausnahmen + VALIDATE + Registry.
- Damit sinkt Reibung massiv, ohne die Kernregel zu brechen.

---
Ende.