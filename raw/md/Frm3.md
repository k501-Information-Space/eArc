{
  "id": "EXP-20260114-090010Z-0003",
  "utc": "2026-01-14T09:00:10Z",
  "source": "chat://session",
  "type": "export_frames_logs_findings",
  "status": "analysis_reference",
  "payload": {
    "frames_summary": [
      {
        "category": "analysis_frames",
        "items": [
          "analysis_mode_set",
          "log_channels_declared",
          "time_reference_frame",
          "poc_plan_selected",
          "ios_storage_constraint_findings",
          "external_storage_integration"
        ],
        "notes": "Alle Analyseframes sind write-once und referenzieren UTC_ZULU."
      },
      {
        "category": "decision_frames",
        "items": [
          "proof_policy_standard",
          "android_archivator_atom_confirmed",
          "poc_testplan_confirmed"
        ],
        "notes": "Bestätigungen durch Nutzer = FACT, sonst analysis_reference."
      }
    ],
    "logs_summary": [
      {
        "log": "analysis.log",
        "events": [
          "BOOT_ACKNOWLEDGED",
          "ANALYSIS_MODE_STRICT",
          "POLICY_SET_POF_POC",
          "EXPORT_SEQUENCE_STARTED"
        ],
        "properties": {
          "append_only": true,
          "mutation": "forbidden"
        }
      },
      {
        "log": "io.log",
        "events": [
          "NO_REAL_IO_IN_CHAT",
          "IOS_SANDBOX_CONSTRAINT_CONFIRMED"
        ]
      },
      {
        "log": "poc.log",
        "events": [
          "POC_TESTPLAN_DEFINED",
          "POC_EXECUTION_OUTSIDE_CHAT"
        ]
      }
    ],
    "key_findings": [
      "Archivator ohne Speicher ist nur ein Denkmodell",
      "Referenz entsteht durch Relation/Netzwerk, nicht Einzelinstanz",
      "Zeitangaben ohne Mehrfachabgleich dürfen nicht als Fakt gelten",
      "ChatGPT ist kein Archivator-Knoten, sondern temporärer Interpreter",
      "Reale Archivator-Atome benötigen lokalen Speicher + IO"
    ],
    "references": {
      "root": "EXP-20260114-090000Z-ROOT",
      "prev": "EXP-20260114-090005Z-0002"
    }
  }
}

