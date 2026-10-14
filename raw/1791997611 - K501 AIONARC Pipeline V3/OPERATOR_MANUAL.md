# K501 AIONARC Pipeline v3 — Operator Manual

**Version:** `3.0.0-alpha.0`  
**Time anchor:** Unix `1791997611` — 2026-10-14 17:06:51 UTC / 19:06:51 CEST  
**Status:** operational candidate, non-canonical  
**llama.cpp:** not integrated

This manual is written for a human at a Linux terminal. It defines the commands and what they do, not just a conceptual architecture. Begin with a small copied test folder and an empty store. Do not begin on the full disk or on canonical K501 working directories.

## 1. What V3 does today

V3 observes a directory tree without intentionally changing its files, assigns stable per-root/per-path/per-type object identities, computes content and record hashes, preserves states as append-only frames, creates a transition against a verified predecessor, maps structural observations to QH256 v2, records source-bound text for supported formats, and provides deterministic lexical query, trace, history, diff, verify and source-comparison commands.

It does **not** connect to a model. Its query is exact lexical AND matching, not embedding search or semantic reasoning. This is the structural memory component that a future model adapter may call, not a finished LLM cognitive system.

## 2. Prerequisites

Recommended environment: Linux / Debian 13 or compatible POSIX environment; a C11 compiler (`cc` or GCC/Clang); `make`; standard libc/POSIX development headers. PDF text extraction is optional and uses `pdftotext` if installed. No OpenSSL, Python package, SQL database, internet access, CUDA or llama.cpp is required by this program.

On Debian, check tools:

    cc --version
    make --version
    uname -a

Optional PDF extractor:

    command -v pdftotext || echo 'PDF extraction unavailable; PDFs remain structural-only'

Do not install or change drivers/models as part of this package workflow.

## 3. Extract and inspect the package

Extract the archive to a new path outside the K501 canonical repositories. Example:

    mkdir -p "$HOME/K501_V3_REVIEW"
    cd "$HOME/K501_V3_REVIEW"
    unzip /path/to/K501_AIONARC_Pipeline_v3.0.0_AI_Memory_Runtime_C.zip

Use the actual download location and inspect `pwd` and `ls` before continuing. Package folder name:

    K501_AIONARC_Pipeline_v3.0.0_AI_Memory_Runtime_C/

Read `README.md`, `LICENSE_STATUS.md`, `docs/STATUS_REGISTER.md` and this manual before collecting real data. The original v2.1-C archive is under `reference/`; `make verify-reference` checks its archived SHA-256.

## 4. Build from source

From the extracted V3 package directory:

    make clean
    make all
    make qh256-test
    make test

Expected build output: `build/k501-memory`. `make test` creates disposable fixtures in a temporary directory, not in your K501 workspace, and reports `K501 V3 TEST SUITE: PASS` on success.

A prebuilt convenience binary exists at `bin/k501-memory-linux-x86_64`. Prefer a local build when operating on the HP xw8600 / Debian 13 host; the source build uses the host toolchain and avoids assuming ABI compatibility with the build container.

If compilation fails, stop and record the full compiler output, `cc --version`, `uname -a`, and the package SHA-256. Do not work around compiler errors by removing validation or changing the QH core.

## 5. Create an isolated test corpus

Example:

    mkdir -p "$HOME/K501_V3_TEST/source/docs"
    printf 'Proof before state.\n' > "$HOME/K501_V3_TEST/source/README.md"
    printf 'Object identity and history.\n' > "$HOME/K501_V3_TEST/source/docs/notes.txt"

Choose a separate empty store path:

    "$PWD/build/k501-memory" init "$HOME/K501_V3_TEST/store"

`init` refuses an existing path. It creates the store and a `frames/` directory. Initialization may leave a partial empty directory if the operating system fails between filesystem operations; inspect it rather than deleting it automatically. For tests, recreate a new distinct path after review.

## 6. First frame (initial observation)

Run the first scan with a stable root ID, explicit frame ID and explicit no-parent marker:

    "$PWD/build/k501-memory" scan \\
      "$HOME/K501_V3_TEST/source" \\
      "$HOME/K501_V3_TEST/store" \\
      k501-test-root frame-001 none

Read the output. The expected success marker is:

    K501 MEMORY SCAN COMMIT PASS
    proof_before_state=PASS

The object count may exceed the number of regular files because directories and symlinks are also objects. Searchable-document count is separate from object count. `frame-001` now exists under `store/frames/frame-001/`.

