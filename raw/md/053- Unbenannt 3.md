I agree with that scope for **Phase 4.5 v1**.

Keep it intentionally small and pure.

The runtime should know only one thing:

```text
proof_id
    ↕
graph
```

and nothing about:

```text
Archive Store

Archive Index

Receipt Registry

Filesystem

Persistence

Loading
```

That preserves the separation you've established since TransitionV2.

---

## Phase 4.5

```text
LineageQueryRuntime
```

Responsibilities:

```text
contains()

find_ancestors()

find_root()

trace()
```

Nothing else.

---

## Runtime Placement

```text
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

Proof Graph owns topology.

Lineage Query owns traversal.

---

## Query Semantics

### contains()

```python
LineageQueryRuntime.contains(
    graph,
    proof_id,
)
```

Returns:

```python
True
```

or

```python
False
```

Purpose:

```text
Existence check
```

---

### find_ancestors()

```python
LineageQueryRuntime.find_ancestors(
    graph,
    proof_id,
)
```

Input:

```text
proof:004
    ↓
proof:003
    ↓
proof:002
    ↓
proof:001
```

Output:

```python
[
    "proof:003",
    "proof:002",
    "proof:001",
]
```

Purpose:

```text
Complete lineage ancestry
```

---

### find_root()

```python
LineageQueryRuntime.find_root(
    graph,
    proof_id,
)
```

Input:

```text
proof:004
    ↓
proof:003
    ↓
proof:002
    ↓
proof:001
```

Output:

```python
"proof:001"
```

Purpose:

```text
Locate origin proof
```

---

### trace()

```python
LineageQueryRuntime.trace(
    graph,
    proof_id,
)
```

Output:

```python
[
    "proof:001",
    "proof:002",
    "proof:003",
    "proof:004",
]
```

Purpose:

```text
Canonical lineage reconstruction
```

---

## Determinism Rules

The runtime should remain:

```text
Pure

Deterministic

Memory-only

Side-effect free
```

Meaning:

```python
trace(graph, proof_id)
```

must always produce:

```python
same graph
+
same proof_id

=
same output
```

---

## Expected Internal Structure

Assuming your ProofGraphRuntime currently emits:

```python
graph = {
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
```

Then all Phase 4.5 queries operate entirely against this object.

No lookups.

No loading.

No archive resolution.

No receipt resolution.

---

## Manifestation Target

After Phase 4.5:

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

At that point the Information Space gains its first true lineage navigation capability:

```text
Store
    ✓

Verify
    ✓

Preserve
    ✓

Graph
    ✓

Traverse
    ✓
```

which is the natural completion of Phase 4.5.