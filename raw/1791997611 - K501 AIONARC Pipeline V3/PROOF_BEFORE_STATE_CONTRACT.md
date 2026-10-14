# Proof Before State — v3 operational contract

**Contract ID:** `K501-PROOF-BEFORE-STATE-V3A0`  
**Status:** specification implemented as local alpha checks; not independent or cryptographic attestation  
**Normative rule:** candidate state must be fully validated and the proof artifact durably written before the candidate state becomes the frame's `STATE.tsv`.

## 1. Preconditions

1. The store exists and carries the expected v3 store marker.
2. Source and store resolve to disjoint directory trees; neither is inside the other.
3. The root ID and frame ID satisfy the defined ASCII identifier grammar.
4. The chosen frame ID is absent. A previous state is either explicitly absent in an empty store or resolves to one verified parent frame.
5. If a parent exists, its complete frame ancestry validates; its root ID matches; its sequence is exactly one less; its state digest matches the child parent-state field.
6. The scanner performs a full path enumeration with deterministic ordering. File bytes are hashed twice; mode/size/mtime are compared around observation; symlinks are read twice and are never followed.

## 2. Candidate construction

The runtime writes only inside a unique hidden staging directory below the store's `frames/` directory. It serializes `STATE.candidate`, then derives text capture, index, transition, Gateway and the QH256 snapshot from the observed input and candidate.

## 3. Required validation before proof

The implementation must pass all of these gates before committing the candidate state:

- Source/store non-overlap and frame-ID absence.
- Parent-state validation, or explicit initial-frame conditions.
- Deterministic object ordering and unique relative paths.
- Recomputed object IDs and record hashes.
- Candidate state re-read and full-file SHA-256 recheck.
- Candidate parse and object-count agreement.
- Object-by-object equality between observed records and parsed candidate records.
- Text-capture parse roundtrip; text digest recomputation; source object path and content digest binding.
- Index row count, order, fields, text availability/status, path encoding and per-object QH256 recomputation.
- Transition counts and event list reconstructed from predecessor and current object sets.
- Gateway header, artifact references and top-level entries reconstructed from candidate scope.
- QH256 serialization roundtrip using the unchanged QH256 v2 C core.
- State, text, index, transition, Gateway, QH256 and frame digests available and bound into proof metadata.

## 4. Commit order

1. Write `FRAME.tsv` into staging and calculate its digest.
2. Write `PROOF.tsv`, including the contract ID, frame/state/chain IDs, artifact digests, passed check list and non-claim.
3. `PROOF.tsv` is flushed and `fsync`'d before commit.
4. Rename `STATE.candidate` to `STATE.tsv` only after proof write has completed.
5. Write and `fsync` the manifest of the eight frame artifacts.
6. `fsync` the staging directory where supported.
7. Promote the complete staging directory to its final, previously absent frame ID using an atomic directory rename; then `fsync` the frames parent where supported.

## 5. Failure behaviour

A validation failure aborts the run before `STATE.tsv` exists in the final frame path. A crash or failed commit may leave a hidden `.stage-*` directory. The runtime never promotes it automatically and never deletes it automatically. Inspect and preserve that evidence; do not call the frame committed solely because a stage directory exists.

## 6. Meaning of PASS

`PROOF BEFORE STATE: PASS` means this implementation's named local checks passed for the candidate bytes and dependencies at the time of the run. It does **not** prove:

- real-world truth of any source statement;
- that the scanned source was factually correct;
- resistance to a malicious operator able to rewrite and rehash the entire store;
- non-repudiation (there are no digital signatures here);
- correctness of the OS, compiler, storage device or SHA-256 algorithm implementation;
- Python/C v2.1 parity or general production readiness;
- semantic correctness, completeness of extraction or LLM answer truth.

The contract is meant to make claims bounded and testable, not to overstate a local software check as universal proof.

## 7. Required tests

The release test suite must test an initial frame, a subsequent update, parent-chain verification, source equivalence, lexical result traceability, tampered-artifact rejection, repeated-frame refusal, ambiguous-branch refusal and explicit source drift detection. Tests run on synthetic fixtures and must never modify project source documents.