The first frame's `TRANSITION.tsv` should classify all current objects as `ADDED`, with no parent. It should not be treated as a model interpretation or statement of truth.

## 7. Verify before retrieval

Always verify a frame before relying on it:

    "$PWD/build/k501-memory" verify "$HOME/K501_V3_TEST/store" frame-001

Expected result:

    VERIFY PASS

Verification reconstructs hashes/identities, index fields including per-object QH256, transition events from the parent and current state, Gateway entries, QH snapshot, proof bindings, manifest and ancestry. This is more informative than checking one SHA-256 value in isolation.

## 8. Observe a second state (append-only transition)

Change the source or add a file:

    printf 'A new note.\n' > "$HOME/K501_V3_TEST/source/docs/new.txt"

Then explicitly name the parent:

    "$PWD/build/k501-memory" scan \\
      "$HOME/K501_V3_TEST/source" \\
      "$HOME/K501_V3_TEST/store" \\
      k501-test-root frame-002 frame-001

Validate both parent and child:

    "$PWD/build/k501-memory" verify "$HOME/K501_V3_TEST/store" frame-001
    "$PWD/build/k501-memory" verify "$HOME/K501_V3_TEST/store" frame-002

No frame is overwritten. Do not reuse `frame-001`. The stable `ROOT_ID` must remain the same for a continuing history. A different source universe or different logical identity should have a separate store/root ID, unless an explicit migration contract is later defined.

For convenience you may pass `latest` as the parent, but only if the store has one unambiguous tip. If multiple branches exist, the runtime refuses to guess. Use an explicit parent frame ID.

## 9. Confirm the current source has not drifted

    "$PWD/build/k501-memory" verify-source \\
      "$HOME/K501_V3_TEST/store" frame-002 \\
      "$HOME/K501_V3_TEST/source"

`VERIFY SOURCE PASS` means the current structural enumeration agrees with the selected stored state for object count, paths, object IDs, record hashes and content hashes. It is not a guarantee against every possible concurrent/adversarial filesystem race and it does not check extracted PDF text against a current extractor version. If it reports `SOURCE DRIFT`, stop treating that frame as a snapshot of the current directory. The historical frame remains a record of what it observed.

## 10. Search the captured text

    "$PWD/K501_V3_REVIEW/K501_AIONARC_Pipeline_v3.0.0_AI_Memory_Runtime_C/build/k501-memory" \\
      query "$HOME/K501_V3_TEST/store" latest "proof before state"

Use the actual package directory if you extracted it elsewhere. Query syntax:

    k501-memory query STORE FRAME_ID|latest "search terms"

Behaviour:

- The specified frame is verified first.
- Query terms are tokenized to ASCII letters/digits, underscore and hyphen; short tokens under two characters are ignored.
- The current algorithm case-folds ASCII and requires every token to appear as a substring in the captured text (AND semantics).
- Results are ranked by total token-substring count; ties are ordered by bytewise path.
- Output includes `OBJECT_ID`, `CONTENT_SHA256`, `TEXT_SHA256`, escaped `PATH`, Base64 path, and a bounded excerpt.

This does not understand paraphrases or synonyms. A query for “previous version” will not reliably match “parent state” unless those literal token strings also occur. No embeddings, vector index or reranking is involved.

## 11. Trace a result to its source object

Copy the `OBJECT_ID` from a query result:

    k501-memory trace STORE latest OBJECT_ID

Trace first verifies the complete selected frame. It returns frame ID/sequence, object ID, record hash, source content hash, object type, relative path, mode, size and times, plus text digest/extractor metadata when captured. This establishes where a result points, not whether source prose is true.

If a path is Base64-encoded, decode it without changing the object identity:

    printf '%s' 'BASE64_VALUE' | base64 -d

Do not rename source files during the pilot. Path is part of `object_id`, so a rename is currently represented by a removed object plus an added object.

## 12. Review changes

    k501-memory diff STORE frame-002

`diff` verifies the complete frame before printing `TRANSITION.tsv`. To review an object's history:

    k501-memory history STORE OBJECT_ID

History verifies every stored frame it enumerates and reports the frames containing that identity. The identity may not continue across renames because path participates in the ID. A missing identity in one frame does not imply the source was deleted at a real-world level; it describes the observed inventory.

## 13. Latest and status

    k501-memory latest STORE
    k501-memory status STORE

`latest` only resolves a unique tip and then verifies it. Multiple tips produce an OPEN/ambiguous result rather than automatically choosing the most recently named directory. `status` is an inventory of frame metadata and possible tips; it does not substitute for `verify`.

