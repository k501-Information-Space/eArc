# V3 Alpha Validation Report

**Build/check date:** 2026-10-14 (package-building environment)  
**Version:** `3.0.0-alpha.0`  
**Result:** local package checks PASS; target-host and independent validation remain OPEN

## 1. Build evidence

The sources were compiled with C11, optimization and strict warnings (`-Wall -Wextra -Wpedantic -Wno-misleading-indentation -Werror`). The explicit `-Wno-misleading-indentation` setting is needed because the current source uses compact one-line C statements; it does not disable other warnings. No external crypto library is required.

## 2. End-to-end fixture tests

`make test` completed and reported `K501 V3 TEST SUITE: PASS`. Tests use disposable temporary directories. They cover:

- QH256 v2 cell states, serialization roundtrip across all 128 cells, TRUE/FALSE merge to GUARD, commutativity and idempotence checks;
- store creation and initial frame;
- precommit state validation and Proof Before State result;
- object/record identity reconstruction;
- full frame verification and source comparison;
- text retrieval with returned source identity and readable path;
- `trace`, `history`, `diff` and historical frame validation;
- second-frame update and parent-chain validation;
- refusal of repeated frame ID;
- rejection of altered `INDEX.tsv`;
- detection of source drift;
- refusal to auto-select among multiple branch tips;
- source corpus with a regular file, directory, Unicode path, spaces, JSON, binary bytes and a symlink that is observed rather than followed.

## 3. Sanitizer pass

The full integration tests were rebuilt and run using AddressSanitizer and UndefinedBehaviorSanitizer. The first sanitizer run found an unfreed `TextVec` in successful `scan` cleanup. That allocation path was corrected. The sanitizer test was then rerun and the suite passed without a sanitizer/leak report. The strict `-Werror` build passed after the source correction.

This is evidence from the package-building environment only. It is not a CI result, independent test, target-host run or 50,000-file scale benchmark.

## 4. Reference provenance

`make verify-reference` returned `OK` for the SHA-256 of the included v2.1 Alpha-C ZIP. The imported QH256/sha256 source files compared byte-for-byte with the unpacked archived release during preparation.

## 5. Not tested / OPEN

- User's Debian 13 / HP xw8600 target host and its exact compiler/libc environment.
- Full 500-file corpus or 50,000-file scale/load/resource behaviour.
- Interrupted power-loss testing on physical storage at each write/rename boundary.
- Multi-process/concurrent-writer behaviour; this alpha assumes one writer.
- Independently audited cryptographic correctness or signed/non-repudiable proofs.
- Python/C v2.1 parity, v2.1 binary record compatibility or silent migration from a v2 store.
- Semantic embeddings, vector search, reranking, LLM prompts, llama.cpp or any model-generated claim admission.
- DOCX extraction, OCR, audio/video ingestion and multilingual semantic retrieval.
- License resolution for the upstream code bundle.

## 6. Validation meaning

The tests validate the declared local behaviour of this alpha implementation. The project must not call V3 canonical, production-ready, independently validated, scientifically superior or fully integrated until the owner has reviewed the schemas and license status, run the package on the target host, and accepted explicit release gates for the intended scope.
