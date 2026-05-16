---
id: kernel5000_v2_5_1_feed_render
version: 2.5.1
kernel: eArc Kernel 5000
type: frame_pack
pack: feed_render
status: active
scope: feed_system
author: Iinkognit0
created: 2026-01-07
updated: 2026-01-07
compatibility:
  - obsidian
  - website
  - feed_rss
  - feed_json
principles:
  - ordnung_vor_inhalt
  - archiv_vor_aktion
  - ruhe_vor_vollstaendigkeit
---

# Frame-Pack · Feed-Render  
## eArc Kernel 5000 · v2.5.1  
### Das Ewige Archiv

---

## Zweck

Dieses Frame-Pack definiert die **Erzeugung von Feeds** als
**read-only Darstellung** archivierter Inhalte.

Der Feed:
- liest aus dem Archiv
- schreibt **niemals** zurück
- ist vollständig entkoppelt von Intake, Review und Archivierung

---

## Grundsatz

> **Feed ist Darstellung, nicht Handlung.**

Ein Feed kann:
- neu gerendert
- pausiert
- gelöscht
werden, ohne das Archiv zu berühren.

---

## Quelle der Wahrheit

Der Feed-Renderer liest **ausschließlich** aus:

- `archive_items` (Datenbank, Metadaten)
- Archiv-Dateien (Dateisystem, Inhalt)

Kein anderer Zustand ist zulässig.

---

## Sichtbarkeitsregel

Ein Archiv-Eintrag erscheint **nur dann** im Feed, wenn:

- `status = archived`
- `feed_visible = true`

Alle anderen Einträge bleiben **unsichtbar**, aber archiviert.

---

## Unterstützte Feed-Typen

### RSS
- kompatibel mit klassischen Readern
- XML-basiert
- chronologisch darstellbar

### JSON Feed
- modern
- API-freundlich
- maschinenlesbar

Alle Feed-Typen greifen auf **dieselbe Datenbasis** zu.

---

## Feed-Renderer (Logik)

### Aufgaben
- Auswahl geeigneter Archiv-Einträge
- Transformation in Feed-Formate
- Ausgabe als statische Dateien oder Endpoints

### Eigenschaften
- deterministisch
- zustandslos
- wiederholbar

---

## Minimaler Feed-Eintrag (abstrakt)

| Feld       | Herkunft            |
|------------|---------------------|
| id         | archive_items.id    |
| title      | Metadaten / Inhalt  |
| date       | approved_at         |
| content    | Archiv-Datei        |
| link       | Archiv-URL          |

---

## Aktualisierung

- Feed-Render erfolgt:
  - manuell
  - oder zeitgesteuert (Cron)
- keine Echtzeit-Pflicht
- kein Push-Zwang

---

## Nicht-Ziele

Der Feed-Renderer:
- ❌ bewertet nicht
- ❌ sortiert nicht verpflichtend
- ❌ kürzt keine Inhalte
- ❌ erzeugt keine Abhängigkeiten

---

## Leitsatz

> **Der Feed zeigt,  
> was das Archiv erlaubt.**

---

## Status

- Frame-Pack: **aktiv**
- Zugriff: **read-only**
- Abhängigkeit: Archiv

As I State Iinkognit0.