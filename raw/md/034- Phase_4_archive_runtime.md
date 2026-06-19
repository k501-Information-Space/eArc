# Phase_4_archive_runtime.md

This phase introduces frozen archives as immutable snapshots of validated transition streams. Archives are not authority; they are sealed replay artifacts [web:181][web:184].

## Target files

- `src/k501/storage/archive_store.py`
- `src/k501/storage/journal.py`
- `tests/unit/test_archive_store.py`
- `tests/integration/test_archive_freeze_replay.py`

## Dataclasses

- `ArchiveHeader`
- `ArchiveEntry`
- `ArchiveManifest`
- `ArchiveHead`

## Functions

- `freeze_archive(...)`
- `load_archive(...)`
- `validate_archive(...)`
- `archive_digest(...)`
- `archive_head(...)`
- `archive_transition_count(...)`

## Public interfaces

- `ArchiveStore`
- `ArchiveValidator`

## pytest tests

- archive freeze creates immutable artifact
- archive digest matches source transitions
- archive head and length are correct
- archive replay reproduces journal-derived digest
- archive validation fails on mutation

## mypy constraints

- archive identity fields typed as immutable values
- archive metadata typed precisely
- no mutable archive payload shared across layers

## ruff constraints

- no in-place mutation of frozen archive records
- no ambiguity between archive and journal APIs

## Migration mapping from existing modules

- `src/k501/storage/archive_store.py` → KEEP and formalize.
- `src/k501/core/archive.py` → PROJECTION or legacy wrapper depending on current usage.

## Estimated git commits

- 1 to 2 commits.

## Expected repository tree after completion

```text
src/k501/storage/
├── __init__.py
├── journal.py
├── segment_store.py
├── archive_store.py
└── index_store.py
tests/unit/
└── test_archive_store.py
tests/integration/
└── test_archive_freeze_replay.py
```