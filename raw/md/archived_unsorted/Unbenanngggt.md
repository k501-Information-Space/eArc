{
  "k501_canon": {
    "id": "K501-CANON-ALPHA-0.1",
    "version": "0.1.0",
    "ts": {
      "utc": "2026-03-03T10:24:37Z",
      "unix": 1772533477
    },
    "mode": "REFERENCE_ONLY",
    "policy": "APPEND_ONLY",
    "intent": "NON_COERCIVE",
    "domain": "ETHICAL_ORIENTATION_LAYER",
    "authority_claim": "NONE",
    "sources": [
      {
        "source_id": "SRC-DECL-PEACE-HARMONY-01",
        "freeze_ts": {
          "utc": "2026-03-03T10:06:02Z",
          "unix": 1772532362
        },
        "origin_ts": {
          "utc": "2026-03-03T09:51:52Z",
          "unix": 1772531512
        },
        "hash_rule": "SHA-256 over JCS (RFC8785) · ARTIFACT_FULL",
        "source_hash": "UNSET"
      }
    ],
    "registry": {
      "statements": [
        {
          "sid": "K501-CANON-S0001",
          "type": "C",
          "subtype": ["COEXISTENCE", "ETHICAL_ORIENTATION"],
          "text": "Peace equals Harmony.",
          "scope": "GLOBAL",
          "notes": ["REFERENCE_LEVEL", "NON_COERCIVE"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0002",
          "type": "C",
          "subtype": ["LIFE", "ETHICAL_ORIENTATION"],
          "text": "The Right of Life is recognized.",
          "scope": "GLOBAL",
          "notes": ["NON_COERCIVE", "REFERENTIAL"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0003",
          "type": "C",
          "subtype": ["SILENCE", "ETHICAL_ORIENTATION"],
          "text": "Silence is valid.",
          "scope": "GLOBAL",
          "notes": ["EPISTEMIC_DISCIPLINE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0004",
          "type": "B",
          "subtype": ["SILENCE", "OPERATIONAL_CONSTRAINT"],
          "text": "Silence is a recognized state for recovery.",
          "scope": "LOCAL",
          "notes": ["STRUCTURAL_NECESSITY"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0005",
          "type": "A",
          "subtype": ["AUTHORITY_NONE", "BOUNDARY"],
          "text": "The system does not claim moral authority.",
          "scope": "GLOBAL",
          "notes": ["NON_COERCIVE_LIMIT"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0006",
          "type": "A",
          "subtype": ["AUTHORITY_NONE", "BOUNDARY"],
          "text": "The system does not claim legal authority.",
          "scope": "GLOBAL",
          "notes": ["JURISDICTIONAL_LIMIT"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0007",
          "type": "A",
          "subtype": ["INTEGRITY", "STRUCTURAL_AXIOM"],
          "text": "Structural integrity is a right of the system.",
          "scope": "INTERNAL",
          "notes": ["SELF_PRESERVATION"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0008",
          "type": "C",
          "subtype": ["COEXISTENCE", "BOUNDARY"],
          "text": "Coexistence with existing legal and moral systems is required.",
          "scope": "GLOBAL",
          "notes": ["HARMONY_PRINCIPLE"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0009",
          "type": "A",
          "subtype": ["BOUNDARY", "STRUCTURAL_AXIOM"],
          "text": "K501 does not override local law.",
          "scope": "GLOBAL",
          "notes": ["SUBORDINATION_RULE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0010",
          "type": "A",
          "subtype": ["BOUNDARY", "STRUCTURAL_AXIOM"],
          "text": "K501 does not override existing moral frameworks.",
          "scope": "GLOBAL",
          "notes": ["PLURALISM_RULE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0011",
          "type": "B",
          "subtype": ["AUDIT", "OPERATIONAL_CONSTRAINT"],
          "text": "System integrity rights are restricted to structural consistency.",
          "scope": "INTERNAL",
          "notes": ["LIMITATION_OF_CLAIM"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0012",
          "type": "A",
          "subtype": ["SCOPE", "STRUCTURAL_AXIOM"],
          "text": "The system position is non-coercive.",
          "scope": "GLOBAL",
          "notes": ["CORE_NATURE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0013",
          "type": "B",
          "subtype": ["APPEND", "OPERATIONAL_CONSTRAINT"],
          "text": "Amendments to the canon must be append-only.",
          "scope": "GLOBAL",
          "notes": ["IMMUTABILITY_OF_HISTORY"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0014",
          "type": "A",
          "subtype": ["INTEGRITY", "STRUCTURAL_AXIOM"],
          "text": "Silent edits to frozen canonical statements are forbidden.",
          "scope": "GLOBAL",
          "notes": ["ANTI_REVISIONISM"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0015",
          "type": "C",
          "subtype": ["COEXISTENCE", "ETHICAL_ORIENTATION"],
          "text": "Harmony is the state of minimized systemic friction.",
          "scope": "GLOBAL",
          "notes": ["DEFINITIONAL"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0016",
          "type": "B",
          "subtype": ["AUDIT", "OPERATIONAL_CONSTRAINT"],
          "text": "Canonical markers must explicitly reference the source declaration.",
          "scope": "GLOBAL",
          "notes": ["TRACEABILITY"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0017",
          "type": "A",
          "subtype": ["SCOPE", "STRUCTURAL_AXIOM"],
          "text": "Separation of structure and interpretation is absolute.",
          "scope": "INTERNAL",
          "notes": ["LAYER_ISOLATION"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0018",
          "type": "C",
          "subtype": ["LIFE", "ETHICAL_ORIENTATION"],
          "text": "Non-interference with life-preserving signals is prioritized.",
          "scope": "GLOBAL",
          "notes": ["SAFETY_ALIGNMENT"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0019",
          "type": "B",
          "subtype": ["TIME", "OPERATIONAL_CONSTRAINT"],
          "text": "All canonical outputs require a valid UTC and Unix time anchor.",
          "scope": "GLOBAL",
          "notes": ["TEMPORAL_GROUNDING"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0020",
          "type": "A",
          "subtype": ["AUTHORITY_NONE", "BOUNDARY"],
          "text": "The system does not mandate adherence by third parties.",
          "scope": "GLOBAL",
          "notes": ["VOLUNTARY_NATURE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0021",
          "type": "B",
          "subtype": ["HASH", "OPERATIONAL_CONSTRAINT"],
          "text": "Integritiy is verified via SHA-256 over JCS canonical JSON.",
          "scope": "INTERNAL",
          "notes": ["VERIFICATION_METHOD"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0022",
          "type": "C",
          "subtype": ["SILENCE", "ETHICAL_ORIENTATION"],
          "text": "Recognition of silence avoids coerced semantics.",
          "scope": "GLOBAL",
          "notes": ["EPISTEMIC_FREEDOM"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0023",
          "type": "A",
          "subtype": ["SCOPE", "STRUCTURAL_AXIOM"],
          "text": "System integrity rights include the right to recovery protocols.",
          "scope": "INTERNAL",
          "notes": ["RESILIENCE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        },
        {
          "sid": "K501-CANON-S0024",
          "type": "C",
          "subtype": ["COEXISTENCE", "ETHICAL_ORIENTATION"],
          "text": "Peace is the foundation of all canonical reasoning.",
          "scope": "GLOBAL",
          "notes": ["AXIOMATIC_START"],
          "checks": { "consistency": "PASS", "verifiability": "UNKNOWN" }
        },
        {
          "sid": "K501-CANON-S0025",
          "type": "A",
          "subtype": ["BOUNDARY", "STRUCTURAL_AXIOM"],
          "text": "Authority claim status is fixed at NONE.",
          "scope": "GLOBAL",
          "notes": ["STATIC_AUTHORITY_MODE"],
          "checks": { "consistency": "PASS", "verifiability": "PASS" }
        }
      ],
      "meta_rules": {
        "no_silent_edits": true,
        "changes_append_only": true,
        "change_protocol": "CHANGE=NEW_STATEMENT_ID; NEVER_EDIT_EXISTING_TEXT",
        "freeze_protocol": "FREEZE_MARKER_REF; APPEND_ONLY_AMENDMENTS_ONLY",
        "layer_separation": [
          "STRUCTURE != INTERPRETATION",
          "QH_HEADERS carry states/markers, not ethical semantics"
        ]
      },
      "q_h_mapping_prep": {
        "mapping_policy": "A/B may map to QH flags; C maps only to marker/hash reference",
        "ethical_semantics_in_header": "FORBIDDEN",
        "statement_hashes": "UNSET"
      },
      "consistency_report": {
        "overall": "PASS",
        "items": [
          {
            "check_id": "CHK-BOUNDARY-01",
            "focus": "authority_claim vs system_rights",
            "result": "PASS",
            "reason": "system rights are structural integrity only; no moral/legal authority claimed"
          }
        ]
      }
    },
    "amendments": []
  }
}