## 14. Text formats and limits

The implementation recognizes common plain-text formats: Markdown, TXT, JSON/JSONL, YAML, TOML, INI/CONF/CFG, CSV/TSV, XML/HTML, C/C++ source, Python, Shell, SQL, JavaScript/TypeScript, CSS, SVG, logs, TeX/Bib, diff/patch and selected system configuration suffixes. Exact candidates are listed in `k501_memory.c` (`is_text_candidate`).

Regular file limit for text read: 16 MiB per file. Total captured text limit: 256 MiB per frame. When a limit is exceeded, the original remains a structural object and a status is recorded in the derived index. PDF extraction requires `pdftotext`; it uses an explicit `exec` call, not a shell command. DOCX is inventory-only in V3 alpha. Images, scanned PDFs, audio and video are not interpreted.

A zero-length file can be successfully captured as empty text, but it is marked `STRUCTURAL_ONLY` in the index because it cannot produce a lexical hit.

## 15. Proof and failure handling

Read the full contract in `docs/PROOF_BEFORE_STATE_CONTRACT.md`. A normal completed frame contains:

- `STATE.tsv`
- `FRAME.tsv`
- `PROOF.tsv`
- `QH256.hex`
- `INDEX.tsv`
- `TEXT.tsv`
- `TRANSITION.tsv`
- `GATEWAY.tsv`
- `MANIFEST.sha256`

`PROOF.tsv` is flushed before the state commit. The directory is promoted from a unique hidden staging directory only after the remaining manifest/promotion steps pass. If a run fails, an incomplete `.stage-*` may remain. Never promote it manually based only on its name. Preserve it for inspection.

A repeated frame ID, parent mismatch, ambiguous tip, source/store overlap, failed hash/reparse, transition mismatch, QH mismatch, index mismatch, Gateway mismatch or changed source bytes should cause refusal rather than silent correction. Capture the command and full output if failure occurs.

## 16. Backup and restoration

A backup is a byte copy of the store, not a canonical promotion. Before copying, run `verify` against the tip. Copy to a new destination and verify the copied frame again. Do not sync two writers into the same store; V3 is a single-writer CLI runtime with no locking protocol. Do not restore over an existing store. Create a new destination and compare verification results.

Example (replace paths):

    k501-memory verify /path/to/store latest
    cp -a /path/to/store /path/to/store-backup-20261014
    k501-memory verify /path/to/store-backup-20261014 latest

This assumes the copy preserved bytes and directory structure. A frame chain can have branches; `latest` refuses ambiguous tips.

## 17. Command reference

- `help` — print CLI syntax.
- `qh256-test` — test QH256 v2 cell encoding, serialization, merge of TRUE/FALSE and basic merge properties across cells.
- `init STORE` — create a new store path; refuses existing path.
- `scan SOURCE STORE ROOT_ID [FRAME_ID] [PARENT_ID|none|latest]` — read source and append a proved frame. When omitted, a timestamp-like frame ID and latest parent are used; for reproducible operation use explicit IDs.
- `latest STORE` — verify and print unique tip.
- `status STORE` — list frame metadata/tips, not a substitute for verification.
- `verify STORE FRAME_ID` — full stored-frame and ancestry validation.
- `verify-source STORE FRAME_ID SOURCE` — compare current source structurally to the frame.
- `query STORE FRAME_ID|latest "terms"` — exact lexical AND retrieval from derived text.
- `trace STORE FRAME_ID|latest OBJECT_ID` — verify and show object/source/text identity.
- `history STORE OBJECT_ID` — verified frames containing object identity.
- `diff STORE FRAME_ID` — verify then print transition.

## 18. Exit / result interpretation

Successful output includes an explicit `PASS` string. Nonzero exit should be treated as failure or refusal; do not depend on partial files being valid. Some source-drift paths use exit 3, general operational refusals use exit 2, and test scripts test for nonzero where exact differentiation is not the subject.

## 19. What V3 does not prove

The runtime does not prove that source statements are factual, that every relevant item was semantically understood, that QH256 is superior to all alternatives, that Python and C v2.1 implementations are byte-identical, or that V3 is safe against an adversary who can rewrite all local store data and recompute every hash. It provides repeatable, locally verifiable source identity and transition records under the declared schema.

There is deliberately no llama.cpp integration in this release. A future model adapter must remain a separate derived layer, and its outputs must not mutate stored source or become canonical state automatically.
