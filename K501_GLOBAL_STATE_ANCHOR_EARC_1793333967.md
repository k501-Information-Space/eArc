# K501 Global State Anchor — eArc / main

**Anchor ID:** `K501_GLOBAL_STATE_ANCHOR_EARC_MAIN_1793333967`  
**Schema:** `K501_GLOBAL_STATE_ANCHOR/1.0.0`  
**Status:** `PASS_SCOPED_REPOSITORY_OBSERVATION_AND_DOCUMENTATION_TRANSITION`  
**Authority boundary:** repository-scoped; not a replacement for the K501 global authority hierarchy.

## 1. Operator time anchor

- Unix Epoch: `1793333967`
- UTC: `2026-10-30T04:19:27Z`
- Europe/Berlin: `2026-10-30T05:19:27+01:00`
- Source: operator-supplied time anchor for this authorized transition.

This is the operator's declared anchor for the transition, not a claim that every API read or Git write occurred at that exact second.

## 2. Source state

- Repository: `k501-Information-Space/eArc`
- Branch: `main`
- Parent commit: `d91d11e8a851d54df0624295452d5c06f96134c3`
- Parent tree: `b1656f48ef6adf89847fafe6c8360372a0bd16bb`
- The first-stage harmonization was already merged to main.

## 3. Observed repository structure

At the parent tree:
- 4,505 Git blobs.
- 62 Git trees/directories.
- Recursive tree response not truncated.
- Git blob-size sum: 722,927,327 bytes. This is not the actual full LFS payload size.

The previous stage removed seven zero-byte placeholder-only directories. This transition does not move, rename or delete existing source/archive/code/specification/derived objects.

## 4. Transition recorded

- Separate software and documentation licences are declared with path-scoped grants.
- A license map and third-party rights notice are added.
- Human and machine navigation are updated.
- Human and machine topology indexes are added.
- Paired state anchor, paired validation report, manifest and checksum list are added.
- Existing historical repository-state directories remain at their original paths; consolidation remains PROPOSED_ONLY_NOT_EXECUTED.

## 5. Licensing state

- MIT: K501-authored software only within `LICENSE_MAP.md`.
- CC BY 4.0: K501-authored documentation only within `LICENSE_MAP.md`, where the licensor holds the necessary rights.
- Mixed source collections, imported data, archival binaries, derived chunks/embeddings, test corpus and unresolved objects are excluded from blanket licences.
- Overall rights review: `PARTIALLY_SCOPED`; complete per-file rights clearance remains OPEN.

## 6. Critical implementation observation

The selected parent source blob for `src/qh_core.c` was `5eadf75402eb1605268b93dffe939a55bb015595`. Its `k501_hash_compute` function assigns each output byte using `(i + len) & 0xFF`; the observed function does not read the input payload bytes. This is not SHA-256 and cannot provide content-dependent cryptographic identity or integrity.

No code correction was made in this transition. Any integrity, frame-identity or hash-chain claim depending on this function remains OPEN until a separate implementation correction and test transition.

## 7. Validation boundary

PASS applies only to the structural and documentation checks listed in `VALIDATION_REPORT.md/.json`. It does not mean:
- every file's full contents were reviewed;
- all LFS payloads were downloaded or rehashed;
- every source has known provenance or cleared rights;
- the C program was built or run;
- the hash routine is cryptographically correct;
- older freeze/seal reports represent current global state.

## 8. Preserved unknowns

- Full rights and provenance status of `raw/**`, `archive/**`, `semantic_ingest_v1/**` and `test_ingest_20/**`.
- Third-party contribution status of every code line.
- Actual LFS payload availability/integrity.
- Runtime/build correctness of the current C implementation.
- Cryptographic correctness of `src/qh_core.c:k501_hash_compute`.
- Exact path-reference dependencies before physical consolidation of historical root directories.

Unknown and OPEN states remain explicit.

## 9. Paired artefacts

- `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.md`
- `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.json`
