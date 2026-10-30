# eArc — Neutral K501 Development Archive

**Repository role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`  
**Repository authority:** `NONE`  
**Canonical authority:** `NONE`

eArc is the neutral, append-only development archive for the historical and evolving K501 work corpus. It preserves workspaces, code fragments, experimental QH256 cores, QH256 implementations and validations, pipeline/runtime releases, specifications, publications, conversation exports, tests, binaries, reports and derived artefacts.

**eArc is not the canonical K501 repository. Nothing becomes canonical inside eArc.** Storage, indexing, hashing, a Gateway link or a source file's own declaration cannot confer eArc authority.

A document may declare `CANONICAL`, `VALIDATED`, `RELEASED` or `CURRENT` in its original context. eArc preserves that only as a source-declared claim with provenance. For example, a QH256 v2 validation package may be canonical in its own QH256 authority context; in eArc it is an archived `VALIDATION_ARTEFACT`, not a canonical eArc object.

Old K501 files containing canonical declarations remain historical development artefacts. Their source text is preserved without adoption.

## Entry points

- `Gateway.md` / `GW__ROOT.json` — navigation.
- `INDEX.md` / `INDEX.json` — observed topology.
- `EARC_NEUTRAL_ARCHIVE_MODEL_v1.0.md/.json` — neutrality model.
- `EARC_INGEST_POLICY_v1.0.md/.json` — intake and publication policy.
- `EARC_OBJECT_RECORD_SCHEMA_v1.0.md/.json` — object record schema.
- `EARC_REPOSITORY_STATE_ANCHOR_1793335241.md/.json` — scoped repository observation.
- `EARC_NEUTRALITY_TRANSITION_1793335241.md/.json` — terminology and policy transition.
- `EARC_NEUTRALITY_VALIDATION_1793335241.md/.json` — validation scope and open issues.

## Existing zones

| Path | Neutral role |
|---|---|
| `raw/` | Source corpus and imports |
| `archive/` | Historical storage, binaries, manifests and topology |
| `src/`, `include/` | Development code artefacts, including historical/experimental |
| `spec/` | Working specifications and research texts |
| `semantic_ingest_v1/` | Derived chunks, embeddings and reports |
| `test_ingest_20/` | Test/ingest corpus |
| `canonical/` | Legacy path name only; contents are development artefacts with no eArc authority |
| underscore-prefixed root paths | Historical analysis, freeze, audit, merge and topology records |

Paths and filenames are preserved. No directory name is an authority boundary. No automatic move, rename, deduplication or version selection is implied.

## Rights

`LICENSE` (MIT) and `LICENSE-CONTENT` (CC BY 4.0) are separate instruments. They apply only to exact objects explicitly listed in `RIGHTS_REGISTER.json`, and only where the grantor has the necessary rights. Unregistered material defaults to `RIGHTS_OPEN`.

Historical source code, workspaces, conversations, old QH256 cores, pipeline/runtime imports, publications, archive objects and derived outputs are not automatically licensed by repository presence or path. See `LICENSE_MAP.md`, `RIGHTS_REGISTER.json` and `THIRD_PARTY_NOTICES.md`.

## Public ingestion

Bulk imports are staged and reviewed before public publication. Conversations/workspaces may contain credentials, personal information, confidential material or third-party content. Unresolved rights, privacy or secret-scanning issues block public admission. Redacted/normalized copies are derivatives, not originals.

## Continuity

Preserve source objects and origin claims. Separate sources, ingestion events, archive metadata, derivatives, observations and interpretations. Keep versions side by side. Distinguish Git blob IDs, LFS pointers and payload hashes. Hashes prove byte identity, not authorship, truth, authority or licence. Unknown remains explicit.

K501 :: PRESERVE_HISTORY  
K501 :: UNKNOWN_BY_DEFAULT  
K501 :: NO_INTERPRETATION  
K501 :: PROOF_BEFORE_STATE  
K501 :: RECONSTRUCT_BEFORE_EXTEND
