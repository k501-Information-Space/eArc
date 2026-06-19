Um Phase 1 gemäß deiner Frozen Specification sauber abzuschließen, sollte `IdentityValidator` nicht nur prüfen, ob eine `transition_id` existiert, sondern die Identität vollständig neu berechnen und vergleichen.

## 1. validator.py ersetzen

`src/k501/core/validator.py`

```python
from __future__ import annotations

from dataclasses import dataclass

from k501.core.transition import (
    Transition,
    compute_transition_id,
    transition_identity_payload,
)


@dataclass(frozen=True)
class IdentityValidationResult:
    valid: bool
    expected_transition_id: str
    actual_transition_id: str


class IdentityValidator:
    @staticmethod
    def validate(
        transition: Transition,
    ) -> IdentityValidationResult:
        payload = transition_identity_payload(
            object_id=transition.object_id,
            content=transition.content,
            provenance=transition.provenance,
        )

        expected_transition_id = compute_transition_id(payload)

        return IdentityValidationResult(
            valid=expected_transition_id == transition.transition_id,
            expected_transition_id=expected_transition_id,
            actual_transition_id=transition.transition_id,
        )
```

---

## 2. validator tests erweitern

`tests/unit/test_identity_validator.py`

```python
from k501.core.transition import Transition
from k501.core.validator import IdentityValidator


def test_identity_validator_accepts_valid_transition() -> None:
    transition = Transition.create(
        object_id="frame:test",
        timestamp_ns=123,
        content={"status": "active"},
        metadata={"source": "unit"},
        provenance=[],
    )

    result = IdentityValidator.validate(transition)

    assert result.valid is True


def test_identity_validator_rejects_modified_transition() -> None:
    transition = Transition.create(
        object_id="frame:test",
        timestamp_ns=123,
        content={"status": "active"},
        metadata={"source": "unit"},
        provenance=[],
    )

    tampered = transition.model_copy(
        update={
            "transition_id": "invalid-transition-id",
        }
    )

    result = IdentityValidator.validate(tampered)

    assert result.valid is False


def test_transition_id_excludes_timestamp() -> None:
    left = Transition.create(
        object_id="frame:test",
        timestamp_ns=111,
        content={"status": "active"},
        metadata={},
        provenance=[],
    )

    right = Transition.create(
        object_id="frame:test",
        timestamp_ns=999,
        content={"status": "active"},
        metadata={},
        provenance=[],
    )

    assert left.transition_id == right.transition_id


def test_transition_id_excludes_metadata() -> None:
    left = Transition.create(
        object_id="frame:test",
        timestamp_ns=1,
        content={"status": "active"},
        metadata={"source": "a"},
        provenance=[],
    )

    right = Transition.create(
        object_id="frame:test",
        timestamp_ns=1,
        content={"status": "active"},
        metadata={"source": "b"},
        provenance=[],
    )

    assert left.transition_id == right.transition_id


def test_provenance_affects_transition_identity() -> None:
    left = Transition.create(
        object_id="frame:test",
        timestamp_ns=1,
        content={"status": "active"},
        metadata={},
        provenance=[],
    )

    right = Transition.create(
        object_id="frame:test",
        timestamp_ns=1,
        content={"status": "active"},
        metadata={},
        provenance=["parent-transition"],
    )

    assert left.transition_id != right.transition_id
```

---

## 3. Validation Run

```bash
uv run mypy src

uv run pytest

uv run ruff check .
```

Expected:

```text
Success: no issues found
All checks passed
29 passed
```

(or whatever your current test count becomes)

---

## 4. Commit

```bash
git add src/k501/core/validator.py

git add tests/unit/test_identity_validator.py

git commit -m "complete transition identity validation kernel"
```

---

## 5. Tag

```bash
git tag proof-v3-transition-kernel
```

---

## Expected Git History

```text
v3-canonical
v4-journal
proof-v3-transition-kernel
```

At that point, under the frozen roadmap:

```text
Phase_0_repository_cleanup      COMPLETE
Phase_1_transition_kernel       COMPLETE
Phase_2_journal_runtime         NEXT
```

and you can proceed to implementing the authoritative append-only journal runtime without leaving unresolved identity semantics behind.