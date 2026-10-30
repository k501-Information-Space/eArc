# Gateway — K501 Information Space / eArc

**Repository:** `k501-Information-Space/eArc`  
**Human entry:** `Gateway.md`  
**Machine entry:** `GW__ROOT.json`  
**Navigation state:** owner-maintained; repository observation is time-scoped.

## Entry sequence

`README.md` → `Gateway.md` → `GW__ROOT.json` → `INDEX.md` / `INDEX.json` → zone content → paired Global State Anchor and validation report.

## Main zones

### Canonical reference and specification
- `canonical/` — owner-designated canonical reference material. A directory name does not automatically confer authority on every file within it.
- `spec/` — research and system specifications.

### Original and historical information
- `raw/` — retained source corpus. Paths and names are preserved exactly.
- `archive/` — historical storage objects, binaries, manifests and topology captures.

### Implementation
- `src/` — C implementation sources.
- `include/` — C interfaces and shared types.
- `Makefile` — build definition; current target is `k501_core.bin` at repository root.
- `.vscode/` — editor/debug configuration.

### Derived and test data
- `semantic_ingest_v1/` — frozen chunks, embeddings and reports. Its freeze record identifies `raw/md/archived_unsorted` as the source.
- `test_ingest_20/` — separate test/ingest corpus.

Derived artifacts do not replace their source objects and do not inherit a blanket licence where source rights are unknown.

## Repository-state records retained at root

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

These remain physically unchanged. Each record must be read with its own time anchor, scope and status. Their coexistence does not make them one current global state.

## Root-level records and controls

- `INDEX.md` / `INDEX.json` — observed topology index.
- `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.md/.json` — matched state-anchor pair.
- `VALIDATION_REPORT.md/.json` — validation scope and limitations.
- `LICENSE`, `LICENSE-CONTENT`, `LICENSE_MAP.md`, `THIRD_PARTY_NOTICES.md` — scoped licensing.
- `MANIFEST.json`, `SHA256SUMS.txt` — integrity metadata for transition artifacts.

## Rights boundaries

MIT applies only to K501-authored software within `LICENSE_MAP.md`. CC BY 4.0 applies only to K501-authored documentation within that map. Mixed raw/archive/derived/test material, third-party material and unresolved sources are excluded unless separately licensed.

## Gateway rules

- Navigation is not validation.
- A path is an identifier, not semantic authority.
- Do not silently move, rename, merge or deduplicate source objects.
- Preserve conflicting and historical state records.
- Report missing evidence as missing.
- Keep generated/derived information distinct from original sources.

K501 :: DETERMINISTIC_ORIENTATION  
K501 :: TRACEABILITY_REQUIRED  
K501 :: PROOF_BEFORE_STATE  
K501 :: PRESERVE_HISTORY
