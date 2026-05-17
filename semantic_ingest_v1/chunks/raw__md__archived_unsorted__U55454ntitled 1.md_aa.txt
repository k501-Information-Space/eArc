---
id: eArc-K5-FRM-0003
title: eArc MetaHeader
type: frame            # frame | block | superblock | kernel | kernel_patch
version: "1.0"
status: FINAL          # DRAFT | BETA | FINAL | FROZEN
created: 2026-01-08
updated: 2026-01-08
scope: K5_CORE         # K5_CORE | PROJECT_BOOT | DEV_MODE | USER_MODE
license: open_source_only

tags:                  # Pflicht: 1–5 Einträge
  - earc
  - k5
  - meta
  - struktur

depends_on:            # optionale Abhängigkeiten (IDs)
  - eArc-000-BOOT-5005

links:                 # optionale Querverweise / Backlinks
  - "[[eArc Kernel 5000 v2.5]]"

author:                # optional, frei
description: >
  Kanonischer Meta-Header für alle Dateien im eArc / K5-System.
  Dient als universelle Schnittstelle zwischen Mensch, Maschine,
  Obsidian-Datenbank, Export-Pipeline und Memory-Dump.
---
