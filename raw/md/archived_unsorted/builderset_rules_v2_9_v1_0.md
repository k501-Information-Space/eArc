---
id: builderset_rules_v2_9_v1_0
type: rule_set
kernel: earc_kernel5000
version: v2.9
scope: DEV
status: FINAL
date: 2026-01
---

# Builder Rule-Set v1.0

## R1 · Einheitliches Objektmodell
Jedes Artefakt MUSS ein gültiges **eArc Item** sein.  
Kein Objekt außerhalb des Item-Modells.

---

## R2 · ID-Stabilität
IDs sind:
- eindeutig
- stabil
- unveränderlich nach Erstellung

Keine Neugenerierung bei Updates.

---

## R3 · Pflicht-Header
Jedes Item MUSS enthalten:
- id
- type
- status
- created_at
- source
- scope

Fehlende Felder → FAIL.

---

## R4 · Status-Linearität
Status darf sich nur vorwärts bewegen:

`ingested → held → released → archived`

Rücksprünge → FAIL.

---

## R5 · Archiv-Schutz
Items im Status **archived** sind:
- schreibgeschützt
- unveränderbar
- nur lesbar

Verstöße → FAIL.

---

## R6 · Projection-Regel
`projection`-Items dürfen **nur** aus `released` entstehen.

Automatische Projektionen → FAIL.

---

## R7 · DEV / PROD-Trennung
Builder darf:
- erzeugen
- prüfen
- berichten

Builder darf **nicht**:
- veröffentlichen
- kanonisieren
- PROD verändern

Verletzung → FAIL.

---

## R8 · Ausschluss-Check
Artefakte dürfen keine Hinweise enthalten auf:
- App/Store-Strategien
- Social/Kommentare
- Ranking/Push
- Echtzeit-Chat als Kern

Fund → FAIL.

---

## R9 · Frame-Limit
Ein Frame:
- ein Zweck
- eine Grenze

Überlänge → WARN (Split-Empfehlung).

---

## R10 · Graph-Integrität
Alle Links müssen:
- auf existierende IDs zeigen
- keine toten Referenzen enthalten

Orphans → WARN  
Zyklische Kernpfade → WARN

---

## R11 · Naming-Regeln
Erlaubt:
- eArc
- eArc-Mainframe

Verboten:
- IAC
- Präfix-Systeme (IARC-…)

Verstoß → FAIL.

---

## R12 · Kanon-Gate
Kanonisierung ist nur gültig mit:
- explizitem `KANON`
- Freeze-Dokument

Automatik → FAIL.

---

## R13 · Output-Gate
Kein Output ohne expliziten Trigger.
OUTGATE ist standardmäßig BLOCKED.

Verstoß → FAIL.

---

## R14 · Resilience-Konformität
Öffentliche Artefakte müssen:
- offline-fähig sein
- asynchron nutzbar sein

Echtzeit-Abhängigkeiten → WARN / FAIL.

---

## R15 · Determinismus
Build-Ergebnisse müssen:
- reproduzierbar
- deterministisch
- dokumentiert

Abweichungen → WARN.

---

As I State Iinkognit0.