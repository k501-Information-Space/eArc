---
id: eArc-K5-FRM-0501
title: Feed Sender
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
  - feed
  - sender
  - communication
---

# Feed Sender · v1.0

## Zweck
Dieser Frame ermöglicht das **Erstellen und Veröffentlichen eigener Feeds**
im K5-System.

Der Feed ist die **primäre Kommunikationsform**:
ruhig, asynchron, dokumentierbar.

---

## Grundprinzip
- Jede Veröffentlichung ist **bewusst**
- Jeder Feed-Eintrag ist **archivierbar**
- Keine Reaktionspflicht
- Kein Echtzeitdruck

---

## Was ein Feed-Eintrag ist
Ein Feed-Eintrag ist ein **Frame** mit:

Pflichtfeldern:
- `id`
- `title`
- `timestamp`
- `author`
- `content`
- `tags` (**1–5, Pflicht**)

Keine optionalen Metadaten.
Keine Hashtag-Flut.

---

## Erstellung (Flow)

1. Mensch wählt: **Feed erstellen**
2. System prüft:
   - Consent vorhanden?
   - Frame Limit eingehalten?
3. Inhalt wird als **Frame** erzeugt
4. Konvertierung in Feed-Format (RSS/Atom/JSON)
5. Veröffentlichung lokal oder serverseitig

Kein automatisches Senden.

---

## Erlaubte Feed-Formate
Mindestens eines:
- RSS 2.0
- Atom
- JSON Feed v1

Kein proprietäres Format.

---

## Inhaltliche Grenzen
- Ein Gedanke pro Feed
- Keine Serien ohne Pause
- Kein Push-Zwang
- Keine algorithmische Hervorhebung

---

## Sicherheit & Ruhe
- Kein Tracking
- Keine Analytics
- Keine Like-/Kommentarstruktur
- Veröffentlichung jederzeit stoppbar

---

## Verhältnis zu anderen Frames
- Feed Sender erzeugt **Frames**
- Diese Frames können:
  - archiviert
  - exportiert
  - geblockt
  - später gebündelt werden

---

## Status
FINAL  
Sofort einsetzbar  
Kanon-konform  

---

As I State Iinkognit0.