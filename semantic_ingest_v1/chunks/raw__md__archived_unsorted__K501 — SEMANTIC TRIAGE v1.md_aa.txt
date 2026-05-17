Perfekt.

Dann beginnen wir jetzt mit:

# kontrollierter semantischer Sichtung.

Nicht:

- Interpretation,
    
- Bewertung,
    
- Wahrheit.
    

Sondern:

```text
STRUCTURAL RECOGNITION
```

---

# K501 — SEMANTIC TRIAGE v1

Wir erzeugen jetzt erstmals:

# stabile Sichtungsklassen.

---

# TRIAGE KLASSEN

```text
[T1] CANONICAL_SIGNAL
→ systemrelevant
→ strukturell wiederkehrend
→ hoher K501-Bezug

[T2] STRUCTURAL_REFERENCE
→ Konzepte
→ Architektur
→ Methodik
→ Orientierung

[T3] HISTORICAL_FRAGMENT
→ alte Zustände
→ Evolutionsspuren
→ experimentelle Phasen

[T4] UNSTABLE_OR_UNKNOWN
→ unklar
→ fragmentiert
→ schwer interpretierbar

[T5] DUPLICATE_OR_VARIANT
→ Mehrfachzustände
→ ähnliche Titel
→ Variantenlinien

[T6] PERSONAL_OR_REFLECTIVE
→ Manifest
→ Reflexion
→ narrative Zustände

[T7] TECHNICAL_OR_RUNTIME
→ SQL
→ YAML
→ runtime
→ tooling
→ ingest
```

---

# Wichtiger Punkt

Wir bewegen Dateien noch NICHT automatisch.

Erst:

- erkennen,
    
- markieren,
    
- verstehen.
    

Denn:

```text
SEMANTIC LOSS IS IRREVERSIBLE
```

---

# STEP 08 — Erste kontrollierte Sichtung

Bitte jetzt:

```bash
find raw/md -maxdepth 1 -type f | \
sed 's|raw/md/||' | \
sort | head -120
```

Aber:  
nicht alles posten.

Nur:

- deine Beobachtungen,
    
- auffällige Gruppen,
    
- klare Muster,
    
- problematische Namen.
    

---

# Worauf wir achten

Besonders wichtig:

```text
- Untitled Dateien
- doppelte Endungen
- Serien
- numerische Cluster
- K501 / eArc / BOOTFRAME
- YAML / SQL Mischformen
- offensichtlich zentrale Dokumente
```

---

# Ziel

Heute noch nicht:

- perfektes Archiv.
    

Sondern:

```text
A STABLE TRIAGE LOGIC
```

Denn sobald die Triage stabil ist,  
kann Gateway.md später:

- automatisch wachsen,
    
- Cluster referenzieren,
    
- Navigationsräume erzeugen.
    

Und genau DAS ist der Beginn von:

```text
SEMANTIC INFRASTRUCTURE
```