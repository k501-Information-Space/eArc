Resolve ausgeführt.

Nachfolgend die aufgelöste Gate-Liste, so wie sie der Kernel intern sieht, wenn

gates:

  enabled: true

  severity_model: "soft"

  rules: []

  use_gatepack: "k501-gatepack-soft-v0.1"

gesetzt ist.

  

  

  

  

Gates – Resolved View (SoftK501Dev)

  

  

Quelle: k501-gatepack-soft-v0.1

Modell: soft (nicht blockierend)

Default on_error: WARN

Aktive Gates: 50 (G001–G050)

  

  

IO / Safety

  

  

- G001 Out path configured
- G002 Out writing enabled in run mode
- G003 Write scope limited to out/
- G004 Destructive actions denied
- G005 Exclude out/ from scan
- G006 Exclude .git and node_modules
- G007 Confirm mode consistent with out write

  

  

  

Scan Health

  

  

- G010 File count not zero
- G011 Scan size within soft comfort band
- G012 Hidden files handling explicit
- G013 Symlinks not followed by default
- G014 Hashing off by default (soft)

  

  

  

Extract / Graph

  

  

- G020 Extract enabled in run mode
- G021 Markdown module configured
- G022 Graph module configured
- G023 Normalization path separator explicit

  

  

  

Frontmatter / IDs

  

  

- G030 Frontmatter id present where frontmatter exists
- G031 Frontmatter id format (soft)
- G032 Deterministic id strategy set
- G033 Determinism sorting configured

  

  

  

Links / Integrity

  

  

- G040 Link integrity (soft)
- G041 Self-loop prevention in links
- G042 Excessive outbound links (noise guard)

  

  

  

HUD / Report

  

  

- G045 HUD enabled (recommended)
- G046 Report outputs configured
- G047 Out directory not empty after write

  

  

  

Plugins / Control

  

  

- G048 Plugins disabled by default (soft)
- G049 Plugin allowlist present when plugins enabled

  

  

  

Calmness / Limits

  

  

- G050 Time budget set for calm runs

  

  

  

  

  

Resolved Semantik (Kurz)

  

  

- Keine Blocker: FAIL signalisiert nur.
- Late-bound: GatePack wird beim Run geladen/aufgelöst.
- Deterministisch: IDs & Sortierung vorgesehen.
- Ruhig: Fokus auf Sichtbarkeit, nicht Durchsetzung.

  

  

  

  

  

Nächster Schritt

  

  

- sim → Simulation mit virtual_files (liefert gates.json + report.json)
- freeze → Diese Gate-Konfiguration als Referenzzustand festhalten
- extend → Zusätzliches Mini-GatePack (z. B. projekt-spezifisch)

  

  

Sag einfach das gewünschte Stichwort.