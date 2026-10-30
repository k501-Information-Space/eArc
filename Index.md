# Index — eArc Root Navigation Directory

**Repository role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`  
**Repository authority:** `NONE`  
**Canonical authority:** `NONE`  
**Classification:** `DERIVED_ROOT_NAVIGATION_DIRECTORY`  
**Completeness:** `NON_EXHAUSTIVE_SELECTED_ROOT_ENTRYPOINTS`  
**Basis commit:** `c376f91ab2accf25927cb972bf0a4eeac4df5ffe`  
**Operator time anchor:** `1793389236` (2026-10-30T19:40:36Z)

This Index maps selected root entrypoints and declared top-level archive zones. It is not a recursive repository inventory, an object catalogue, a content checksum list, a validation result, a rights clearance or an authority declaration.

## Navigation entries

| Path | Declared class | Relation |
|---|---|---|
| `README.md` | `HUMAN_ENTRY` | `CURRENT_ROOT` |
| `Gateway.md` | `HUMAN_GATEWAY` | `COMMON_ROOT_ENTRYPOINT` |
| `Gateway.json` | `MACHINE_GATEWAY` | `COMMON_ROOT_ENTRYPOINT` |
| `Index.md` | `HUMAN_INDEX` | `COMMON_ROOT_ENTRYPOINT` |
| `Index.json` | `MACHINE_INDEX` | `COMMON_ROOT_ENTRYPOINT` |
| `GW__ROOT.json` | `LEGACY_MACHINE_GATEWAY` | `PRESERVED_HISTORICAL_ENTRYPOINT` |
| `INDEX.md` | `LEGACY_HUMAN_TOPOLOGY_INDEX` | `PRESERVED_HISTORICAL_SNAPSHOT` |
| `INDEX.json` | `LEGACY_MACHINE_TOPOLOGY_INDEX` | `PRESERVED_HISTORICAL_SNAPSHOT` |
| `EARC_NEUTRAL_ARCHIVE_MODEL_v1.0.md` | `NEUTRALITY_MODEL` | `GOVERNING_MODEL_HUMAN` |
| `EARC_NEUTRAL_ARCHIVE_MODEL_v1.0.json` | `NEUTRALITY_MODEL` | `GOVERNING_MODEL_MACHINE` |
| `EARC_INGEST_POLICY_v1.0.md` | `INGEST_POLICY` | `GOVERNING_POLICY_HUMAN` |
| `EARC_INGEST_POLICY_v1.0.json` | `INGEST_POLICY` | `GOVERNING_POLICY_MACHINE` |
| `EARC_OBJECT_RECORD_SCHEMA_v1.0.md` | `OBJECT_RECORD_SCHEMA` | `GOVERNING_SCHEMA_HUMAN` |
| `EARC_OBJECT_RECORD_SCHEMA_v1.0.json` | `OBJECT_RECORD_SCHEMA` | `GOVERNING_SCHEMA_MACHINE` |
| `EARC_REPOSITORY_STATE_ANCHOR_1793335241.md` | `STATE_ANCHOR` | `TIME_SCOPED_OBSERVATION_HUMAN` |
| `EARC_REPOSITORY_STATE_ANCHOR_1793335241.json` | `STATE_ANCHOR` | `TIME_SCOPED_OBSERVATION_MACHINE` |
| `EARC_NEUTRALITY_TRANSITION_1793335241.md` | `TRANSITION_RECORD` | `HISTORICAL_TRANSITION_HUMAN` |
| `EARC_NEUTRALITY_TRANSITION_1793335241.json` | `TRANSITION_RECORD` | `HISTORICAL_TRANSITION_MACHINE` |
| `EARC_NEUTRALITY_VALIDATION_1793335241.md` | `VALIDATION_RECORD` | `SCOPED_VALIDATION_HUMAN` |
| `EARC_NEUTRALITY_VALIDATION_1793335241.json` | `VALIDATION_RECORD` | `SCOPED_VALIDATION_MACHINE` |
| `RIGHTS_REGISTER.json` | `RIGHTS_REGISTER` | `EXPLICIT_PER_OBJECT_RIGHTS` |
| `LICENSE` | `LICENSE_INSTRUMENT` | `REPOSITORY_METADATA` |
| `LICENSE-CONTENT` | `LICENSE_INSTRUMENT` | `REPOSITORY_METADATA` |
| `raw/` | `ARCHIVE_ZONE` | `SOURCE_CORPUS` |
| `archive/` | `ARCHIVE_ZONE` | `HISTORICAL_STORAGE` |
| `src/` | `ARCHIVE_ZONE` | `DEVELOPMENT_CODE` |
| `include/` | `ARCHIVE_ZONE` | `DEVELOPMENT_INTERFACES` |
| `spec/` | `ARCHIVE_ZONE` | `WORKING_SPECIFICATIONS` |
| `semantic_ingest_v1/` | `DERIVED_DATA_ZONE` | `DERIVED_CHUNKS_AND_EMBEDDINGS` |
| `test_ingest_20/` | `TEST_DATA_ZONE` | `TEST_AND_INGEST_CORPUS` |
| `canonical/` | `LEGACY_NAMED_ZONE` | `NO_EARC_AUTHORITY` |

## Historical topology snapshot

The previous [INDEX.md](INDEX.md) / [INDEX.json](INDEX.json) pair remains unchanged. It records parent commit `0429b08b710252e4e83799b8e8d19f0705433a53`, with 4,516 Git blobs and 62 trees in that earlier snapshot. Those counts are not carried forward as current inventory values.

## Neutrality boundary

- eArc repository authority and canonical authority remain `NONE`.
- `canonical/` is a preserved legacy path name, not an eArc canonical zone.
- Source-declared claims remain provenance only; storage or navigation does not adopt them.
- Rights, privacy, provenance, integrity, content review and reproduction remain separate axes.
- No source object, archived file or historical declaration is modified by this Index.
