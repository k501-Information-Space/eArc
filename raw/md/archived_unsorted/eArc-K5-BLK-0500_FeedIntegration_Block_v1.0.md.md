/home/oai/eArc/K5/eArc-K5-BLK-0500_FeedIntegration_Block_v1.0.md
---
id: eArc-K5-BLK-0500
title: K5 Feed Integration Block
type: block
version: 1.0
status: DRAFT
created: 2026-01-08
updated: 2026-01-08
scope: K5_CORE
license: open_source_only
depends_on:
  - eArc-K5-FRM-0001 (K5 MetaHeader)
  - eArc-K5-FRM-0100 (Frame Lifecycle)
  - eArc-K5-FRM-0200 (CleanState)
---

# K5 Feed Integration Block

## 0 · Zweck
Dieser Block definiert die **einzige initiale Kommunikationsform** im K5-System:
**Feeds** (RSS / Atom / JSON Feed).

Kein Chat.
Kein Messaging.
Kein Social Graph.

Kommunikation erfolgt **asynchron, ruhig, dokumentierbar**.

---

## 1 · Grundprinzip
- Jeder Mensch **sendet** Feeds
- Jeder Mensch **abonniert** Feeds
- Alles ist **lesbar, archivfähig, exportierbar**
- Kein Algorithmus entscheidet, **was wichtig ist**

---

## 2 · Feed-Typen (Kanonisch)

### 2.1 Outgoing Feed (Sender)
- erzeugt lokal oder serverseitig
- basiert auf **Markdown + MetaHeader**
- wird in Feed-Format konvertiert

### 2.2 Incoming Feed (Empfänger)
- abonnierbar per URL / Datei
- wird **nicht verändert**
- wird als Frame gespeichert

---

## 3 · Feed-Formate (erlaubt)
Pflicht: **mindestens eines**

- RSS 2.0
- Atom
- JSON Feed (v1)

Kein proprietäres Format.

---

## 4 · Pflicht-Metadaten pro Feed-Item
Jeder Feed-Eintrag MUSS enthalten:

- `id`
- `title`
- `timestamp`
- `author` (frei wählbar)
- `content`
- `tags` (**genau 1–5**, Pflicht)

### Tag-Regel (wichtig)
- mindestens **1**
- maximal **5**
- universell (keine Hashtag-Flut)
- semantisch klar

> Beispiel: `ruhe`, `technik`, `gedanke`, `beobachtung`

---

## 5 · Technischer Stack (Open Source)

### 5.1 Parsing (Empfang)
**Primär**
- `FastFeedParser` (Python, MIT)
- `feedparser` (Python, BSD)

### 5.2 Generierung (Senden)
**Primär**
- `Feedsmith` (JavaScript / TypeScript, MIT)

### 5.3 Verarbeitung / Automatisierung
Optional:
- RSS-Bridge (GPL)
- RSS-Merger (GPL/MIT je nach Tool)
- Feedpushr (MIT)

---

## 6 · Medien & Lizenzen
### Audio
- **MP3** → erlaubt (Patentfrei seit 2017)
- **OGG / Opus** → bevorzugt (offen)

### Text
- Markdown als Ursprung
- HTML nur als Export

### Verboten
- proprietäre Codecs ohne OSS-Lizenz
- DRM
- Tracking-Pixel

---

## 7 · Export / Archiv
Feeds können jederzeit exportiert werden als:

- `.md` (Frame)
- `.html`
- `.pdf`
- `.epub`

Pipeline:
- **Pandoc**
- **LaTeX** (PDF)
- optional EPUB-Stylesheets

Kein automatischer Export.  
Trigger erforderlich: `EXPORT`

---

## 8 · Speicherung (Memory Dump kompatibel)
- Jeder Feed-Item → **Frame**
- Speicherung **ohne Ordnerzwang**
- Verlinkung über IDs & Backlinks
- Obsidian-kompatibel

---

## 9 · Sicherheit & Ruhe
- Keine Echtzeit-Abhängigkeit
- Kein Push-Zwang
- Kein Ranking
- Kein Engagement-Tracking

Feed ist **Information**, kein Stimulus.

---

## 10 · Integration eArc-Mainframe
- eArc-Mainframe stellt **öffentliche Feeds**
- Mobile K5-Systeme können:
  - abonnieren
  - spiegeln
  - archivieren
- Kein Zwang zur Verbindung

---

## 11 · Grenzen
- Kein Chat
- Kein Kommentar-Thread
- Keine Likes
- Keine Manipulationsmechaniken

Kommunikation ≠ Reaktion.

---

## 12 · Status
DRAFT  
Bereit für Implementierung  
Kanonisierung **noch nicht erfolgt**

---

As I State Iinkognit0.