{
  "summary": { "PASS": 5, "WARN": 1, "FAIL": 2, "NA": 42 },
  "results": [
    { "id": "G010", "level": "PASS", "message": "File count >= 1." },

    {
      "id": "G030",
      "level": "PASS",
      "message": "Frontmatter id present (id=2026010901).",
      "evidence": { "file": "notes/a.md", "id": 2026010901 }
    },
    {
      "id": "G031",
      "level": "PASS",
      "message": "Frontmatter id matches ^[0-9]{8,}$.",
      "evidence": { "file": "notes/a.md", "id": "2026010901" }
    },

    {
      "id": "G040",
      "level": "FAIL",
      "message": "Strict: broken links must be 0. Target 'notes/b' not found in virtual_files.",
      "evidence": { "broken_wikilinks": ["notes/b"] }
    },

    {
      "id": "G045",
      "level": "PASS",
      "message": "HUD enabled."
    },

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