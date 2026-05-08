---
id: kernel5000_v2_5_1_feed_grundlagen
version: 2.5.1
kernel: eArc Kernel 5000
type: frame_pack
pack: feed_grundlagen
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

# Frame-Pack · Feed-Grundlagen  
## eArc Kernel 5000 · v2.5.1  
### Das Ewige Archiv

---

## Zweck

Dieses Frame-Pack definiert die **grundlegenden Begriffe, Zustände und Regeln**
des Feed-Systems.

Es schafft ein **gemeinsames Vokabular** und verhindert:
- implizite Annahmen
- technische Kurzschlüsse
- Vermischung von Archiv und Darstellung

---

## Grundannahmen

1. Ein Feed ist **keine Quelle**, sondern eine **Ansicht**.  
2. Sichtbarkeit ist **reversibel**, Archivierung nicht.  
3. Jeder Feed-Eintrag hat einen **archivierten Ursprung**.  
4. Jede Veröffentlichung ist **explizit**.

---

## Zentrale Begriffe

### Feed
Eine **lesende Projektion** von archivierten Inhalten.  
Der Feed schreibt **niemals** in das Archiv zurück.

### Archiv
Der **dauerhafte Speicher** aller freigegebenen Inhalte.  
Das Archiv existiert **unabhängig** von Feeds oder Darstellung.

### Intake
Der technische **Eingangspunkt** für neue Inhalte  
(z. B. Smartphone → Server).

### Staging
Ein **temporärer Zwischenraum**, in dem Inhalte warten,  
bis eine menschliche Entscheidung erfolgt.

### Review
Der **menschliche Prüf- und Entscheidungsprozess**  
(APPROVE / REJECT).

---

## Zustände (Statusmodell)

Jeder Inhalt befindet sich zu jedem Zeitpunkt in **genau einem** Zustand.

| Status     | Bedeutung                          |
|------------|-----------------------------------|
| ingested   | eingegangen, noch ungeprüft       |
| approved   | menschlich freigegeben            |
| rejected   | verworfen                         |
| archived   | dauerhaft gespeichert             |

Zusatzstatus (Darstellungsebene):
- `feed_visible = true | false`

---

## Trennungsprinzipien

- Intake ≠ Archiv  
- Archiv ≠ Feed  
- Freigabe ≠ Veröffentlichung  

Kein Modul darf:
- Zustände überspringen
- Entscheidungen automatisieren
- Sichtbarkeit erzwingen

---

## Nicht-Ziele (explizit)

Dieses Feed-System ist **nicht** zuständig für:
- Social Interaktion
- Likes, Rankings, Kommentare
- Realtime-Streams
- Push-Mechaniken

---

## Minimalformel

> **Archiv ist Wahrheit.  
> Feed ist Spiegel.  
> Entscheidung ist menschlich.**

---

## Status

- Frame-Pack: **aktiv**
- Gültigkeit: **Kernel 5000 · v2.5.1**
- Erweiterungen: **nur frameweise**

As I State Iinkognit0.