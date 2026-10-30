# eArc — K501 Information Space

**eArc:** Append-only deterministic information architecture.  
**Repository:** [k501-Information-Space/eArc](https://github.com/k501-Information-Space/eArc)

## Snapshot and scope

This navigation snapshot was prepared from the GitHub tree rooted at:

- Branch: `main`
- Commit: `f78849f9b792d59cc6e8d81418b71277129fbb33`
- Tree: `94468af772b7cf1c70897cfbf9caf0594ef2f222`
- Observation anchor supplied for this review: Unix `1793333424` — 2026-10-30 04:10:24 UTC

The original root declaration recorded `Status: CANONICAL` and time anchor `1778976550` (2026-05-17). That historical owner-declared status is preserved as history; this navigation snapshot does not independently validate every artifact or change the status of any enclosed object.

This first harmonization pass:
- removes only seven tracked placeholder files that were the sole contents of otherwise empty directories;
- updates the human and machine navigation to match the observed repository tree;
- does not move, rename, deduplicate, reinterpret, or rewrite source, archive, specification, implementation, or derived data.

The branch carrying this pass is separate from `main`.

## Entry order

1. `README.md` — repository overview.
2. `Gateway.md` — human navigation and zone descriptions.
3. `GW__ROOT.json` — machine-readable root navigation.

## Harmonized repository zones

| Zone | Exact path(s) | Observed role |
|---|---|---|
| Canonical reference | `canonical/` | Owner-designated canonical definitions, manifests, and hash-seal records. Individual files retain their own declared status. |
| Formal specifications | `spec/` | Research and system specifications. |
| Source corpus | `raw/` | Retained source collections: DOCX, Markdown, TXT, and a legacy workspace subtree. |
| Historical archive | `archive/` | Epoch binaries, legacy storage objects, runtime topology manifest, and topology snapshots. |
| Implementation | `src/`, `include/`, `Makefile`, `.vscode/` | C sources, C interfaces, build configuration, and editor/debug configuration. |
| Derived ingest | `semantic_ingest_v1/` | Frozen chunk/embedding outputs and ingest reports derived from the declared source path. |
| Test corpus | `test_ingest_20/` | A separate 20-file Markdown ingest/test collection. |
| Repository-state evidence | The existing top-level `_` directories listed below | Historical tree captures, freeze records, merge preparation, namespace analysis, runtime seals, and topology reports. |

### Source corpus: `raw/`

The current populated source branches are:

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

The path `chatGPT_converastions` is preserved exactly as stored; this pass does not normalize names. `raw/md/archived_unsorted/` is populated and is not an empty directory.

### Derived ingest: `semantic_ingest_v1/`

The freeze record at `semantic_ingest_v1/FREEZE_20260517/semantic_ingest_state.txt` declares:

- source: `raw/md/archived_unsorted`
- model: `nomic-embed-text`
- chunk directory: `semantic_ingest_v1/chunks`
- embedding directory: `semantic_ingest_v1/embeddings`
- report directory: `semantic_ingest_v1/reports`
- chunk maximum: 40 lines

The observed tree contains 994 chunk files and 994 embedding files, plus a freeze record, manifests, reports, and a separate `test_run/` subtree. These are derived artifacts, not replacements for their source records. The freeze file's own `CANONICAL_BASELINE` label is retained as a source declaration; the folder's navigation role here is “derived ingest”.

### Implementation

The repository contains six C source files in `src/` and six headers in `include/`. The root `Makefile` builds `k501_core.bin` from `src/*.c`; `.vscode/launch.json` and `.vscode/tasks.json` also refer to that root-level output. Therefore this pass does not move the binary or change build paths without a build-and-test transition.

### Repository-state evidence currently at root

These exact existing paths are grouped together for navigation, but remain physically unchanged in this pass:

- `_ANALYSIS/`
- `_FREEZE_CANONICAL/`
- `_FREEZE_STATE/`
- `_REMOTE_TREE/`
- `_mainline_freeze/`
- `_merge_preparation/`
- `_namespace_normalization/`
- `_remote_audit/`
- `_runtime_seal/`
- `_topology_map/`

Their manifests and reports are historical, source-scoped records. They must not be interpreted as a single current global state merely because they are presented together in navigation.

### Root-level hold items

The following files remain at their original paths until their exact roles and downstream references are registered:

- `k501_core.bin` — referenced build output.
- `output.ndjson` — NDJSON object tracked through Git LFS.
- `run1.ndjson` — retained line-oriented data file.
- `structure.txt` — local workspace topology capture; a same-content copy is also present at `archive/manifests/runtime/structure.txt`. The two paths remain separate objects.

No deduplication or automatic relocation is performed.

## Empty-directory cleanup in this branch

Git does not store empty directories. The following seven paths were represented only by a zero-byte `.keep` file and are removed in this branch:

- `raw/imports/`
- `raw/md/canonical_candidates/`
- `raw/md/duplicate_candidates/`
- `raw/md/gateway_indexed/`
- `raw/md/pending_review/`
- `raw/md/structural_unknown/`
- `raw/md/unstable_fragments/`

The `.keep` file under `raw/md/archived_unsorted/` is retained because that directory also contains 1,014 source files. Other zero-byte files that are not empty-directory markers are retained.

## Second-stage physical consolidation proposal — not executed

The remaining repository-state directories could later be placed beneath one physical root, for example `repository_state/`, with this explicit crosswalk:

| Current path | Proposed path |
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

This is a proposal, not a completed move. Before applying it, create an exact old-path/new-path register, inspect references to old paths, preserve all blob identities and checksums, and validate the resulting tree. The raw corpus, archive, canonical material, specifications, implementation, test corpus, and derived ingest should remain separate zones.

## Continuity rules

- Preserve exact paths and filenames unless an explicit path transition is registered.
- Keep source objects, archive objects, specifications, canonical declarations, and derived ingest outputs distinguishable.
- Do not infer authority from a filename or directory name alone.
- Do not treat hashes as semantic correctness proofs.
- Keep historical snapshots time-scoped.
- Do not merge, overwrite, or deduplicate equal-content objects solely because their bytes match.

K501 :: APPEND_ONLY  
K501 :: PROOF_BEFORE_STATE  
K501 :: RECONSTRUCT_BEFORE_EXTEND  
K501 :: PRESERVE_HISTORY
