{
  "summary": { "PASS": 6, "WARN": 1, "FAIL": 1, "NA": 42 },
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
      "level": "FAIL",
      "message": "Strict: limits.time_budget_ms must be set."
    },

    {
      "id": "G014",
      "level": "WARN",
      "message": "Strict recommends hashing; hashing is disabled."
    }
  ]
}