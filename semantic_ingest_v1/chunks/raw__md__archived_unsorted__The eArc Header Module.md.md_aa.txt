---
id: IAC-000-BOOT-001-01
title: "The eArc Header Module"
type: module
subtype: website_header
project: Iinkognit0
system: eArc
scope: website
target: wordpress
status: draft
version: 1
lang: de
created: 2026-01-06T00:00:00+01:00
updated: 2026-01-06T00:00:00+01:00
source: "ChatGPT Session · Header-Konzept + Implementationslogik"
requires:
  - "global css placement"
  - "global html insertion"
provides:
  - "sticky header"
  - "centered navigation with frames"
  - "FramesNewsLooP ticker band"
  - "consistent module across all pages"
links:
  start: "https://iinkognit0.de/"
  earc: "https://iinkognit0.de/earc/"
  podcast: "https://iinkognit0.de/podcast/"
  podlink: "https://pod.link/1862625280"
  substack: "https://iinkognit0.substack.com"
notes:
  - "Das farbige Element der Seite ist ausschließlich Header + FramesNewsLooP."
  - "Navigation: mittig, breite Borders/Frames, Strahlkraft, auf jeder Seite gleich."
  - "Ticker: Cyberpunk-Band, Endlos-Loop, Name: FramesNewsLooP."
---

# The eArc Header Module

## Zweck
Ein einziges, wiederverwendbares Header-Modul, das **auf jeder Seite identisch** erscheint und als **einziges farbiges Element** den visuellen Rahmen (Frames) setzt: Navigation + FramesNewsLooP (Ticker).

## Visuelles Konzept
- **Grundfläche:** Schwarz/Ink, klare harte Kanten (Square), keine Rundungen.
- **Frames:** breite Borders, klare Linien, leuchtende Akzentfarbe (einheitlich).
- **Zentrierung:** Navigation mittig ausgerichtet, gleiche Breite/Optik auf allen Seiten.
- **Strahlkraft:** Akzentfarbe nur im Header-/Ticker-Bereich (Brand-Identität).
- **Konstanz:** Header verhält sich überall gleich (Start, eArc, Podcast, Posts/Pages).

## Bausteine (Struktur)
1. **Brand-Zeile**
   - Text: `iinkognit0` (oder `eArc` – je nach gewünschter Hierarchie)
   - Optional: kurzer Untertitel „Das Ewige Archiv“

2. **Navigation-Frames**
   - Buttons/Frames:
     - Start → `/`
     - Das Ewige Archiv → `/earc/`
     - Podcast → `/podcast/`
   - Layout:
     - Desktop: eine Zeile, zentriert
     - Mobile: 2 Zeilen (wie bei dir im Screenshot) oder ein Grid

3. **FramesNewsLooP (Ticker-Band)**
   - Name/Label: `FRAMESNEWSLOOP`
   - Inhalt: endlos scrollende Items (z. B. „eArc Update…“, „Podcast…“, „Start…“)
   - Cyberpunk-Band: kontrastreich, akzentfarbig, klarer Rahmen

## Funktionsregeln
- **Sticky:** bleibt beim Scrollen oben.
- **Reduced Motion:** respektiert `prefers-reduced-motion` (Ticker stoppt dann).
- **Performance:** CSS/Animationen zentral, nicht pro Seite duplizieren.
- **SEO/UX:** Header ist HTML (nicht nur Bild), Links sind echte `<a>`.

## WordPress-Implementationslogik (ohne Code)
**Ziel:** Einmal einbauen, überall sichtbar.

### Empfohlen (sauber & wartbar)
- **CSS zentral** in *Customizer → Zusätzliches CSS* (oder Theme/Child-Theme Stylesheet).
- **Header-HTML global** über:
  - Theme Site Editor / Header Template (Block Theme), oder
  - Child Theme `header.php`, oder
  - Plugin „Header Footer Code Manager“ / „Insert Headers and Footers“ (sitewide), oder
  - Block „Custom HTML“ als **Template-Part**, der in alle Templates eingebunden wird.

### Notlösung (nur wenn nötig)
- HTML + CSS in jede Seite kopieren (funktioniert, aber dupliziert & fehleranfällig).

## Inhalte für FramesNewsLooP (Ticker Items – Vorschlag)
- `eArc · Ordnung vor Inhalt`
- `RSS · FramesFeed aktiv`
- `Podcast · Nachtgedanken neue Folge`
- `Start · Kanonische Referenz`
- `Substack · Schrift / Archiv`

## Nächster Schritt
Wenn du „**Code**“ oder „**Weiter**“ sagst:
- Ich gebe **nur den Maschinencode** (Header + Ticker) aus, so dass du ihn 1:1 in WordPress einsetzen kannst.