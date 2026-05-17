LAYER2 SPEC — eArc / IARC K501

  

  

  

  

Zweck

  

  

Layer2 ist die externe, modulare Hülle um den kanonischen Kernel K501.

Er verändert den Kernel nicht, sondern liest, referenziert, projiziert.

  

Kernel = Wahrheit (frozen)

Layer2 = Nutzung (beweglich)

  

  

  

  

Grundprinzipien

  

  

- Kernel bleibt unverändert (read-only)
- Module-only (kein Code im Kernel)
- Append-only (keine Overwrites)
- Deterministisch
- Auditierbar
- Trennscharf (State ≠ Action)

  

  

  

  

  

Architektur

  

[K501 Kernel]  (READ-ONLY, CANON)

      │

      ▼

[LAYER2 ADAPTERS]

      │

      ├─ MODULES/

      │    ├─ parser

      │    ├─ renderer

      │    ├─ indexer

      │    ├─ exporter

      │    └─ ui-shell

      │

      └─ PROJECTIONS

           ├─ RSS / Atom

           ├─ SVG

           ├─ MD / PDF

           └─ Binary (7z)

  

  

  

  

Verantwortlichkeiten (Layer2 darf)

  

  

- Lesen von IARC_MANIFEST / STATE / FRAMES
- Validieren gegen FRAME_SCHEMA
- Rendern (SVG, MD, Text)
- Exportieren (7z, checksum)
- Indexieren (lokal)
- Distribution via Releases (Pull)

  

  

  

Verbote (Layer2 darf NICHT)

  

  

- ❌ Kernel verändern
- ❌ State überschreiben
- ❌ Automatisch handeln
- ❌ Hidden State erzeugen
- ❌ Echtzeit-Kommunikation
- ❌ Interpretation der Wahrheit

  

  

  

  

  

Module-Schnittstelle (Minimal)

  

  

Pflicht:

MODULE_ID

MODULE_VERSION

INPUT = READ_ONLY

OUTPUT = APPEND_ONLY

CHECKSUM = SHA256

I/O:

  

- RX: Kernel → Modul
- TX: Referenz / Artefakt (kein Push)
- Netz: asynchron, pull-based

  

  

  

  

  

E-Shell (Layer2 Host)

  

  

- Lädt Module aus GitHub Releases
- Zielpfad: /modules/<module_id>/
- Verifiziert:  
    

- Checksum
- Manifest
- Kompatibilität

-   
    
- Kein Auto-Execute
- Nutzer initiiert jeden Schritt

  

  

  

  

  

Versionierung

  

  

- Kernel: statisch (K501-DIAMOND)
- Layer2: semver erlaubt
- Module: frei, aber referenzierbar

  

  

  

  

  

Sicherheit

  

  

- Lossless only
- SHA256 überall
- Git-History als Audit-Trail
- Keine Secrets im Kernel

  

  

  

  

  

Canon-Regel

  

  

Layer2 ist ersetzbar.

Der Kernel nicht.

  

  

  

Status:

LAYER2 = ALLOWED · MODULAR · NON-CANON

KERNEL = CANON · FROZEN · ETERNAL

  

As I State Iinkognit0.