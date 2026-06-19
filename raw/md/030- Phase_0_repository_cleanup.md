# Phase_0_repository_cleanup.md

This phase prepares the repository for the frozen K501-AIONARC specification without changing ontology or axioms. It aligns the codebase with a `src/` layout, removes drift, and makes later phases mechanically safer [web:178][web:185][web:187].

## Target files

- `pyproject.toml`
- `pytest.ini`
- `ruff.toml` or `.ruff.toml`
- `mypy.ini` or `[tool.mypy]` in `pyproject.toml`
- `.gitignore`
- `src/k501/__init__.py`
- `src/k501/core/__init__.py`
- `src/k501/storage/__init__.py`
- `src/k501/graph/__init__.py`
- `src/k501/evidence/__init__.py`
- `tests/conftest.py`
- `tests/unit/*`
- `src/k501/storage/index_store.py`
- `src/k501/storage/evidence_store.py`
- `src/k501/storage/archive_store.py`
- generated artifacts under `src/k501/__pycache__/`, `k501_aionarc.egg-info/`

## Dataclasses

- None added in this phase.
- Existing dataclasses are only reviewed for naming and import stability.

## Functions

- No new business functions.
- Cleanup helpers only if needed for test fixtures or import paths.

## Public interfaces

- No new public interfaces.
- Preserve current import paths where possible.
- Stabilize package root so future modules resolve from `src/k501`.

## pytest tests

- Existing 17 tests must keep passing.
- Add a repository-structure smoke test if needed:
  - import package root
  - import storage modules
  - confirm no accidental root-level imports

## mypy constraints

- Keep `mypy` passing on `src`.
- Avoid introducing any `Any`-heavy cleanup helpers.
- Preserve current type contracts for existing storage objects.

## ruff constraints

- No unused imports.
- No redefined names.
- No wildcard imports.
- No import-order regressions.
- No new lint suppressions unless absolutely required.

## Migration mapping from existing modules

- `src/k501/storage/index_store.py` → KEEP.
- `src/k501/storage/evidence_store.py` → STORAGE.
- `src/k501/storage/archive_store.py` → STORAGE.
- `src/k501/core/*` → review-only; no ontology changes.
- `src/k501/evidence/*` → classify later; keep only if transition-backed.
- `src/k501/graph/*` → keep structure, but later phases will formalize behavior.
- remove generated caches and egg-info artifacts from version control.

## Estimated git commits

- 1 commit for repository cleanup and packaging stabilization.

## Expected repository tree after completion

```text
src/
└── k501/
    ├── __init__.py
    ├── core/
    ├── storage/
    ├── graph/
    └── evidence/
tests/
pyproject.toml
pytest.ini
ruff.toml
mypy.ini
```