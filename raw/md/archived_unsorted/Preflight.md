  

Build Schritt 4 · Preflight Validation (Fail-Fast)

  

  

Ziel: Bevor irgendein Artefakt entsteht, läuft der Preflight: Schema, Scope, Strings, Ausschlüsse, Transitions, Surfaces, Archiv-Regeln.

  

  

4.1 Validations (logische Reihenfolge)

  

  

1. Schema-Check

  

  

  

- kernel/src/kernel.yaml enthält alle Pflichtfelder
- type: kernel, scope: dev_alpha, kanon: ja

  

  

  

2. Builder-Meta-Check

  

  

  

- builder.id == kernel_builder_2_9
- builder.version == 2.9

  

  

  

3. Scope-Schutz / String-Scan

  

  

  

- Kernel-Text enthält kein public_alpha
- Endpunkte haben kein public/ Präfix

  

  

  

4. Release-Surfaces-Check

  

  

  

- keys: feeds/endpoints/export/artifacts vorhanden
- Werte ∈ {enabled, disabled}
- dev_alpha defaults = enabled (bei dir gesetzt)

  

  

  

5. Exclusions-Check (forbidden_features)

  

  

  

- Kernel enthält keine Social/Ranking/Push/Realtime-Chat/App-Store-Strategie als Feature

  

  

  

6. State Machine Check

  

  

  

- erlaubte Transitions exakt:  
    ingested→held, held→released, released→archived
- keine Rücksprünge erlaubt

  

  

  

7. Archiv-Check

  

  

  

- archived = immutable
- mutation_policy = revision_only

  

  

  

4.2 Preflight Output (was Builder 2.9 erzeugt, bevor er baut)

  

  

- kernel/reports/build_report_kernel_5000_dev_alpha_v4.1.json  
    

- status: success oder fail
- bei fail: keine Artefakte in dist/

-   
    

  

  

  

4.3 Dein Kontrollpunkt

  

  

Wenn du sagst weiter, gilt:

✅ Preflight ist bestanden → wir gehen in Schritt 5: Build (Artefakte + Hashes + Report final).

  

weiter