# Phase_1_transition_kernel.md

This phase formalizes the transition kernel only. It introduces canonical serialization, transition identity, transition schema, and identity validation without touching storage runtime behavior [web:128][web:183].

## Target files

- `src/k501/core/canonical.py`
- `src/k501/core/transition.py`
- `src/k501/core/projection.py`
- `src/k501/core/validator.py`
- `src/k501/core/replay.py`
- `tests/unit/test_transition.py`
- `tests/unit/test_canonical.py`
- `tests/unit/test_identity_validator.py`

## Dataclasses

- `Transition`
- `StateObject`
- `IdentityValidationResult` if needed for validator return typing

## Functions

- `canonical_bytes(obj) -> bytes`
- `canonical_string(obj) -> str`
- `canonical_hash(obj) -> str`
- `transition_identity_payload(transition) -> dict`
- `compute_transition_id(...) -> str`
- `project_state(transitions) -> StateObject`
- `IdentityValidator.validate(transition)`

## Public interfaces

- `Transition.create(...)`
- `Transition.to_record()`
- `StateObject.from_transition(...)` or equivalent projection constructor
- `IdentityValidator`

## pytest tests

- canonical bytes are stable for the same object
- canonical hash is stable for the same object
- transition ID excludes `timestamp_ns`
- transition ID excludes `metadata`
- provenance transition IDs affect identity
- projection reconstructs StateObject from transitions

## mypy constraints

- `timestamp_ns` must be typed as `int`
- content and metadata must be typed dictionaries
- no implicit optional timestamp generation
- no untyped validator return values

## ruff constraints

- no duplicate helper names
- no unnecessary encode/decode round-trips
- no mutable default arguments
- no import cycles between `canonical`, `transition`, and `validator`

## Migration mapping from existing modules

- `src/k501/core/axiom.py` → PROJECTION / replace with explicit kernel functions.
- `src/k501/core/state_object.py` → PROJECTION into `projection.py`.
- `src/k501/core/frame.py` → PROJECTION if still needed internally.
- `src/k501/core/kernel.py` → LEGACY, split into kernel primitives.
- `src/k501/core/snapshot.py` → PROJECTION.

## Estimated git commits

- 1 to 2 commits.

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
├── test_canonical.py
├── test_transition.py
└── test_identity_validator.py
```