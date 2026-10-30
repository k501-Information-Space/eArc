# eArc — Repository Index

**Index type:** observed topology index  
**Source branch:** `main`  
**Source commit before this transition:** `d91d11e8a851d54df0624295452d5c06f96134c3`  
**Source tree before this transition:** `b1656f48ef6adf89847fafe6c8360372a0bd16bb`  
**Operator time anchor:** `1793333967` — 2026-10-30 04:19:27 UTC / 05:19:27 Europe/Berlin.

This index describes the observed Git tree. It is navigation metadata, not a semantic classification, rights clearance, complete content audit or build validation.

## 1. Observed inventory before this transition

- Files: 4,505 Git blobs.
- Directories: 62 Git trees.
- Recursive tree response: not truncated.
- Git blob-size sum: 722,927,327 bytes. This is Git object metadata, not a verified total payload size; Git LFS objects are represented by pointer blobs in the Git tree.

### Top-level zones

| Path | Files | Role observed |
|---|---:|---|
| `.vscode/` | 3 | Editor/debug/build-task configuration |
| `_ANALYSIS/` | 1 | Historical runtime-state note |
| `_FREEZE_CANONICAL/` | 4 | Historical canonical freeze records |
| `_FREEZE_STATE/` | 2 | Historical freeze-state records |
| `_REMOTE_TREE/` | 4 | Historical remote tree captures |
| `_mainline_freeze/` | 7 | Mainline freeze manifests and reports |
| `_merge_preparation/` | 7 | Merge preparation manifests and reports |
| `_namespace_normalization/` | 5 | Namespace normalization manifests/reports |
| `_remote_audit/` | 10 | Remote audit records |
| `_runtime_seal/` | 4 | Runtime seal manifest/reports |
| `_topology_map/` | 6 | Topology map manifests/reports |
| `archive/` | 12 | Historical storage, binaries, manifests and topology snapshots |
| `canonical/` | 14 | Canonical declarations and hash-seal records |
| `include/` | 6 | C interfaces |
| `raw/` | 2,367 | Source corpus; seven empty placeholders removed in prior transition |
| `semantic_ingest_v1/` | 2,009 | Derived chunks, embeddings, freeze and reports |
| `spec/` | 7 | Research/system specifications |
| `src/` | 6 | C implementation sources |
| `test_ingest_20/` | 20 | Separate test/ingest documents |

There are also 11 root-level blobs in the source tree: `.gitattributes`, `.gitignore`, `GW__ROOT.json`, `Gateway.md`, `LICENSE`, `Makefile`, `README.md`, `k501_core.bin`, `output.ndjson`, `run1.ndjson` and `structure.txt`.

## 2. Raw source subzones

Observed populated paths:

- `raw/docx/`
- `raw/md/AIONARC_KANON/`
- `raw/md/archived_unsorted/`
- `raw/md/bootframes/`
- `raw/md/chatGPT_converastions/`
- `raw/md/kernel/`
- `raw/md/philosophy/`
- `raw/md/snapshots/`
- `raw/md/temporary/`
- `raw/txt/`
- `raw/legacy/vscodium_workspace/`

The path `chatGPT_converastions` is recorded exactly as present. It is not normalized here.

## 3. Derived ingest

`semantic_ingest_v1/FREEZE_20260517/semantic_ingest_state.txt` declares:

- source: `raw/md/archived_unsorted`
- embedding model: `nomic-embed-text`
- chunk limit: 40 lines
- output roots: `chunks/`, `embeddings/`, `reports/`.

The tree contains 994 chunk objects and 994 embedding objects. Derived outputs remain distinct from their original source collection and inherit no blanket licence from this index.

## 4. Implementation

- `src/`: six C files.
- `include/`: six C headers.
- `Makefile`: compiles `src/*.c` into root-level `k501_core.bin`.
- `.vscode/`: three config files referring to the root build output.

The build was not run during this index transition.

## 5. Root-level items retained

- `k501_core.bin`
- `output.ndjson`
- `run1.ndjson`
- `structure.txt`

`output.ndjson` is configured for Git LFS by `.gitattributes`. LFS payloads were not downloaded as part of this tree inventory.

## 6. Historical repository-state directories

The ten underscore-prefixed root directories remain physically unchanged. The proposed target root `repository_state/` is not present and no path relocation is asserted.

| Existing path | Proposed future path |
|---|---|
| `_ANALYSIS/` | `repository_state/analysis/` |
| `_FREEZE_CANONICAL/` | `repository_state/freeze/canonical/` |
| `_FREEZE_STATE/` | `repository_state/freeze/state/` |
| `_mainline_freeze/` | `repository_state/freeze/mainline/` |
| `_REMOTE_TREE/` | `repository_state/tree_captures/` |
| `_merge_preparation/` | `repository_state/merge_preparation/` |
| `_namespace_normalization/` | `repository_state/namespace_normalization/` |
| `_remote_audit/` | `repository_state/remote_audit/` |
| `_runtime_seal/` | `repository_state/runtime_seal/` |
| `_topology_map/` | `repository_state/topology_map/` |

No move should be executed until exact old-path/new-path registration and reference validation are complete.

## 7. Navigation

- `README.md`
- `Gateway.md`
- `GW__ROOT.json`
- `INDEX.md`
- `INDEX.json`
- `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.md/.json`
- `VALIDATION_REPORT.md/.json`
- `LICENSE`
- `LICENSE-CONTENT`
- `LICENSE_MAP.md`
- `THIRD_PARTY_NOTICES.md`
- `MANIFEST.json`
- `SHA256SUMS.txt`
