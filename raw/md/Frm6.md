{
  "id": "EXP-20260114-090025Z-0006",
  "utc": "2026-01-14T09:00:25Z",
  "source": "chat://session",
  "type": "export_closure_integrity_handover",
  "status": "analysis_reference",
  "payload": {
    "integrity_proof": {
      "no_information_loss": true,
      "append_only_sequence": true,
      "frame_order_verified": [
        "EXP-20260114-090000Z-ROOT",
        "EXP-20260114-090005Z-0002",
        "EXP-20260114-090010Z-0003",
        "EXP-20260114-090015Z-0004",
        "EXP-20260114-090020Z-0005",
        "EXP-20260114-090025Z-0006"
      ],
      "references_intact": true,
      "mutation_detected": false
    },
    "handover": {
      "recipient": "user (local archive)",
      "action": "copy_paste_store",
      "next_steps": [
        "Store frames sequentially in NEW_STANDARDS_ARCHIVE/01_FRAMES",
        "Optionally generate local index (existence+links)",
        "Proceed with APK PoC execution outside chat"
      ]
    },
    "final_notes": [
      "Chat environment used as temporary interpreter only",
      "Kernel remains read-only specification",
      "All future FACTs require PoF verification"
    ],
    "references": {
      "root": "EXP-20260114-090000Z-ROOT",
      "prev": "EXP-20260114-090020Z-0005"
    }
  }
}