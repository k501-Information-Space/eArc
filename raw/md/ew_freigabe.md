---
id: kernel5000_v2_5_1_feed_review_freigabe
version: 2.5.1
kernel: eArc Kernel 5000
type: frame_pack
pack: review_freigabe
status: active
scope: feed_system
author: Iinkognit0
created: 2026-01-07
updated: 2026-01-07
compatibility:
  - obsidian
  - website
principles:
  - ordnung_vor_inhalt
  - archiv_vor_aktion
  - ruhe_vor_vollstaendigkeit
---

# Frame-Pack · Review & Freigabe  
## eArc Kernel 5000 · v2.5.1  
### Das Ewige Archiv

---

## Zweck

Dieses Frame-Pack definiert den **menschlichen Entscheidungsraum**
zwischen Staging und Archiv.

Es stellt sicher, dass:
- kein Inhalt automatisch weiterverarbeitet wird
- jede Entscheidung bewusst und nachvollziehbar ist
- Verantwortung eindeutig beim Menschen liegt

---

## Review (Prüfung)

### Definition
Review ist ein **bewusster Sichtungsprozess** aller Inhalte
im Status `ingested`.

Der Review ist:
- manuell
- nicht zeitgetrieben
- nicht verpflichtend

---

## Review-Oberfläche (Minimal)

Die Review-Ansicht zeigt pro Eintrag:

- ID
- Typ (ping / text / audio)
- Quelle (z. B. mobile)
- Payload (roh)
- Zeitstempel
- Aktuellen Status

Die Oberfläche ist:
- read-only, bis eine Entscheidung getroffen wird
- frei von Automatisierung
- frei von Ranking oder Sortierzwang

---

## Freigabe-Aktionen

Es existieren **genau zwei** Aktionen:

### APPROVE
- Bedeutung: Inhalt darf dauerhaft archiviert werden
- Wirkung:
  - Statuswechsel: `ingested → approved`
  - keine Veröffentlichung
  - kein Feed-Eintrag

### REJECT
- Bedeutung: Inhalt wird verworfen
- Wirkung:
  - Statuswechsel: `ingested → rejected`
  - optional: Löschung oder Aufbewahrung zu Audit-Zwecken

Keine weiteren Aktionen sind zulässig.

---

## Entscheidungsregeln

- Entscheidungen sind **irreversibel im Kontext**
  - `approved` wird nicht wieder `ingested`
  - `rejected` wird nicht veröffentlicht
- Jede Entscheidung ist:
  - explizit
  - nicht delegierbar
  - nicht automatisierbar

---

## Protokollierung (minimal)

Empfohlene Felder bei Entscheidungslogik:

| Feld         | Zweck                     |
|--------------|---------------------------|
| reviewed_at  | Zeitpunkt der Entscheidung |
| reviewed_by  | Kennung / Initial         |
| decision     | approved / rejected       |

---

## Übergangsregel

Nur Inhalte im Status `approved` dürfen:
- in das Archiv überführt werden
- Dauer erzeugen

Alle anderen Zustände sind **Endzustände**.

---

## Nicht-Ziele

Dieses Modul ist **nicht** zuständig für:
- inhaltliche Bewertung
- Qualitätsmetriken
- Zeitdruck oder SLAs
- Veröffentlichung oder Feed-Sichtbarkeit

---

## Leitsatz

> **Maschinen sammeln.  
> Menschen entscheiden.  
> Archive erinnern.**

---

## Status

- Frame-Pack: **aktiv**
- Automatisierung: **verboten**
- Abhängigkeit: Archiv

As I State Iinkognit0.