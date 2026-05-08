✅ SIM STRICT – Final Rerun (mit hud.enabled: true, notes/a.md, notes/b.md, und limits.time_budget_ms: 60000)

  

Jetzt sollte Strict 0 FAIL erreichen. Hashing bleibt in Strict nur WARN (Empfehlung), nicht FAIL.

  

  

  

  

out/gates.json (Strict) – FINAL

  

{

  "summary": { "PASS": 7, "WARN": 1, "FAIL": 0, "NA": 42 },

  "results": [

    { "id": "G010", "level": "PASS", "message": "File count >= 1." },

  

    {

      "id": "G030",

      "level": "PASS",

      "message": "Frontmatter id present (notes/a.md, notes/b.md).",

      "evidence": { "files": ["notes/a.md", "notes/b.md"] }

    },

    {

      "id": "G031",

      "level": "PASS",

      "message": "Frontmatter id matches ^[0-9]{8,}$ (notes/a.md, notes/b.md).",

      "evidence": { "files": ["notes/a.md", "notes/b.md"] }

    },

  

    {

      "id": "G040",

      "level": "PASS",

      "message": "Broken links = 0 (strict).",

      "evidence": { "checked_wikilinks": ["notes/b"], "broken": [] }

    },

  

    { "id": "G045", "level": "PASS", "message": "HUD enabled." },

  

    {

      "id": "G050",

      "level": "PASS",

      "message": "limits.time_budget_ms set.",

      "evidence": { "time_budget_ms": 60000 }

    },

  

    {

      "id": "G014",

      "level": "WARN",

      "message": "Strict recommends hashing; hashing is disabled."

    }

  ]

}

  

  

  

  

out/hud.json – FINAL

  

{

  "kernel": { "name": "SoftK501Dev", "version": "0.1.0", "build": "dev" },

  "target": ".",

  "summary": { "files_total": 2, "nodes": 6, "edges": 1, "WARN": 1, "FAIL": 0 },

  "top_warnings": [

    { "gate": "G014", "hint": "Optionally enable scan.hashing.enabled for integrity." }

  ],

  "graph_stats": { "nodes": 6, "edges": 1 }

}

  

  

  

  

out/report.json – FINAL

  

{

  "run": {

    "id": "sim-virtual-strict-final",

    "mode": "run",

    "target": ".",

    "profile": "default",

    "confirm": "yes"

  },

  "kernel": { "name": "SoftK501Dev", "version": "0.1.0", "build": "dev" },

  "gatepack": "k501-gatepack-strict-v0.1",

  "status": {

    "result": "PASS_STRICT_WITH_WARNINGS",

    "PASS": 7,

    "WARN": 1,

    "FAIL": 0,

    "NA": 42

  }

}

  

  

  

  

Ergebnis

  

  

- ✅ Strict: PASS
- ⚠️ 1 Warnung (Hashing-Empfehlung, optional)

  

  

Wenn du willst, kann ich jetzt:

  

- freeze strict (Strict-SIM als Referenz einfrieren)
- export strict tar (Bundle wie vorhin, aber strict-final)
- enable hashing (DSL-Minimaländerung + rerun)