# eArc — Neutral Archive Index

**Index type:** observed repository topology; descriptive only.  
**Repository role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`.  
**Authority:** `NONE`.  
**Parent commit/tree:** `0429b08b710252e4e83799b8e8d19f0705433a53`.  
**Operator time anchor:** `1793335241`.

This index records locations and counts. It does not classify authority,
establish canonicality, validate content, clear rights or select a current version.

## Parent inventory

- Git blobs: 4,516.
- Git trees/directories: 62.
- Recursive API response: not truncated.
- Git LFS payloads: not downloaded for this index.

## Main areas

| Path | Files | Neutral archival description |
|---|---:|---|
| `.vscode/` | 3 | Editor/debug/build configuration |
| `_ANALYSIS/` | 1 | Historical analysis |
| `_FREEZE_CANONICAL/` | 4 | Historical freeze records carrying source terminology |
| `_FREEZE_STATE/` | 2 | Historical state |
| `_REMOTE_TREE/` | 4 | Historical tree captures |
| `_mainline_freeze/` | 7 | Historical mainline freeze |
| `_merge_preparation/` | 7 | Historical merge preparation |
| `_namespace_normalization/` | 5 | Historical namespace records |
| `_remote_audit/` | 10 | Historical remote audit |
| `_runtime_seal/` | 4 | Historical runtime seal |
| `_topology_map/` | 6 | Historical topology |
| `archive/` | 12 | Historical storage and topology |
| `canonical/` | 14 | Legacy path name only; development artefacts; eArc authority NONE |
| `include/` | 6 | Development code interfaces; rights open |
| `raw/` | 2,367 | Source corpus and imports |
| `semantic_ingest_v1/` | 2,009 | Derived chunk/embedding/report artefacts |
| `spec/` | 7 | Development specifications |
| `src/` | 6 | Development code including experimental/history |
| `test_ingest_20/` | 20 | Test/ingest corpus |

The counts describe the parent tree only, not semantic content or legal status.

## Source and derivative areas

Observed raw subareas include `raw/docx/`, `raw/md/AIONARC_KANON/`,
`raw/md/archived_unsorted/`, `raw/md/bootframes/`,
`raw/md/chatGPT_converastions/`, `raw/md/kernel/`,
`raw/md/philosophy/`, `raw/md/snapshots/`, `raw/md/temporary/`,
`raw/txt/` and `raw/legacy/vscodium_workspace/`.

The existing semantic ingest freeze file identifies `raw/md/archived_unsorted`
as source and records its own model/chunk settings. Those are preserved source
claims; derived output does not replace source.

## Legacy path named canonical

`canonical/` remains at its historical path. Its contents are archived
development artefacts. Original source declarations remain unchanged, but
eArc does not treat this path or its contents as canonical.

## Code example

`src/qh_core.c` is recorded by the operator as an old historical experimental
core in `EARC_OBJECT_RECORD_qh_core.c_1793335241.json`. That is an archive
classification, not a code quality or currentness validation.

## Historical state folders

Ten underscore-prefixed root directories remain in place. Future grouping
under `repository_state/` is only a proposal pending path-reference mapping.

## Rights and model

Unregistered objects default to `RIGHTS_OPEN`. Exact grants are in
`RIGHTS_REGISTER.json`; no directory-wide grants are made. See the model,
ingestion policy, object schema and neutrality transition files.
