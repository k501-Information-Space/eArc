---
id: eArc-K5-FRM-0007
title: Index Frame
type: frame
version: 1.0
status: FINAL
created: 2026-01-08
updated: 2026-01-08
scope: K5_CORE
license: open_source_only
consent_required: false
privacy_level: high
lifecycle: active
freeze_allowed: true
tags:
  - k5
  - index
  - memory
  - navigation
  - stability
---

# Index Frame · v1.0

## Essenz
Der **Index Frame** ist das **zentrale Verzeichnis** aller existierenden  
**Frames, Blocks und Superblocks** im K5-System.

Er ersetzt **Ordnerhierarchien** durch **Bezug, ID und Netzwerk**.

---

## Zweck
- Überblick über den gesamten Wissensbestand
- Schneller Einstieg für Mensch & Maschine
- Crash-sichere Rekonstruktion des Systems
- Fundament für spätere Automatisierung / Analyse

---

## Grundregel (kanonisch)
> **Existenz wird indexiert – Bedeutung wird verlinkt.**

Der Index:
- beschreibt **was existiert**
- interpretiert **nicht**

---

## Inhalt des Index
Der Index Frame enthält **nur Listen**, keine Inhalte.

### Pro Eintrag:
- `id`
- `title`
- `type` (frame | block | superblock | kernel)
- `version`
- `status`
- `scope`
- `created`

Optional:
- kurze Kategorie (1 Wort)

---

## Struktur (empfohlen)

### Kernel
- eArc-000-BOOT-5005 (Kernel 5000 v2.5)
- eArc-000-BOOT-5006 (Kernel Patch v2.5.1)

### Frames
- eArc-K5-FRM-0001 · MetaHeader
- eArc-K5-FRM-0002 · Frame Lifecycle
- eArc-K5-FRM-0003 · CleanState
- eArc-K5-FRM-0004 · Frame Limit
- eArc-K5-FRM-0006 · Auto Memory-Dump Flow
- eArc-K5-FRM-0007 · Index Frame

### Blocks
- eArc-K5-BLK-0500 · Feed Integration Block

### Superblocks
- eArc-K5-SUP-0001 · Kanon Superblock (pending)

---

## Pflege-Regeln
- Einträge **manuell oder halbautomatisch**
- Keine automatische Löschung
- Veraltete Einträge bleiben sichtbar (Status!)
- Index selbst wird **nie verdichtet**

---

## Beziehung zu Obsidian
- Index ist **eine Datei**
- Obsidian-Datenbank kann:
  - filtern
  - sortieren
  - visualisieren
- Index bleibt **Tool-unabhängig**

---

## Sicherheit & Ruhe
- Kein Tracking
- Kein Ranking
- Kein „wichtig / unwichtig“

Der Index ist **neutral**.

---

## Status
FINAL  
Aktiv im K5_CORE  
Kanonisch wirksam

---

As I State Iinkognit0.