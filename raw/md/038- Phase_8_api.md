# Phase_8_api.md

This phase adds the HTTP API surface over the frozen runtime. The API is operational only and must not redefine architecture [web:178][web:187].

## Target files

- `src/k501/api/__init__.py`
- `src/k501/api/routes/*.py`
- `src/k501/api/middleware/*.py`
- `tests/unit/test_api.py`
- `tests/integration/test_api_replay.py`

## Dataclasses

- `APIRequest`
- `APIResponse`
- `ValidationPayload` if needed

## Functions

- route handlers for transitions, projection, replay validation, graph build, archive freeze, archive replay
- request parsing helpers
- response serialization helpers

## Public interfaces

- `POST /transitions`
- `GET /transitions/{transition_id}`
- `GET /states/{state_id}`
- `POST /replay/validate`
- `POST /graph/build`
- `POST /archives/freeze`
- `POST /archives/replay`

## pytest tests

- transition append endpoint returns deterministic ID
- transition fetch endpoint returns same record
- state projection endpoint matches projection logic
- replay validation endpoint reports digest equivalence
- invalid payloads return stable errors

## mypy constraints

- request/response types explicit
- no untyped route handlers
- no dynamic response dictionaries in public signatures

## ruff constraints

- no business logic duplication from core modules
- no silent exception masking in middleware
- no route-local ontology changes

## Migration mapping from existing modules

- `src/k501/api/*` → KEEP and formalize.
- middleware and routes should wrap core/storage, not replace them.

## Estimated git commits

- 2 commits.

## Expected repository tree after completion

```text
src/k501/api/
├── __init__.py
├── middleware/
└── routes/
tests/unit/
└── test_api.py
tests/integration/
└── test_api_replay.py
```