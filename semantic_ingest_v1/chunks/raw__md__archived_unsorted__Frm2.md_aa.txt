
{
  "id": "EXP-20260114-090005Z-0002",
  "utc": "2026-01-14T09:00:05Z",
  "source": "chat://session",
  "type": "export_system_states_and_policies",
  "status": "analysis_reference",
  "payload": {
    "system_states": [
      {
        "system": "ARCHIVAT0R",
        "kernel": "K501",
        "version": "SINGULARITY",
        "time_base": "UTC_ZULU",
        "canon": true,
        "freeze": "ON",
        "execution": "BLOCKED",
        "comm": "OFF",
        "mode": "APPEND_ONLY",
        "drift": "NONE",
        "integrity": "PRESERVED",
        "notes": [
          "Kernel ist Spezifikation (read-only)",
          "Keine Ausführung im Chat",
          "Anzeige triggert keine Aktion"
        ]
      }
    ],
    "core_policies": [
      {
        "name": "PoF+PoC Double Confirmation",
        "rules": [
          "Kein Output als FACT ohne Mehrfach-Referenz",
          "Geprüft != Fakt",
          "Unsicherheit muss explizit markiert werden"
        ],
        "procedure": [
          "Interne Referenz prüfen (kann veraltet sein)",
          "Bei Unsicherheit externe Referenzen abfragen",
          "Vergleich durchführen",
          "Klassifizieren: UNVERIFIED | VERIFIED | FACT",
          "FACT nur bei Konsistenz"
        ]
      },
      {
        "name": "Append-Only / No-Mutation",
        "rules": [
          "Logs nur anhängen",
          "Frames write-once",
          "Index existence+links only"
        ]
      },
      {
        "name": "Time as Reference",
        "rules": [
          "UTC_ZULU als Primärreferenz",
          "Lokale Zeiten nur abgeleitet",
          "Zeitangaben ohne Verifikation nicht als Fakt"
        ]
      }
    ],
    "references": {
      "root": "EXP-20260114-090000Z-ROOT"
    }
  }
}