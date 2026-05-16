---
id: eArc-K5-FRM-0004
title: Frame Limit
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
  - stability
  - frame_limit
---

# Frame Limit · v1.0

## Essenz
Dieser Frame begrenzt **Menge, Größe und Kadenz** von Frames im K5-System,  
um **Stabilität**, **Lesbarkeit** und **Crash-Sicherheit** zu gewährleisten.

Frame Limit ist **keine Einschränkung der Freiheit**,  
sondern eine **Schutzschicht für Mensch und System**.

---

## Kanonische Grundregel
> **Weniger Frames → klarere Struktur → stabileres System.**

Diese Regel gilt systemweit für **User- und Dev-Mode**.

---

## Aktive Limits (verbindlich)

### 1. Mengen-Limit (pro Output)
- **Maximal 1–3 Frames** pro Output
- Überschreitung → **Hinweis**, kein automatischer Split

### 2. Größen-Limit (pro Frame)
- Zielbereich: **300–800 Wörter**
- Absolute Obergrenze: **~1.200 Wörter**
- Darüber → **Split empfohlen**, Entscheidung beim Menschen

### 3. Zweck-Limit (Komplexität)
Ein Frame darf:
- **nur einen klaren Zweck** verfolgen
- **keine Block- oder Superblock-Logik** enthalten
- **keine fremden Frames implementieren**

---

## Verhalten bei Überschreitung
- Kein Abbruch
- Kein automatisches Kürzen
- Kein stilles Weglassen

Systemmeldung (informativ):
> „Frame-Limit erreicht – Split empfohlen.“

---

## Verhältnis zu höheren Ebenen
- **Frame** → atomar, eindeutig
- **Block** → kompositorisch
- **Superblock** → stabil, eingefroren

Frame Limit erzwingt **natürliche Evolution**:
**Frame → Block → Superblock**

---

## Sicherheit & Ruhe
- Keine impliziten Änderungen
- Keine automatische Verdichtung
- Keine versteckten Optimierungen

Alles bleibt **transparent, ruhig, nachvollziehbar**.

---

## Status
FINAL  
Aktiv im K5_CORE  
Kanonisch wirksam

---

As I State Iinkognit0.