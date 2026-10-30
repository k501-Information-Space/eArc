# Third-Party Notices and Rights Boundaries

**Review scope:** repository tree and selected top-level, code, specification, manifest and licence files read during the 2026-10-30 eArc harmonization.  
**Review state:** INITIAL_NOTICE_REGISTER; NOT_A_COMPLETE_PROVENANCE_AUDIT.

## 1. Third-party components

The reviewed C source and header files do not expose an explicit third-party copyright header in the portions inspected. This observation does not prove that all code is original or that no third-party contribution exists. No comprehensive line-by-line code provenance scan, dependency lockfile audit, or software composition analysis was performed in this transition.

No external source is intentionally relicensed by `LICENSE`. Any later-discovered third-party code must retain its own licence and notices and be registered here before a new redistribution claim is made.

## 2. Source corpus and archive

The following zones are mixed, historical, imported, generated or not sufficiently rights-reviewed for a blanket grant:

- `raw/**`
- `archive/**`
- `semantic_ingest_v1/**`
- `test_ingest_20/**`
- root-level data and binary artifacts named in `LICENSE_MAP.md`.

They may include operator-authored material, conversation exports, imported files, legacy code, third-party works or derived representations. Their presence in this public repository is not evidence that all rights have been cleared.

## 3. Derived data

Chunks, embeddings and reports in `semantic_ingest_v1/` are derived from source collections. Their distribution status depends on source rights, database rights and applicable conditions. No separate blanket CC BY licence is asserted for them.

## 4. Required future actions

When an individual source's provenance or licence is established:

1. record its exact repository path and object identity;
2. record the source and rights evidence;
3. preserve its existing notice or add a specific attribution/notice;
4. update this register and `LICENSE_MAP.md` in an append-only, reviewable transition;
5. do not apply a broad licence to unrelated files.

## 5. No blanket warranty

This register is an initial, bounded rights notice. It is not legal advice, not a guarantee that all source rights have been cleared, and not an assertion of ownership over third-party or imported material.
