---
id: eArc-000-BOOT-5006
title: eArc Kernel 5000 v2.5.1 Patch MetaHeader Export
type: kernel_patch
version: 2.5.1
status: DRAFT
created: 2026-01-07
updated: 2026-01-07
scope: PROJECT_BOOT
depends_on:
  - eArc-K5-FRM-0003 (eArc Meta-Header v1.0)
---

# Kernel Patch v2.5.1 — MetaHeader + Export IO

## Neue Kernel-Regel: METAHEADER_REQUIRED
Ab jetzt gilt:
- **Jede Datei** (MD/TXT/HTML/…) beginnt mit dem **eArc Meta-Header** (v1.0).
- Ohne Meta-Header wird die Datei als **unvollständig** markiert (status bleibt DRAFT).

## Neue Kernel-Regel: IO_EXPORT_GATE
- Export ist **immer gated** (kein Auto-Export).
- Export nur auf Trigger: `EXPORT`
- Standard-Pipeline: **Pandoc**
- PDF-Engine: **LaTeX**
- Targets: PDF / EPUB / HTML / DOCX (optional)

## Trigger-Erweiterung (minimal)
Zusätzlich erlaubt:
- `EXPORT` → erzeugt einen Export-Plan (keine Ausführung ohne Zustimmung)
- `EXPORT RUN` → nur im DEV MODE, und nur wenn Tooling verfügbar

## Sicherheit / Ruhe
- Kein Export ohne explizites Kommando
- Keine Web-Inhalte im Codeblock
- Keine versteckten Metadaten

As I State Iinkognit0.