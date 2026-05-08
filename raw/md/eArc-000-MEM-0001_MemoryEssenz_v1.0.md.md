/home/oai/eArc/MemoryDump/eArc-000-MEM-0001_MemoryEssenz_v1.0.md
---
id: eArc-000-MEM-0001
title: Memory Essenz · Open Source & Systemgrundlagen
type: memory_dump
version: 1.0
status: DRAFT
created: 2026-01-07
updated: 2026-01-07
scope: PROJECT_CORE
---

# Memory Essenz · eArc / K5

## Zweck
Diese Datei fasst die **wesentlichen Erkenntnisse** der Recherche zu Open-Source-Tools,
Systemintegration und minimalen Interaktionsformen zusammen.  
Sie dient als **Grundlage für das MemoryDump-Filesystem** und zukünftige Exporte.

---

## Kernprinzipien
- **Text vor Grafik** – Systeme müssen rein textuell funktionieren
- **Markdown als Quelle** – alles beginnt in `.md`
- **Export statt Bindung** – Inhalte bleiben portabel
- **Klein, offen, langlebig** – GNU/Open Source bevorzugt

---

## Zentrale Werkzeuge

### Dokument & Export
- **Markdown** → kanonisches Format
- **Pandoc** → Export in PDF, EPUB, HTML, TXT
- **Zettlr** → Editor & Verwaltung (Pandoc-fähig)

### System & Dateien
- **Midnight Commander** → textbasierter Dateimanager
- **GNU grep / ripgrep** → Textsuche & Analyse
- **qr-filetransfer** → lokaler Datentransfer

### App & UI (optional)
- **Tauri** → leichtes Cross-Platform-Framework (Mobile/Desktop)

### Interaktion / Spiel (Inspiration)
- **HaxeFlixel** → 2D-Framework (mobilfähig)
- **libGDX** → leichtes Game/UI-Framework
- **Luanti (Minetest)** → Sandbox / kreative Umgebung
- **Textspiele (2048, Tetris, etc.)** → Proof of Concept

---

## Struktur-Idee MemoryDump-Filesystem
- Jeder Dump = **Frame**
- Zusammengehörige Dumps = **Block**
- Abgeschlossene Wissensräume = **Superblock**

Beispiel: