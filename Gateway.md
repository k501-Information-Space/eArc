# Gateway — K501 Information Space / eArc

**Status:** CANONICAL (owner-declared; original anchor retained in `GW__ROOT.json`)  
**Mode:** STRICT  
**System:** K501 Information Space  
**Repository:** `k501-Information-Space/eArc`

This file is the root human-navigation layer for this repository. Its path is `Gateway.md` at the repository root.

## Navigation order

`README.md` → `Gateway.md` → `GW__ROOT.json` → zone-specific content.

The previous references to `/workspace/Gateway.md` described a local workspace path, not the current GitHub repository path. Use the root-relative path `Gateway.md`.

## Primary zones

### Canonical reference and specifications

- `canonical/` — owner-designated canonical definitions, manifests, and hash-seal records. The declared status of each object remains source-specific.
- `spec/` — research and system specifications.

### Source and historical archive

- `raw/` — source corpus, retained in its existing subpaths.
- `archive/` — historical binaries, storage objects, runtime structure manifest, and topology snapshots.

### Implementation

- `src/` — C implementation source.
- `include/` — C interfaces.
- `Makefile` — current build contract; target `k501_core.bin` is emitted at repository root.
- `.vscode/` — editor, launch, and build-task configuration.

### Derived and test data

- `semantic_ingest_v1/` — derived chunk and embedding outputs. Its freeze record identifies `raw/md/archived_unsorted` as the source.
- `test_ingest_20/` — separate test/ingest corpus.

Derived output must not be mistaken for canonical source material. A freeze marker inside a derived zone remains that file's own declaration and does not change the origin of its inputs.

## Raw Markdown substructure

The populated current subdirectories are:

- `raw/md/AIONARC_KANON/`
- `raw/md/archived_unsorted/`
- `raw/md/bootframes/`
- `raw/md/chatGPT_converastions/`
- `raw/md/kernel/`
- `raw/md/philosophy/`
- `raw/md/snapshots/`
- `raw/md/temporary/`

Paths are identifiers and are preserved exactly. No semantic path normalization is implied.

## Repository-state and audit records

The following directories currently remain at repository root and are navigated as one logical group:

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

They contain time-scoped reports, manifests, tree captures, merge/namespace preparation, and runtime/topology seal evidence. They are not automatically the current global state. Read each record with its own timestamp, scope, and status.

A future grouping beneath `repository_state/` is proposed in `README.md`; it has not been executed in this branch.

## Root-level artifacts retained

- `GW__ROOT.json` — machine-readable root navigation.
- `k501_core.bin` — current root-level Makefile target.
- `output.ndjson`, `run1.ndjson`, `structure.txt` — retained root-level data/topology objects, pending explicit path registration before relocation.

## Empty placeholder paths removed in this branch

The seven paths documented in `README.md` were represented solely by `.keep` files and were empty. They are removed here. Populated source directories and all other zero-byte files are retained.

## Gateway principles

- Orient; do not reinterpret source objects.
- Navigate; do not claim that navigation proves validity.
- Preserve exact path identity until a registered transition exists.
- Separate source, archive, canonical declaration, specification, implementation, derived data, test data, and historical evidence.
- Preserve conflicting and time-scoped records rather than flattening them.
- Reconstruction depends on retained objects and explicit procedures; missing evidence remains missing.

K501 :: DETERMINISTIC_ORIENTATION  
K501 :: TRACEABILITY_REQUIRED  
K501 :: NO_PHANTOM  
K501 :: UNKNOWN_BY_DEFAULT  
K501 :: PROOF_BEFORE_STATE
