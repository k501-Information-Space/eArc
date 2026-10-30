# eArc — K501 Information Space

**Repository:** https://github.com/k501-Information-Space/eArc  
**Model:** append-only, reference-oriented archival and information structure.

## Repository state

This main-branch update is based on the verified parent:

- Parent commit: `d91d11e8a851d54df0624295452d5c06f96134c3`
- Parent tree: `b1656f48ef6adf89847fafe6c8360372a0bd16bb`
- Operator time anchor: Unix `1793333967` — 2026-10-30 04:19:27 UTC / 05:19:27 Europe/Berlin.

The previous first-stage harmonization is already on `main`. This transition adds a rights boundary, a human/machine index, a paired Global State Anchor, a validation report, and updated navigation. It does not physically move the ten historical repository-state directories. Their proposed consolidation remains separate and requires an exact path-reference register.

## Navigation order

1. `README.md` — repository purpose, boundaries and entry points.
2. `Gateway.md` — human navigation.
3. `GW__ROOT.json` — machine-readable root navigation.
4. `INDEX.md` and `INDEX.json` — observed repository inventory.
5. `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.md/.json` — paired, time-scoped state record.
6. `VALIDATION_REPORT.md/.json` — scope and results of this transition.

## Main zones

| Zone | Paths | Role |
|---|---|---|
| Canonical reference | `canonical/` | Owner-designated canonical declarations and manifests; file-level status remains authoritative for each object. |
| Specifications | `spec/` | Research and system specifications. |
| Source corpus | `raw/` | Retained DOCX, Markdown, TXT and legacy source material. |
| Historical archive | `archive/` | Historical binaries, storage objects, manifests and topology snapshots. |
| Implementation | `src/`, `include/`, `Makefile` | C source, interfaces and build definition. |
| Derived ingest | `semantic_ingest_v1/` | Chunk, embedding and report artifacts derived from an identified source path. |
| Test corpus | `test_ingest_20/` | Separate 20-file ingest/test collection. |
| Repository-state evidence | Ten existing top-level `_` directories | Historical freeze, tree, audit, merge, namespace, runtime and topology records. |

The root-level historical repository-state directories remain at their existing paths. A proposed `repository_state/` crosswalk is documented in `INDEX.md`, but no physical consolidation is claimed in this transition.

## Licensing

The repository uses two separate licensing tracks:

- `LICENSE` — MIT for K501-authored software, within the exact scope in `LICENSE_MAP.md`.
- `LICENSE-CONTENT` — CC BY 4.0 for K501-authored documentation, within the exact scope in `LICENSE_MAP.md`.

`THIRD_PARTY_NOTICES.md` records the rights boundary and review limitations. The licences do **not** automatically cover the mixed source corpus, imported conversations, legacy material, archival binaries, LFS payloads, derived embeddings, test data, or files whose authorship/rights have not been established. Those objects remain source-specific / rights-open unless a file-level notice says otherwise.

## Continuity and evidence

- Preserve source objects and historical path identity.
- Keep source, canonical declarations, specifications, implementation and derived output distinct.
- Treat timestamps and status claims as time- and scope-bound.
- Do not infer rights, authority, correctness or semantic equivalence from a filename, path or matching hash.
- A Git tree inventory is not a complete payload download, content review, build, runtime test or legal provenance audit.
- The state anchor is a scoped repository observation, not a replacement for the K501 global authority hierarchy.

K501 :: PROOF_BEFORE_STATE  
K501 :: RECONSTRUCT_BEFORE_EXTEND  
K501 :: APPEND_ONLY  
K501 :: NO_PHANTOM  
K501 :: UNKNOWN_BY_DEFAULT
