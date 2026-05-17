---
id: objectmodel_earc_item_v2_9
type: object_model
scope:
  - kernel5000_v2_9
status: FINAL (DEV)
date: 2026-01
---

# eArc Item · Objektmodell (v2.9)

## Grundsatz
Ein eArc Item ist die **einzige** verarbeitbare Einheit
im Kernel- und Builder-Kontext.

Alles ist Item.  
Nichts arbeitet außerhalb davon.

---

## Typen (enum)
- text
- frame
- memory_frame
- system_event
- projection

---

## Pflichtfelder
- id (eindeutig, stabil)
- type (enum)
- status (enum)
- created_at
- source (kernel | builder | import)
- scope (earc / kernel / dev / prod)

---

## Status (Lifecycle)
- ingested  → aufgenommen
- held      → intern gehalten
- released  → freigegeben (bewusst)
- archived  → dauerhaft gesichert

Archiv ist Endzustand.

---

## Optionale Felder
- links[]        (Graph)
- metadata{}     (YAML, validiert)
- checksum       (Integrität)
- render_profile (nur bei projection)

---

## Regeln
- Status-Rücksprünge verboten
- projection nur aus released
- archived ist schreibgeschützt
- Builder erzeugt Items, setzt keinen Kanon

---

As I State Iinkognit0.