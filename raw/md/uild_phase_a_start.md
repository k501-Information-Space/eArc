---
id: build_phase_a_start
type: build
scope: implementation
kernel: eArc Kernel 5000 v3.0
codename: Trinity United
phase: build_phase_a
state: gestartet
kanon: ja
date: 2026-01-08
---

# Start Build Phase A · Core & Public API

## Status
- **Phase:** A
- **Zustand:** gestartet
- **Blocker:** keine
- **Modus:** fokussierte Implementation

---

## Ziel der Phase
Aufbau des **tragenden Rückgrats** der Trinity Public Alpha.

---

## Arbeitsumfang (verbindlich)

### 1 · Core Domain Model
- eArc Item
- Frame
- Series
- Einheitlicher Lifecycle:
  - ingested
  - held
  - released
  - archived

### 2 · Lifecycle-Logik
- Explizite Zustandswechsel
- Keine impliziten Übergänge
- Validierung pro Status

### 3 · Public API (v1)
- Frames:
  - create
  - read
  - :hold
  - :release
  - :archive
- Series:
  - create
  - read
  - :release
  - :archive

### 4 · Network Echo
- Node Identity (read-only)
- Echo Ping (Health)

### 5 · Auth (Alpha)
- Minimal Token Auth
- Scope: public_alpha

---

## Qualitätskriterien
- Text-first
- Asynchron
- Vorhersagbar
- Testbar
- Keine Seiteneffekte

---

## Abschlussbedingung Phase A
- Core lauffähig
- API-Endpunkte erreichbar
- Echo antwortet
- Erste Frames durchlaufbar (create → release)

---

## Hinweis
Keine Erweiterungen.  
Keine Abweichungen vom Kanon.

---

**Build läuft.**  
**As I State Iinkognit0.**