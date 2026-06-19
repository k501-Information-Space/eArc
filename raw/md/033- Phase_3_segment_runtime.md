# Phase_3_segment_runtime.md

This phase adds optional segment handling without changing the journal’s authority. Segments are runtime accelerators and recovery units only [web:162][web:184].

## Target files

- `src/k501/storage/segment_store.py`
- `src/k501/storage/journal.py`
- `tests/unit/test_segment_store.py`
- `tests/integration/test_segment_rebuild.py`

## Dataclasses

- `SegmentHeader`
- `SegmentRecord`
- `SegmentTrailer`
- `SegmentManifest` if needed for segment bookkeeping

## Functions

- `write_segment(...)`
- `read_segment(...)`
- `seal_segment(...)`
- `validate_segment(...)`
- `rebuild_from_segments(...)`
- `truncate_incomplete_tail(...)`

## Public interfaces

- `SegmentStore`
- `SegmentValidator` only if kept in storage runtime layer

## pytest tests

- segment write/read round-trip
- sealed segment validates
- incomplete tail is truncated
- segment rebuild reproduces journal order
- segment digest matches contents

## mypy constraints

- framed record types typed explicitly
- segment offsets and lengths typed as `int`
- no mixed binary/text ambiguity

## ruff constraints

- no duplicate framing logic
- no hidden side effects in reader functions
- no mutation of validated records after parse

## Migration mapping from existing modules

- no existing segment module in current tree.
- move any future segment-like logic out of journal code and into `segment_store.py`.

## Estimated git commits

- 2 commits.

## Expected repository tree after completion

```text
src/k501/storage/
├── __init__.py
├── journal.py
├── index_store.py
├── evidence_store.py
└── segment_store.py
tests/unit/
└── test_segment_store.py
tests/integration/
└── test_segment_rebuild.py
```