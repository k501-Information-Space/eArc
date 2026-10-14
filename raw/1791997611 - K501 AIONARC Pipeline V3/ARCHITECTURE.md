# K501 AIONARC Pipeline v3 — architecture

**Status:** SPECIFICATION / candidate implementation correspondence must be verified by tests  
**Version:** `3.0.0-alpha.0`  
**Time anchor:** `1791997611`

## 1. Purpose

V3 is a small local memory substrate. It records structurally observed source objects, preserves append-only snapshots, captures readable source text as a derived layer, derives deterministic navigation records, and offers a read-only query/trace interface. It is intentionally a C CLI application; it is not a multi-process daemon.

The target is a reliable memory foundation that a future local model client can consume. V3 itself is not a language model and does not infer meaning.

## 2. Modules

### QH256 v2 core

The core is the referenced QH256 C implementation. It defines 128 two-bit cells, 256 bits, 32 serialized bytes, cell states `UNKNOWN/FALSE/TRUE/GUARD = 00/01/10/11`, and a plane-wise-OR merge (`MERGE_K`). V3 does not change the QH256 core, operators, or serialization.

### V3 application mapping

The profile `QH256-K501-AIONARC-MEMORY-V3A0` maps observed object properties into cells 0–31, operation/transition checks into 32–47, and whole-inventory observations into 48–63. It intentionally leaves cells 64–127 UNKNOWN. Details and the limits of each mapped statement are in `QH256_MAPPING_PROFILE.md`.

Each object has a QH256 value encoded into the derived `INDEX.tsv`; `QH256.hex` holds the aggregate fold produced with the actual QH256 v2 `qh256_merge()` function. Aggregate folds are lossy: a GUARD in a corpus aggregate may result from TRUE and FALSE observations across different objects. It must not be interpreted automatically as a contradiction about one object or as a real-world truth claim.

### Observation and identity

The scanner resolves the source root, rejects source/store overlap, walks paths in bytewise deterministic order and does not follow symlinks. Files are hashed twice; metadata is checked around the observation. Symlink targets are recorded and hashed without opening target content through the link. A mutation noticed during observation raises `NO_DRIFT FAIL`.

`object_id` is derived from a domain-separated tuple containing profile domain, stable root ID, relative path and object type. `content_sha256` covers regular file bytes, or symlink target bytes for symlink entries. `record_hash` covers the v3 textual record serialization including metadata and content digest. `state_sha256` covers the canonical serialized state file bytes. `chain_sha256` links the prior frame's chain digest to the current state digest in a v3-specific domain. These are separate identity domains.

### State, transition and temporal frames

A frame is a versioned observation result. It binds a stable root ID, sequence number, optional parent frame ID, parent state digest, object count, transition counters, state digest, chain digest and artifact references. A state stores the sorted object set and structural metadata. Transition records classify additions, removals, content changes, metadata changes and unchanged objects. Because the current `object_id` includes the relative path, a rename appears as a removal plus an addition; continuity is not inferred.

### Text capture and index

Readable UTF-8 text is retained in `TEXT.tsv` as a derived snapshot, bound to the source object's content digest and to a text digest. The index is deterministically derived from the observed state and text capture. Every index row contains object identity, record digest, content digest, object type, text reference/status, Base64 path and per-object QH256 digest. The index is not canonical data and cannot redefine object identity.

Plain text candidates are read as UTF-8 bytes. PDFs use `pdftotext` when available. Other formats remain structurally observed but do not become searchable text unless a versioned extractor is added. DOCX is not extracted by alpha. There is no OCR.

### Gateway

`GATEWAY.tsv` is orientation metadata. It references the files in a frame and emits top-level entries. It does not assert semantic authority. V3 validates the full Gateway serialization against the candidate frame before committing state.

### CLI

The CLI is the operator interface. All state inspection commands verify the frame before using evidence where implemented (`verify`, `query`, `trace`, `diff`, and `history`). `status` is an inventory view; run `verify` for integrity assurance.

## 3. Dataflow

`source root → read-only observation → deterministic sort → object IDs + record hashes → candidate STATE.tsv → derived TEXT.tsv / INDEX.tsv / TRANSITION.tsv / GATEWAY.tsv / QH256.hex → proof contract checks → durable PROOF.tsv → STATE.candidate renamed to STATE.tsv → manifest → atomic frame-directory promotion`.

No source file is moved, renamed, deleted or rewritten. The only write target is the runtime store. A failed/interrupted staging directory is retained and never automatically promoted. The operator must inspect it before any deliberate cleanup.

## 4. Canonical/derived boundary

- Source files: supplied input; never mutated by V3.
- `STATE.tsv` and frame records: source-observation state for this runtime profile.
- `PROOF.tsv`: evidence that the named local acceptance checks passed before commit.
- `QH256.hex`: deterministic aggregate state representation; not complete history.
- `TEXT.tsv`: derived extracted text.
- `INDEX.tsv`: derived navigation/search projection.
- `GATEWAY.tsv`: derived machine/human orientation.
- Query result: derived retrieval output; no truth claim.
- Any future LLM answer: not included here; would remain DERIVED until a separate, explicit admission process is specified and implemented.

## 5. Non-goals

V3 does not presently implement semantic embeddings, vector similarity, reranking, model prompts, llama.cpp connectivity, speech I/O, multi-agent coordination, content classification, entity resolution, auto-summarization, automated publication, distributed consensus, digital signatures or remote replication.
