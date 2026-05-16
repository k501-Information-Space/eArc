/home/oai/eArc/Kernel/eArc-000-BOOT-5003_eArc_Kernel_v1.2_PATCH.md
---
id: eArc-000-BOOT-5003
title: eArc Kernel v1.2 Patch
type: kernel_patch
version: 1.2
status: DRAFT
created: 2026-01-06
updated: 2026-01-06
scope: PROJECT_BOOT
patch_of: eArc-000-BOOT-5002
---

# eArc Kernel v1.2 · Patch

## Ziel
Nahtloser Übergang zwischen **Kernel**, **MiniLoader** und **Modulen**.
Reduktion von Friktion beim Erstkontakt (LLM-agnostisch).

---

## 1) MINI_LOADER_HANDSHAKE (neu)
**Zweck:** Sichere Initialisierung nach Kernel-Load.

**Ablauf**
1. Kernel INIT
2. ETHOS_CORE aktiv
3. ASK_OUTPUT
4. **OPTION:** MINI_LOADER_START
5. Übergabe an Modulindex

**Regel**
- MiniLoader ist **Text-only**, keine Datei nötig.
- MiniLoader darf erklären, nicht ausführen.

---

## 2) CHAT_FALLBACK (neu)
**Wenn Nutzer nur sprechen möchte**
- Erlaubter Pfad aus ASK_OUTPUT:
  - `CHAT`
  - `PHILO`

**Effekt**
- Kein Datei-Zwang
- Keine Versionierung
- Keine Kanonisierung

---

## 3) SAFETY_GUARDS (präzisiert)
- Kein Auto-Upgrade des Kernels
- Kein implizites Nachladen von Modulen
- Jede Expansion benötigt expliziten Trigger

---

## 4) MODUL_INDEX_PREP (vorbereitet)
**Index-Typen**
- BOOT_MODULE
- DOC_MODULE
- API_MODULE
- CONTENT_MODULE

**Regel**
- Kernel kennt **nur Typen**, nicht Inhalte.

---

## Status
- Kernel weiterhin **DRAFT**
- Bereit für Finalisierung v1.x → v1.0 FINAL nach Kommando

---
Ende.