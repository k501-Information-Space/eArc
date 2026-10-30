# eArc — License Map

**Policy version:** 1.0  
**Scope anchor:** main transition based on parent commit `d91d11e8a851d54df0624295452d5c06f96134c3`.  
**Rights state:** PARTIALLY_SCOPED; no full per-object provenance audit is claimed.

## 1. K501-authored software — MIT

The MIT licence in `LICENSE` applies to K501-authored software in these paths, only to the extent Patrick R. Miller holds the relevant rights:

| Path | Scope |
|---|---|
| `src/**` | C implementation source |
| `include/**` | C headers and interfaces |
| `Makefile` | Root build definition |

Any file carrying its own copyright/licence notice or identified third-party provenance is governed by that file's notice instead. No third-party code is relicensed by this map.

## 2. K501-authored documentation — CC BY 4.0

The CC BY 4.0 notice in `LICENSE-CONTENT` applies to K501-authored documentation, only where the licensor holds the necessary rights:

- Root documentation: `README.md`, `Gateway.md`, `INDEX.md`, `LICENSE_MAP.md`, `THIRD_PARTY_NOTICES.md`, `VALIDATION_REPORT.md`.
- Machine-readable K501 navigation and project-state documentation: `GW__ROOT.json`, `INDEX.json`, `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.md`, `K501_GLOBAL_STATE_ANCHOR_EARC_1793333967.json`, `VALIDATION_REPORT.json`, `MANIFEST.json`.
- K501-authored specification documents under `spec/**`.
- K501-authored canonical documentation under `canonical/**`.

Where a file contains third-party or imported material, the applicable third-party terms and file-specific notices take precedence. The presence of a path in this list is not a statement that every embedded source or quotation has been cleared.

## 3. Explicitly excluded from blanket repository licensing

No blanket MIT or CC BY 4.0 grant is made by this repository policy for:

- `raw/**` — imported source corpus, conversations, DOCX, Markdown and text collections;
- `archive/**` — historical binary/storage objects, legacy objects and topology captures;
- `semantic_ingest_v1/**` — chunks, embeddings, derived outputs and reports sourced from other files;
- `test_ingest_20/**` — retained test/ingest corpus;
- root data and generated artifacts: `k501_core.bin`, `output.ndjson`, `run1.ndjson`, `structure.txt`;
- any object with unresolved or third-party authorship, provenance or licence.

These materials remain RIGHTS_OPEN or subject to their own source-specific licence. Public availability in GitHub is not a licence grant.

## 4. Third-party and individual notices

A third-party licence, copyright header, attribution condition, database right or other source-specific notice remains controlling for the relevant object. See `THIRD_PARTY_NOTICES.md`. If a file's provenance or licence is unknown, treat it as not cleared for redistribution beyond access already provided by its source.

## 5. Interpretation

This map is a scoped permission statement, not a legal opinion and not a declaration that every repository object has been reviewed. No rights are granted beyond those the licensor is legally entitled to grant.
