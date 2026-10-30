# eArc Main Transition — Validation Report

**Report ID:** `K501_EARC_MAIN_TRANSITION_VALIDATION_1793333967`  
**Scope:** repository navigation, scoped rights documentation, index, state-anchor pair and integrity metadata.  
**Parent:** `d91d11e8a851d54df0624295452d5c06f96134c3` / tree `b1656f48ef6adf89847fafe6c8360372a0bd16bb`.

## PASS — observed and performed checks

1. Connected GitHub permissions reported `admin`, `maintain`, `pull` and `push`.
2. The `main` branch and recursive repository tree were read before transition.
3. The parent recursive tree reported 4,505 Git blobs and 62 Git trees, with `truncated=false`.
4. The seven empty placeholder-only paths removed by the previous merged transition were absent from the parent tree.
5. Primary source/archive/canonical/specification/implementation/derived/test zones were present.
6. Selected README, Gateway, root Gateway JSON, existing licence, C source, headers, canonical, specification, manifest and freeze files were read.
7. The prior MIT text contained redundant historical contact information and did not clearly limit its application to authored software.
8. New MIT and CC BY 4.0 grants are path-scoped; mixed/unverified material is explicitly excluded.
9. New JSON documents were syntax-checked before blob creation.
10. SHA-256 was generated for listed transition files using a local pure-JavaScript implementation; the implementation passed the published `abc` test vector.
11. A resulting Git tree was created and read back before the main ref transition. Key existing data-zone paths were confirmed present.

## OBSERVATION — critical implementation finding

The selected source file `src/qh_core.c` (parent blob `5eadf75402eb1605268b93dffe939a55bb015595`) defines:

`out[i] = (uint8_t)((i + len) & 0xFF);`

inside `k501_hash_compute(const uint8_t *data, size_t len, uint8_t out[32])`.

In the observed function body, output bytes are derived from the loop index and input length; the input payload bytes are not read. This is **not a SHA-256 implementation** and cannot provide content-dependent cryptographic identity or integrity. This observation is a static reading of the selected file, not a complete code audit. The function must not be relied on as a cryptographic hash until replaced under a separate reviewed transition and tested against standard vectors.

## OPEN — not tested or not established

- No C build or runtime test was run.
- No full content scan or rehash of all repository objects was run.
- Git LFS payloads were not downloaded; pointer integrity is not payload integrity.
- No complete file-by-file source, copyright or licence audit was performed.
- No exhaustive third-party code provenance scan was performed.
- No semantic validation of canonical/specification assertions was performed.
- No physical move of the ten historical repository-state directories was made.
- No current validity claim is made for older runtime hashes or freeze-state declarations.
- The `k501_hash_compute` implementation is not SHA-256; integrity functions depending on it remain unverified.

## Result semantics

`PASS` applies only to the explicitly listed structural/documentation checks. Software correctness, hash correctness, complete rights clearance, full repository integrity and physical consolidation remain OPEN.
