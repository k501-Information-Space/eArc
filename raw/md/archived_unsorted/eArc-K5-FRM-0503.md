/home/oai/eArc/K5/eArc-K5-FRM-0503_ExportRUN_v1.0_FINAL.md
---
id: eArc-K5-FRM-0503
title: Export RUN
type: frame
version: 1.0
status: FINAL
created: 2026-01-08
updated: 2026-01-08
scope: K5_CORE
consent_required: true
privacy_level: high
tags:
  - k5
  - export
  - pandoc
  - latex
  - io
---

# Export RUN · v1.0

## Zweck
Dieser Frame ermöglicht die **echte Ausführung von Datei-Exports**
aus dem K5-System heraus – **kontrolliert, bewusst und reproduzierbar**.

Export RUN ist die **Brücke zwischen Denken und Datei**.

---

## Grundprinzip
- Kein automatischer Export
- Keine Hintergrund-Ausführung
- Keine versteckten Side-Effects

> **Export ist ein bewusster Akt.**

---

## Voraussetzungen
Export RUN ist **nur aktiv**, wenn:
1. **DEV MODE ON**
2. Tooling lokal verfügbar:
   - `pandoc`
   - LaTeX-Engine (z. B. `xelatex` oder `pdflatex`)
3. Ziel-Frame enthält gültigen **K5 MetaHeader**

Fehlt etwas → Export wird **abgelehnt**, nicht simuliert.

---

## Unterstützte Export-Ziele

### Text & Dokumente
- PDF (via LaTeX)
- EPUB
- HTML
- DOCX
- reines Markdown (Kopie)

### Pipeline (fix)