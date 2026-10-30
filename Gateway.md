# Gateway — eArc Neutral Development Archive

**Repository role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`  
**Repository authority:** `NONE`  
**Canonical authority:** `NONE`  
**Gateway classification:** `NAVIGATION_ONLY`  
**Operator time anchor:** `1793389236` — 2026-10-30T19:40:36Z / 2026-10-30T20:40:36+01:00

## Common root entrypoints

- [README.md](README.md) — repository role, archive policy and entry sequence.
- [Gateway.json](Gateway.json) — machine-readable routes and neutrality boundaries.
- [Index.md](Index.md) / [Index.json](Index.json) — non-exhaustive root navigation directory; not a recursive file inventory.
- [EARC_NEUTRAL_ARCHIVE_MODEL_v1.0.md](EARC_NEUTRAL_ARCHIVE_MODEL_v1.0.md) / [machine model](EARC_NEUTRAL_ARCHIVE_MODEL_v1.0.json) — governing neutrality model.
- [EARC_INGEST_POLICY_v1.0.md](EARC_INGEST_POLICY_v1.0.md) / [machine policy](EARC_INGEST_POLICY_v1.0.json) — intake and publication sequence.
- [EARC_OBJECT_RECORD_SCHEMA_v1.0.md](EARC_OBJECT_RECORD_SCHEMA_v1.0.md) / [machine schema](EARC_OBJECT_RECORD_SCHEMA_v1.0.json) — object-level record structure.
- [RIGHTS_REGISTER.json](RIGHTS_REGISTER.json) — explicit per-object rights register.

## Preserved historical entrypoints

- [GW__ROOT.json](GW__ROOT.json) — preserved prior machine Gateway record. It is not replaced by this common root Gateway.
- [INDEX.md](INDEX.md) / [INDEX.json](INDEX.json) — preserved historical topology capture based on parent commit `0429b08b710252e4e83799b8e8d19f0705433a53`, recording 4,516 Git blobs and 62 trees. These values describe that parent snapshot only; they are not a current eArc inventory.

## Neutrality

This Gateway does not approve, canonize, validate, endorse, select or establish currentness for any archived object. Source-declared status is preserved as a claim from its own originating context. eArc authority is always `NONE`.

A source artefact may be canonical in its own originating authority context. Its storage, indexing, hashing or linking in eArc does not confer or adopt that authority.

## Areas

- `raw/`: original source corpus and imports.
- `archive/`: historical storage, binaries, manifests and topology captures.
- `src/`, `include/`: development code, including historical and experimental material.
- `spec/`: working specifications and research.
- `semantic_ingest_v1/`: derived chunks/embeddings, not source replacements.
- `test_ingest_20/`: test and ingest corpus.
- `canonical/`: legacy path name only; not a canonical zone in eArc.
- Underscore-prefixed paths: time-scoped historical analysis, freeze, audit, merge and topology records.

## State and validation records

- [Repository state anchor](EARC_REPOSITORY_STATE_ANCHOR_1793335241.md) / [machine record](EARC_REPOSITORY_STATE_ANCHOR_1793335241.json).
- [Neutrality transition](EARC_NEUTRALITY_TRANSITION_1793335241.md) / [machine record](EARC_NEUTRALITY_TRANSITION_1793335241.json).
- [Neutrality validation](EARC_NEUTRALITY_VALIDATION_1793335241.md) / [machine record](EARC_NEUTRALITY_VALIDATION_1793335241.json).

## Rights and reproduction

`LICENSE` and `LICENSE-CONTENT` are instruments with distinct scopes. Exact grants are listed in `RIGHTS_REGISTER.json`; the default is `RIGHTS_OPEN`, and no folder-wide grants apply. Integrity, provenance, rights, privacy, content review and reproduction remain separate axes.

## Invariants

Preserve origin claims as claims. Never expose an eArc `CANONICAL` status. Keep provenance, integrity, rights, privacy, review and reproduction as separate axes. Preserve exact paths and historical versions. Unknown remains unknown.

K501 :: TRACEABILITY_REQUIRED  
K501 :: PRESERVE_HISTORY  
K501 :: PROOF_BEFORE_STATE
