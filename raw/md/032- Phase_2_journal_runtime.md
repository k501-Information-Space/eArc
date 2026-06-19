# Phase_2_journal_runtime.md

This phase implements the authoritative append-only journal runtime. It must treat the journal as truth and make append failures explicit, with recoverability for tail corruption [web:184][web:181][web:162].

## Target files

- `src/k501/storage/journal.py`
- `src/k501/storage/index_store.py`
- `src/k501/storage/evidence_store.py`
- `tests/unit/test_journal_runtime.py`
- `tests/unit/test_index_store.py`
- `tests/integration/test_journal_append_recover.py`

## Dataclasses

- `JournalRecord`
- `JournalHead`
- `IndexEntry`

## Functions

- `append_transition(record) -> str`
- `read_transitions() -> iterator`
- `rebuild_index() -> None`
- `detect_tail_corruption() -> bool`
- `recover_tail() -> None`
- `load_head() -> JournalHead`
- `persist_head() -> None`

## Public interfaces

- `JournalStore`
- `IndexStore`
- `EvidenceStore` only if it remains transition-backed and journal-based

## pytest tests

- append writes one canonical record
- duplicate transition ID raises explicit error
- journal can be scanned back into records
- tail corruption is detected
- index rebuild matches journal contents
- append is durable after fsync boundary

## mypy constraints

- file paths typed as `Path`
- index structures typed precisely
- explicit exceptions for duplicates and append-only violations
- no silent `False` return for write failure

## ruff constraints

- no broad exception swallowing
- no print-based diagnostics in runtime code
- no unused recovery helpers
- no unsafe file writes without explicit helper

## Migration mapping from existing modules

- `src/k501/storage/evidence_store.py` → STORAGE, journal-backed only.
- `src/k501/storage/index_store.py` → KEEP, but refit as rebuildable accelerator.
- `src/k501/evidence/*` → remove runtime authority from these paths.
- any SQLite-backed persistence → migrate out of authority path.

## Estimated git commits

- 2 commits.

## Expected repository tree after completion

```text
src/k501/storage/
├── __init__.py
├── journal.py
├── index_store.py
└── evidence_store.py
tests/unit/
├── test_journal_runtime.py
└── test_index_store.py
tests/integration/
└── test_journal_append_recover.py
```