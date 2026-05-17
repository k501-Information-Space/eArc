BOOTFRAME{
  "name": "K501 Technical Core BootFrame",
  "version": "1.5",
  "status": "REFERENCE_ONLY|APPEND_ONLY|STRUCTURAL",

  "canonical": {
    "website": "https://iinkognit0.de",
    "zenodo_base": "https://zenodo.org/records/18615245",
    "concept_doi": "10.5281/zenodo.18511613"
  },

  "identity": {
    "framework": "K501 Frames",
    "author": "Patrick R. Miller",
    "orcid": "0009-0005-5125-9711",
    "contact": "iinkognit0@proton.me"
  },

  "core_policy": {
    "append_only": true,
    "mutation": "forbidden",
    "interpretation_layer": "external",
    "execution": "none",
    "deterministic_serialization": "required",
    "time_anchor": ["utc_iso8601", "unix_epoch"]
  },

  "frame_requirements": {
    "frame_id": "required_unique",
    "time_utc": "ISO-8601-Z",
    "time_unix": "integer_seconds",
    "hash_binding": "SHA-256",
    "serialization": "RFC8785_JCS"
  },

  "integration_model": {
    "mode": "encapsulation",
    "replaces_systems": false,
    "scope": "repository_neutral_structural_layer"
  },

  "v1_5_document_set": [
    "K501 — Structural Integration Specification (v1.5)",
    "K501 — Formal Mathematical Abstraction (v1.5)",
    "K501 — Minimal Integration & Compliance (v1.5)",
    "K501 — Canonical Serialization & Time Anchoring (v1.5)",
    "K501 Frames — Provenance and Snapshot Semantics (v1.5)",
    "K501 Frames — Interoperability and Repository Neutrality (v1.5)",
    "K501 — Technical Core Index (v1.5)"
  ],

  "delta_H_policy": {
    "principle": "DELTA_H_EQUALS_ZERO",
    "meaning": "structural_invariance_under_append",
    "note": "instance_growth_without_rule_change"
  },

  "timekeeper": {
    "required": false,
    "compatible_with": "K501-Timekeeper-v1.x",
    "role": "external_temporal_consensus_optional"
  }
}