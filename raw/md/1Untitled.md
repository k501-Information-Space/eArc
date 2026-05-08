/home/oai/eArc/K5/eArc-K5-FRM-0501_FeedItem_Frame_v1.0.md
---
id: eArc-K5-FRM-0501
title: K5 Feed Item Frame
type: frame
version: 1.0
status: DRAFT
created: 2026-01-08
updated: 2026-01-08
scope: K5_CORE
license: open_source_only
depends_on:
  - eArc-K5-FRM-0001 (K5 MetaHeader)
  - eArc-K5-FRM-0100 (Frame Lifecycle)
---

# K5 Feed Item · Frame

## Zweck
Dieser Frame beschreibt **eine einzelne Kommunikationseinheit** im K5-System.  
Ein Feed-Item ist **keine Nachricht**, kein Chat-Beitrag, kein Kommentar.

Es ist ein **bewusster Zustandsausdruck**:
- geschrieben
- veröffentlicht
- gelesen
- archiviert

As I State Iinkognit0.

---

## Grundprinzip
- Ein Feed-Item steht **für sich**
- Es verlangt **keine Antwort**
- Es erzeugt **keinen Reaktionsdruck**
- Es ist vollständig **archivierbar**

Ein Feed-Item ist ein **Frame** im Sinne des Systems:
> ein klar definierter Zustand zu einem Zeitpunkt.

---

## Pflichtbestandteile (minimal & strikt)

Jeder Feed-Item-Frame MUSS enthalten:

- `id` — eindeutige Frame-ID
- `title` — kurzer, klarer Titel
- `timestamp` — Erstellungszeitpunkt (lokal oder UTC)
- `author` — frei wählbarer Name oder Kennung
- `content` — Textinhalt (Markdown)
- `tags` — **genau 1–5 Pflichtbegriffe**

Ohne diese Felder ist der Frame **ungültig**.

---

## Tag-Regel (kanonisch)
- mindestens **1**
- maximal **5**
- keine freien Hashtags
- keine Ketten
- keine Synonym-Flut

Ziel: **Orientierung, nicht Reichweite**

Beispiele:
- `ruhe`
- `gedanke`
- `beobachtung`
- `technik`
- `ethos`

---

## Inhaltliche Grenzen
- Kein Call-to-Action
- Keine Aufforderung zur Reaktion
- Keine Bewertung anderer Frames
- Keine algorithmische Optimierung

Feed-Items sind **Mitteilungen**, keine Stimuli.

---

## Technische Eigenschaften
- Ursprung: **Markdown**
- Exportfähig via Pandoc:
  - RSS / Atom / JSON Feed
  - HTML
  - PDF / EPUB
- Keine Abhängigkeit von UI
- Vollständig textbasiert

---

## Speicherung (Memory-Dump-kompatibel)
- Jeder Feed-Item-Frame kann:
  - einzeln gespeichert werden
  - verlinkt werden (Backlinks)
  - später zu Blocks oder Superblocks zusammengeführt werden
- Keine Ordnerstruktur erforderlich
- Ordnung entsteht über **IDs & Verweise**

---

## Lebenszyklus
1. Entwurf (DRAFT)
2. Veröffentlichung (Feed)
3. Archivierung (Frame bleibt unverändert)
4. Optionale Verdichtung (Block)

Keine Löschung.  
Kein „Editieren der Vergangenheit“.

---

## Status
DRAFT  
Bereit für Nutzung  
Nicht kanonisch

---

As I State Iinkognit0.