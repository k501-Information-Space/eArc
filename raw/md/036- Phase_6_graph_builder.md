# Phase_6_graph_builder.md

This phase builds the transition-centric graph from transitions. The graph remains reconstructable and non-authoritative [web:183][web:178].

## Target files

- `src/k501/graph/models.py`
- `src/k501/graph/store.py`
- `src/k501/graph/validator.py`
- `tests/unit/test_graph_builder.py`
- `tests/integration/test_graph_rebuild.py`

## Dataclasses

- `TransitionNode`
- `TransitionEdge`
- `GraphBuildResult`
- `GraphValidationResult` if needed

## Functions

- `build_graph(transitions) -> graph`
- `add_node(...)`
- `add_edge(...)`
- `validate_dag(...)`
- `rebuild_graph(...)`
- `lineage(...)`
- `provenance(...)`

## Public interfaces

- `TransitionGraph`
- `GraphValidator`

## pytest tests

- graph rebuild from transitions succeeds
- derived_from edges are reconstructable
- validation catches cycles
- graph is deterministic for same transition stream
- provenance edges are derived from transitions

## mypy constraints

- graph node and edge dataclasses typed strictly
- adjacency maps typed precisely
- no graph persistence authority beyond reconstructable storage

## ruff constraints

- no reliance on insertion order for graph correctness
- no mutable default arguments in graph builders
- no untyped traversal helpers

## Migration mapping from existing modules

- `src/k501/graph/*` → KEEP and formalize.
- any graph persistence not derived from transitions → remove from authority path.

## Estimated git commits

- 2 commits.

## Expected repository tree after completion

```text
src/k501/graph/
├── __init__.py
├── models.py
├── store.py
└── validator.py
tests/unit/
└── test_graph_builder.py
tests/integration/
└── test_graph_rebuild.py
```