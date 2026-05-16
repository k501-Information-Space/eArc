---
id: kernel5000_v2_5_1_feed_archiv
version: 2.5.1
kernel: eArc Kernel 5000
type: frame_pack
pack: archiv
status: active
scope: feed_system
author: Iinkognit0
created: 2026-01-07
updated: 2026-01-07
compatibility:
  - obsidian
  - website
  - filesystem
  - database
principles:
  - ordnung_vor_inhalt
  - archiv_vor_aktion
  - ruhe_vor_vollstaendigkeit
---

# Frame-Pack · Archiv  
## eArc Kernel 5000 · v2.5.1  
### Das Ewige Archiv

---

## Zweck

Dieses Frame-Pack definiert das **Archiv** als dauerhafte,
unabhängige und primäre Speicherinstanz des Feed-Systems.

Das Archiv ist:
- Quelle der Wahrheit
- nicht flüchtig
- nicht vom Feed abhängig
- nicht von Darstellung oder UI abhängig

---

## Definition Archiv

Das Archiv besteht aus **zwei klar getrennten Ebenen**:

1. **Dateisystem** – trägt den Inhalt  
2. **Datenbank** – trägt Ordnung, Metadaten und Referenzen

Diese Ebenen dürfen **niemals vermischt** werden.

---

## Übergang ins Archiv

Ein Inhalt darf **nur dann** archiviert werden, wenn:

- Status = `approved`
- Entscheidung durch einen Menschen erfolgt ist
- keine offenen Review-Zustände existieren

Der Übergang lautet:

`approved → archived`

---

## Archiv-Dateisystem

### Prinzipien
- menschenlesbar
- portabel
- migrationsfähig
- unabhängig von Software

### Empfohlene Struktur (Beispiel)