{
  "id": "EXP-20260114-090015Z-0004",
  "utc": "2026-01-14T09:00:15Z",
  "source": "chat://session",
  "type": "export_implementation_paths_storage",
  "status": "analysis_reference",
  "payload": {
    "android": {
      "role": "primary_archivator_atom",
      "storage": {
        "filesystem": "app sandbox (internal)",
        "logs": "NDJSON append-only",
        "frames": "JSON write-once",
        "index": "NDJSON (existence + links)"
      },
      "io": [
        "Share Intent",
        "File Picker",
        "Bluetooth/WLAN (optional later)"
      ],
      "poc_status": "ready_for_execution_outside_chat"
    },
    "ios": {
      "constraints": "strict sandboxing",
      "options": [
        "Files app locations (On My iPhone) when supported",
        "Third-party file manager apps with local containers",
        "Dedicated iOS app for true Archivator behavior"
      ],
      "note": "Chat environment cannot persist data on-device"
    },
    "web_db": {
      "asset": "iinkognit0.de",
      "capacity": "250GB (user-provided)",
      "db_choices": ["MariaDB", "SQL"],
      "recommended_schema": [
        "arc_logs (append-only events)",
        "arc_frames (frame metadata pointers)",
        "arc_index (existence + links mirror)",
        "wp_main (if website CMS is used)"
      ],
      "role": "external persistence & sync target (optional)",
      "separation_rule": "kernel spec remains read-only"
    },
    "references": {
      "root": "EXP-20260114-090000Z-ROOT",
      "prev": "EXP-20260114-090010Z-0003"
    }
  }
}