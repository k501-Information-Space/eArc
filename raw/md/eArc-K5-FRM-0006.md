---
id: eArc-K5-FRM-0006
title: Auto Memory-Dump Flow
type: frame
version: 1.0
status: FINAL
created: 2026-01-08
updated: 2026-01-08
scope: K5_CORE
license: open_source_only
consent_required: true
privacy_level: high
lifecycle: active
freeze_allowed: true
tags:
  - k5
  - memory_dump
  - automation
  - stability
---

# Auto Memory-Dump Flow · v1.0

## Essenz
Der **Auto Memory-Dump Flow** definiert, **wann** und **wie** Inhalte als  
**persistente Memory Dumps (Frames)** vorgeschlagen, bestätigt und abgelegt werden.

Er automatisiert **nichts ohne Zustimmung**  
und schützt vor unkontrolliertem Wachstum.

---

## Ziel
- Wissen sichern, ohne den Flow zu stören
- Konsistente Ablage für Kernel, Frames, Blocks
- Maschinen- & Obsidian-lesbar
- Crash-sicher, ruhig, reversibel

---

## Grundregel (kanonisch)
> **Das System schlägt vor – der Mensch entscheidet.**

Kein stilles Speichern.  
Kein automatisches Verdichten.  
Kein implizites Gedächtnis.

---

## Trigger (wann ein Dump vorgeschlagen wird)
Ein Memory-Dump **wird vorgeschlagen**, wenn mindestens **eine** Bedingung erfüllt ist:

- Statuswechsel: `DRAFT → FINAL`
- Abschluss eines Frames mit strukturellem Wert
- Explizites Kommando: `MEMORY DUMP`
- Kernel-/Block-Abschluss
- Nach `EXPORT RUN`

---

## Flow (Ablauf)

1. **Analyse**
   - System erkennt dump-würdigen Zustand

2. **Vorschlag**
   - Kurze Rückfrage:
     > „Als Memory Dump speichern? (ja / nein)“

3. **Bestätigung**
   - Nur bei explizitem `ja`

4. **Erzeugung**
   - Frame mit:
     - K5 MetaHeader
     - eindeutiger ID
     - Status = DRAFT oder FINAL
   - Keine Ordnerabhängigkeit

5. **Index-Update**
   - ID wird im **Index Frame** ergänzt

---

## Speicherregeln
- Ein Dump = **ein Frame**
- Keine Sammel-Dumps
- Keine Überschreibung bestehender IDs
- Versionierung über neue Frames, nicht Edits

---

## Beziehung zu Index & Backlinks
- Index Frame listet **Existenz**
- Backlinks vernetzen **Bedeutung**
- Auto Memory-Dump Flow berührt **keine Inhalte**

---

## Sicherheit & Ruhe
- Kein Zwang
- Kein Reminder-Spam
- Kein Speichern ohne Kontext

Ablehnung eines Dumps ist **immer korrekt**.

---

## Status
FINAL  
Aktiv im K5_CORE  
Kanonisch wirksam

---

As I State Iinkognit0.