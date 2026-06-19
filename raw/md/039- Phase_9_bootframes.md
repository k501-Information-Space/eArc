# Phase_9_bootframes.md

This phase formalizes bootframes, startup state handling, and crash recovery sequencing. It does not alter the kernel; it makes runtime entry deterministic [web:184][web:181].

## Target files

- `src/k501/core/lifecycle.py`
- `src/k501/core/kernel.py`
- `src/k501/cli/main.py`
- `src/k501/storage/journal.py`
- `tests/unit/test_bootframes.py`
- `tests/integration/test_boot_and_recover.py`

## Dataclasses

- `BootFrame`
- `RuntimeState`
- `BootResult`
- `RecoveryPlan`

## Functions

- `bootframe_0()`
- `bootframe_1()`
- `bootframe_2()`
- `bootframe_3()`
- `enter_active_state()`
- `enter_frozen_state()`
- `enter_archived_state()`
- `recover_runtime()`

## Public interfaces

- boot sequence entrypoint
- runtime state inspection
- recovery entrypoint

## pytest tests

- bootframes execute in order
- empty store enters active state
- frozen archive reopens deterministically
- recovery after partial tail is successful
- runtime state transitions are valid

## mypy constraints

- state enum typed explicitly
- boot result dataclasses typed explicitly
- no implicit global state mutation in boot helpers

## ruff constraints

- no hidden side effects in bootframe functions
- no mutable default arguments
- no circular import regressions between kernel and lifecycle

## Migration mapping from existing modules

- `src/k501/core/lifecycle.py` → KEEP and formalize.
- `src/k501/core/kernel.py` → KEEP only if it becomes boot/runtime orchestration.
- any boot logic in CLI or storage should move here.

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
├── validator.py
├── lifecycle.py
└── kernel.py
tests/unit/
└── test_bootframes.py
tests/integration/
└── test_boot_and_recover.py
```