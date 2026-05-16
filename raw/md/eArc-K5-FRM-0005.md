---
id: eArc-K5-FRM-0005
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
  - memory_dump
  - stability
---

# Index Frame · v1.0

## Essenz
Der **Index Frame** ist das **stille Rückgrat** des K5-Systems.  
Er listet **alle existierenden Frames, Blocks und Superblocks** über ihre **IDs** auf –  
ohne Inhalte zu duplizieren.

Er ist **kein Ordner**,  
keine Hierarchie,  
sondern ein **navigierbarer Gedächtnisanker**.

---

## Zweck
- Zentrale Übersicht aller Memory Dumps
- Schnelles Wiederfinden über IDs
- Entkopplung von Ordnerstrukturen
- Obsidian- & Maschinen-kompatibel (Properties / Datenbankfähig)

> Ordnung entsteht durch **Bezug**, nicht durch Verzeichnisse.

---

## Grundprinzip (kanonisch)
- **Eine Zeile = eine ID**
- Keine Inhalte im Index
- Keine Interpretation
- Keine Priorisierung

Der Index **weiß, dass etwas existiert** –  
nicht *was* es ist.

---

## Struktur

### Pflichtbestandteile
Jeder Eintrag besteht aus:
- `id`
- optionalem Kurzlabel (max. 3–5 Wörter)
- optionalem Typ-Hinweis (frame / block / superblock)

### Beispiel