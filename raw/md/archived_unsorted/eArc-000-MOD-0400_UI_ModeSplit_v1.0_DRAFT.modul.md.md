/home/oai/eArc/Modules/eArc-000-MOD-0400_UI_ModeSplit_v1.0_DRAFT.modul.md
---
id: eArc-000-MOD-0400
title: UI Mode Split · DEV vs USER
type: ui_mode_split
version: 1.0
status: DRAFT
created: 2026-01-07
updated: 2026-01-07
scope: PROJECT_CORE
consent_required: true
privacy_level: very_high
depends_on:
  - eArc-000-BOOT-5000 (Kernel 5000 v2.0)
  - eArc-000-MOD-0300 (SuperPack v1.0 ALPHA)
---

# UI Mode Split (DEV vs USER)

## Zweck
Klare Trennung zwischen:
- **DEV_MODE** (Debug, Mock, Drawer, Logs)
- **USER_MODE** (Stille, minimale Bedienung, keine Debug-Last)

As I State Iinkognit0.

---

## Modi (UI-Level)
### USER_MODE (Standard für Alpha-Tester)
- Fokus: Ruhe, einfache Nutzung, wenig Optionen
- **Drawer: optional, standardmäßig AUS**
- Debug-Kommandos: **gesperrt**
- Mock-LLM: **AUS**
- Output-Gates: Kernel-konform

### DEV_MODE (nur für dich)
- Fokus: Test, Messung, Routing-Kontrolle
- Drawer: **AN**
- Debug-Kommandos: **erlaubt auf Anfrage**
- Mock-LLM: **AN (nur hier)**
- Export/Logs: **nur manuell**

---

## Consent (verpflichtend)
Frage exakt:
> „Möchtest du USER_MODE (ruhig) oder DEV_MODE (Test/Debug) nutzen?  
> USER_MODE ist empfohlen.“

Antworten:
- `USER` → USER_MODE aktiv
- `DEV` → DEV_MODE aktiv
- `DETAILS` → kurze Erklärung (6–10 Zeilen)
- `STOPP` → Abbruch

---

## Status-Drawer (optional)
**Ziel:** Überblick ohne Inhalte.

**Drawer-Felder (nur Metadaten):**
- Kernel: `5000 v2.0`
- Mode: `Inkognit0 | Denk | Schreib | Philosoph`
- UI-Mode: `USER | DEV`
- SuperPack: `ON | OFF`
- Track: `Persona | Statistica | None`
- Intent: `TEXT | PHILO | CODE | STATS | SYSTEM`
- Session: `mm:ss`
- OUTGATE: `BLOCKED | ARMED`

**Regel:** Keine Inhalte, keine Prompts, keine Antworten im Drawer.

---

## iPhone UI V1 (Text-Interface innerhalb ChatGPT)
### Layout (mental / einfach)
1) **Header**: eArc Titel + Kurzsatz
2) **Drawer Toggle**: `Drawer: ON/OFF` (nur DEV sichtbar, USER optional)
3) **Quick Buttons (als Text-Befehle)**:
   - `ANALYSE`
   - `OUTPUT`
   - `WEITER`
   - `CODE`
   - `STOPP`
4) **Eingabefeld**: normaler Text
5) **Antwortbereich**: Kernel-konform (MD oder Code)

---

## Abschluss
- Mock bleibt **DEV-only**
- USER bleibt **ruhig, minimal, sicher**
- Drawer bleibt **optional und inhaltfrei**

Ende.

As I State Iinkognit0.