# Phase_5_replay_validator.md

This phase implements replay validation as a first-class deterministic check. It compares ordered transition IDs, derived projections, replay digest, and graph topology exactly as specified [web:183][web:178].

## Target files

- `src/k501/core/replay.py`
- `src/k501/core/validator.py`
- `src/k501/storage/journal.py`
- `tests/unit/test_replay_validator.py`
- `tests/integration/test_replay_validation.py`

## Dataclasses

- `ReplayValidationResult`
- `ReplayDiff`
- `ReplayDigest`
- `ReplayHead`

## Functions

- `compute_replay_digest(ordered_transition_ids) -> str`
- `validate_replay(...) -> ReplayValidationResult`
- `compare_ordered_ids(...)`
- `compare_projections(...)`
- `compare_topology(...)`

## Public interfaces

- `ReplayValidator`
- `ReplayValidationResult`

## pytest tests

- same ordered IDs produce same digest
- reordered IDs fail validation
- inserted IDs fail validation
- deleted IDs fail validation
- mutated IDs fail validation
- derived projections must match
- graph topology must match

## mypy constraints

- replay comparison outputs typed dataclasses
- no dynamic validation dictionaries in public API
- digest input must be an ordered sequence type

## ruff constraints

- no accidental set-based comparison where order matters
- no hidden normalization that weakens digest semantics

## Migration mapping from existing modules

- `src/k501/core/replay.py` → KEEP and formalize.
- any current replay logic in `storage` or `graph` → move to validator boundary.

## Estimated git commits

- 1 commit.

## Expected repository tree after completion

```text
src/k501/core/
├── __init__.py
├── canonical.py
├── transition.py
├── projection.py
├── replay.py
└── validator.py
tests/unit/
└── test_replay_validator.py
tests/integration/
└── test_replay_validation.py
```