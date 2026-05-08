{
  "bootframe": {
    "id": "K501-BOOTFRAME-DEV-ALPHA-v1",
    "decl": "BOOTFRAME",
    "mode": "DEVELOPMENT",
    "policy": "APPEND_ONLY",
    "license": "PUBLIC_DOMAIN",

    "time": {
      "ts_utc": "2026-03-03T15:13:54Z",
      "ts_unix": 1772550834,
      "time_policy": "UTC+UNIX_REQUIRED"
    },

    "canon": {
      "canonicalization": "RFC8785/JCS",
      "encoding": "UTF-8",
      "json_standard": "RFC8259",
      "transport": "NDJSON",
      "ndjson_rules": [
        "one-json-per-line",
        "no-crlf-inside-json",
        "utf8-only"
      ]
    },

    "hash": {
      "algorithm": "SHA-256",
      "standard": "NIST FIPS 180-4",
      "format": "hex-lower",
      "prefix": "SHA256:"
    },

    "hard_index": {
      "status": "BYTE_PROOFED",
      "artifact": "hard_index.payload.jcs.json",
      "bytes": 808,
      "sha256": "SHA256:17017ad18e63107bcb73d7b45c9687b1b17c568cc100eae26656bff134784556",
      "anchor_ts_unix": 1772546620
    },

    "bootframe_sim_reference": {
      "status": "BYTE_PROOFED",
      "artifact": "bootframe.sim.jcs.json",
      "bytes": 391,
      "sha256": "SHA256:c2f803027fe0bf26dddad28752cf42ed0ac5596d483c8f4eeba315714436bc4c"
    },

    "pack_reference": {
      "artifact": "pack_bootframe_sim.ndjson",
      "bytes": 953,
      "sha256": "SHA256:39a8e196b1836af2983ca3ea8d6e7b883724f9c66c50657453ccbd9bcf9e30bf",
      "pack_policy": "APPEND_ONLY_NDJSON"
    },

    "verification_rules": {
      "must": [
        "time-anchor-present-or-unknown",
        "append-only-frame-order",
        "jcs-key-sort",
        "utf8-encoding",
        "sha256-over-canonical-bytes"
      ],
      "must_not": [
        "NaN",
        "Infinity",
        "lone-surrogates",
        "whitespace-variant-canonical-json"
      ]
    },

    "development_state": {
      "stage": "ALPHA",
      "determinism": "CONFIRMED_LOCAL",
      "cross_engine_status": "PARTIAL",
      "byte_proof": "CONFIRMED",
      "intended_use": [
        "LLM validation",
        "NDJSON pack verification",
        "local iSH reproducibility",
        "development pipeline stabilization"
      ]
    },

    "notes": [
      "This is a DEVELOPMENT bootframe.",
      "All referenced artifacts are locally byte-verified.",
      "Any modification requires new frame and new hash.",
      "Designed for ChatGPT/Gemini validation workflows."
    ]
  }
}