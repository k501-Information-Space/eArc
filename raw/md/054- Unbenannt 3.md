Here is a complete Phase 4.5 manifestation consistent with the architecture you have been building.

### Create Runtime

```bash
nano src/k501/core/lineage_query_runtime.py
```

```python
from __future__ import annotations

from typing import TypeAlias

ProofId: TypeAlias = str
Graph: TypeAlias = dict[ProofId, list[ProofId]]


class LineageQueryRuntime:
    """
    Pure lineage traversal runtime.

    Responsibilities:

    - contains()
    - find_ancestors()
    - find_root()
    - trace()

    No archive loading.
    No file operations.
    No registry access.
    No persistence.
    """

    @staticmethod
    def contains(
        graph: Graph,
        proof_id: ProofId,
    ) -> bool:
        return proof_id in graph

    @staticmethod
    def find_ancestors(
        graph: Graph,
        proof_id: ProofId,
    ) -> list[ProofId]:

        if not LineageQueryRuntime.contains(
            graph,
            proof_id,
        ):
            return []

        ancestors: list[ProofId] = []

        current = proof_id

        while True:
            parents = graph[current]

            if not parents:
                break

            current = parents[0]

            ancestors.append(
                current,
            )

        return ancestors

    @staticmethod
    def find_root(
        graph: Graph,
        proof_id: ProofId,
    ) -> ProofId | None:

        if not LineageQueryRuntime.contains(
            graph,
            proof_id,
        ):
            return None

        current = proof_id

        while True:
            parents = graph[current]

            if not parents:
                return current

            current = parents[0]

    @staticmethod
    def trace(
        graph: Graph,
        proof_id: ProofId,
    ) -> list[ProofId]:

        if not LineageQueryRuntime.contains(
            graph,
            proof_id,
        ):
            return []

        path: list[ProofId] = []

        current = proof_id

        while True:
            path.append(
                current,
            )

            parents = graph[current]

            if not parents:
                break

            current = parents[0]

        path.reverse()

        return path
```

---

### Create Tests

```bash
nano tests/unit/test_lineage_query_runtime.py
```

```python
from k501.core.lineage_query_runtime import (
    LineageQueryRuntime,
)


def build_lineage_graph() -> dict[str, list[str]]:
    return {
        "proof:001": [],
        "proof:002": [
            "proof:001",
        ],
        "proof:003": [
            "proof:002",
        ],
        "proof:004": [
            "proof:003",
        ],
    }


def test_contains_true() -> None:

    graph = build_lineage_graph()

    assert (
        LineageQueryRuntime.contains(
            graph,
            "proof:003",
        )
        is True
    )


def test_contains_false() -> None:

    graph = build_lineage_graph()

    assert (
        LineageQueryRuntime.contains(
            graph,
            "proof:999",
        )
        is False
    )


def test_find_ancestors() -> None:

    graph = build_lineage_graph()

    ancestors = (
        LineageQueryRuntime.find_ancestors(
            graph,
            "proof:004",
        )
    )

    assert ancestors == [
        "proof:003",
        "proof:002",
        "proof:001",
    ]


def test_find_ancestors_root() -> None:

    graph = build_lineage_graph()

    ancestors = (
        LineageQueryRuntime.find_ancestors(
            graph,
            "proof:001",
        )
    )

    assert ancestors == []


def test_find_root() -> None:

    graph = build_lineage_graph()

    root = (
        LineageQueryRuntime.find_root(
            graph,
            "proof:004",
        )
    )

    assert root == "proof:001"


def test_find_root_root() -> None:

    graph = build_lineage_graph()

    root = (
        LineageQueryRuntime.find_root(
            graph,
            "proof:001",
        )
    )

    assert root == "proof:001"


def test_find_root_not_found() -> None:

    graph = build_lineage_graph()

    root = (
        LineageQueryRuntime.find_root(
            graph,
            "proof:999",
        )
    )

    assert root is None


def test_trace() -> None:

    graph = build_lineage_graph()

    trace = (
        LineageQueryRuntime.trace(
            graph,
            "proof:004",
        )
    )

    assert trace == [
        "proof:001",
        "proof:002",
        "proof:003",
        "proof:004",
    ]


def test_trace_root() -> None:

    graph = build_lineage_graph()

    trace = (
        LineageQueryRuntime.trace(
            graph,
            "proof:001",
        )
    )

    assert trace == [
        "proof:001",
    ]


def test_trace_not_found() -> None:

    graph = build_lineage_graph()

    trace = (
        LineageQueryRuntime.trace(
            graph,
            "proof:999",
        )
    )

    assert trace == []


def test_trace_deterministic() -> None:

    graph = build_lineage_graph()

    results = [
        LineageQueryRuntime.trace(
            graph,
            "proof:004",
        )
        for _ in range(100)
    ]

    assert all(
        result == results[0]
        for result in results
    )
```

---

# Verification

```bash
python -m py_compile \
src/k501/core/lineage_query_runtime.py

python -m py_compile \
tests/unit/test_lineage_query_runtime.py
```

Run phase tests:

```bash
uv run pytest -v \
tests/unit/test_lineage_query_runtime.py
```

Expected:

```text
11 passed
```

---

# Full Validation

```bash
python -m compileall src

uv run mypy src

uv run pytest

uv run ruff check .
```

Expected:

```text
All checks passed
```

---

# Commit Manifestation

```bash
git add \
src/k501/core/lineage_query_runtime.py

git add \
tests/unit/test_lineage_query_runtime.py

git commit -m \
"manifest lineage query runtime pure traversal"

git tag \
phase4-lineage-query-runtime-v1
```

---

### Updated Ladder

```text
Transition
    ↓
Journal
    ↓
Index
    ↓
Projection
    ↓
Replay
    ↓
Snapshot
    ↓
Freeze
    ↓
Audit
    ↓
Proof
    ↓
Receipt
    ↓
Archive
    ↓
Archive Store
    ↓
Archive Index
    ↓
Receipt Registry
    ↓
Proof Graph
    ↓
Lineage Query
```

Phase 4.5 is the point where the Information Space gains deterministic lineage navigation: not just storing and proving history, but traversing it.