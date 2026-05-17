{
  "summary": { "PASS": 1, "WARN": 1, "FAIL": 0, "NA": 0 },
  "results": [
    { "id": "G001", "title": "Out directory writable", "level": "PASS" },
    {
      "id": "G010",
      "title": "Frontmatter id present where YAML frontmatter exists",
      "level": "WARN",
      "evidence": { "files": ["notes/a.md", "notes/b.md"], "missing_field": "id" },
      "message": "Some frontmatter blocks have no id"
    }
  ]
}