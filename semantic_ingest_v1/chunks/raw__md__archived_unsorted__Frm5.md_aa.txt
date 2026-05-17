{
  "id": "EXP-20260114-090020Z-0005",
  "utc": "2026-01-14T09:00:20Z",
  "source": "chat://session",
  "type": "export_new_standards_folder_declaration",
  "status": "analysis_reference",
  "payload": {
    "declaration": {
      "name": "NEW_STANDARDS_ARCHIVE",
      "purpose": "Isolate and preserve the latest canonical standards without legacy confusion",
      "scope": [
        "Frame formats",
        "Frame-stamps (id/utc/source/type)",
        "JSON schemas",
        "NDJSON logs",
        "Index existence+links",
        "PoF+PoC policies",
        "Append-only / No-mutation rules"
      ],
      "freeze": {
        "enabled": true,
        "changes_require": "explicit future unfreeze declaration"
      }
    },
    "recommended_local_structure": [
      "00_STANDARDS/",
      "01_FRAMES/",
      "02_LOGS/",
      "03_INDEX/",
      "04_EXPORTS/",
      "README.md (human-readable explanation)"
    ],
    "governance": {
      "canon_source": "NEW_STANDARDS_ARCHIVE",
      "legacy": "read-only, no imports unless explicitly mapped"
    },
    "references": {
      "root": "EXP-20260114-090000Z-ROOT",
      "prev": "EXP-20260114-090015Z-0004"
    }
  }
}