# K501 AIONARC Pipeline v3.0.0 — AI Memory Runtime (C)

**Time anchor:** Unix `1791997611` — 2026-10-14 17:06:51 UTC / 19:06:51 Europe/Berlin  
**Package status:** `ALPHA.0 / OPERATIONAL CANDIDATE / NON-CANONICAL`  
**Runtime integration:** `NOT PASS`  
**llama.cpp integration:** intentionally absent

## Purpose

Pipeline v3 is a compact terminal-first structural-memory runtime built in C11. It combines a read-only filesystem observer, versioned append-only frames, QH256 v2 serialization and merge, a declared v3 mapping profile, a derived per-object index, a Gateway, transitions, source-bound text capture, lexical retrieval and a proof-before-state commit gate.

The operational result is not just a list of hashes: an operator can inspect current and historical source states, compare frames, locate exact terms in captured text, trace a hit to its source object, verify that the source still matches an earlier frame, and reject incomplete or altered frames. The retrieval query is exact lexical AND matching; it is not semantic search or a language model.

## Components

- `k501_memory.c` — v3 runtime and command-line interface.
- `include/qh256.h`, `src/qh256.c` — QH256 v2 core retained without changing its algebra or wire format.
- `src/sha256.c`, `src/sha256.h` — SHA-256 implementation retained from the referenced v2.1-C package.
- `docs/OPERATOR_MANUAL.md` — step-by-step operator guide.
- `docs/PROOF_BEFORE_STATE_CONTRACT.md` — normative v3 candidate contract.
- `docs/QH256_MAPPING_PROFILE.md` — complete v3 mapping for cells 0–63.
- `tests/test.sh` — end-to-end test suite using temporary fixtures only.
- `reference/` — original v2.1 Alpha-C release archive and the recorded SHA-256.

## Build and test

On Linux with a C11 compiler and standard POSIX development headers:

    make all
    make test

The built program is `build/k501-memory`. A convenience x86-64 binary is also included in `bin/`; compiling locally is the recommended path for the target Debian 13 workstation.

## First run

    build/k501-memory help
    build/k501-memory qh256-test
    build/k501-memory init /path/to/ai-memory-store
    build/k501-memory scan /path/to/read-only-source /path/to/ai-memory-store k501-root frame-001 none
    build/k501-memory verify /path/to/ai-memory-store frame-001
    build/k501-memory query /path/to/ai-memory-store latest "proof before state"

Read `docs/OPERATOR_MANUAL.md` before using real data. Use a new empty store and a bounded, non-sensitive test directory first.

## Architectural boundaries

- QH256 v2 core remains the same 128-cell / 256-bit / 32-byte algebra and serialization implementation. The v3 mapping profile uses 64 cells; cells 64–127 remain UNKNOWN/reserved in the current profile.
- `object_id`, `record_hash`, `content_sha256`, `state_sha256`, `chain_sha256`, text hashes, QH256 and artifact file hashes are distinct values with distinct meanings.
- `STATE.tsv` captures structural object state. `TEXT.tsv` and `INDEX.tsv` are derived. A model-generated interpretation is outside this package and must never be silently promoted to source or canonical state.
- A source-path change produces an object removal/addition because relative path is part of object identity. Automatic rename inference is not implemented.
- Frames are append-only. Existing frame IDs are refused; branch tips are never silently selected.
- Proof PASS means only that the declared local checks passed. It does not prove external truth, absence of malicious replacement, production readiness, or scientific superiority.

## Current limits

No llama.cpp client, embeddings, vector database, reranker, agent, socket service or automatic semantic fact writer is included. Supported text is extracted from UTF-8 text-like formats; PDF extraction uses `pdftotext` if installed. DOCX is inventoried but not extracted in this version. Querying uses exact lexical AND matching. Runtime integration with the operator's local HP xw8600 / Debian 13 host has not been tested from this package-building environment.

## Reference implementation and license status

The original v2.1 Alpha-C archive is included verbatim under `reference/` with its recorded checksum. No new license is declared for this package because the referenced release itself states that its licensing status is unresolved. See `LICENSE_STATUS.md`.
