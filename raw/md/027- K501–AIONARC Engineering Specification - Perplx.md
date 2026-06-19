# K501–AIONARC Engineering Specification

This specification formalizes K501–AIONARC as a deterministic, append-only, locally reconstructable transition system. It aligns with the architecture refined in the chat history: **identity is not occurrence, transitions are canonical, projections are disposable, provenance is transition-derived, and replay validation must be order-sensitive**.[[github](https://github.com/trailofbits/rfc8785.py)]

## 1. System Contract

K501–AIONARC is a **transition-centric persistence kernel**, not a generic event-sourcing system, not a Git clone, and not a semantic knowledge graph. Its canonical truth is the append-only transition stream; everything else is derived from it. The system must remain `PURE_LOGIC`, `PURE_QH256`, `APPEND_ONLY`, `NO_DRIFT`, `RECONSTRUCTABLE`, `DETERMINISTIC`, `LOCAL_FIRST`, and `PHYSICAL_PERSISTENCE`.

## Canonical interpretation

- **Transitions** are the only canonical records.
    
- **StateObjects** are projections, not primary facts.
    
- **Graph structures** are derived from transitions.
    
- **Evidence records** survive only if they are transition-backed.
    
- **Replay** must reproduce both ordered stream identity and derived projections.
    

## 2. Foundational Axioms

## 2.1 `IDENTITY_AXIOM_0`

Transition identity SHALL be computed from:

- `before_state_id`
    
- `after_state_id`
    
- `transition_type`
    
- `content`
    
- `provenance_transition_ids`
    

Excluded from identity:

- `timestamp_ns`
    
- `metadata`
    

Identity is invariant under replay, relocation, and storage backend changes.

## 2.2 `REPLAY_AXIOM_0`

Replay identity SHALL be:

SHA256(RFC8785(ordered_transition_ids))\text{SHA256}(\text{RFC8785}(\text{ordered\_transition\_ids}))SHA256(RFC8785(ordered_transition_ids))

Replay digest MUST detect:

- reordering
    
- insertion
    
- deletion
    
- mutation
    

Replay digest SHALL be order-sensitive, and replay validation SHALL compare ordered transition IDs, derived projections, replay digest, and graph topology.

## 2.3 `PROJECTION_AXIOM_0`

StateObjects are projections. Transitions are canonical.  
StateObjects SHALL NOT possess independent identity.  
StateObjects MUST be reconstructable solely from transitions.

## 2.4 `PROVENANCE_AXIOM_0`

Provenance is transition-derived.  
Proofs, audits, imports, freezes, validations, and archives are represented as transitions.  
No mutable provenance dictionaries are permitted.

## 3. QH256 Model

QH256 is foundational information geometry, independent of persistence. Its cell states are:

- `UNKNOWN` = `00`
    
- `FALSE` = `01`
    
- `TRUE` = `10`
    
- `GUARD` = `11`
    

QH256 MUST remain independent from graph databases and LLM frameworks. It SHALL NOT contain semantic assertions. It is a representational substrate, not a truth engine.

## 4. Runtime Model

The runtime is a transition engine with a strict boot sequence and a deterministic lifecycle.

## 4.1 Boot sequence

- `BOOTFRAME_0`: load configuration, validate filesystem layout.
    
- `BOOTFRAME_1`: open journal and rebuild transition index.
    
- `BOOTFRAME_2`: verify replay digest and segment integrity.
    
- `BOOTFRAME_3`: activate runtime services and validators.
    

## 4.2 Runtime states

- `EMPTY`
    
- `ACTIVE`
    
- `FROZEN`
    
- `ARCHIVED`
    

## 4.3 Operations

- `append_transition`
    
- `project_state`
    
- `build_graph`
    
- `freeze_archive`
    
- `replay_archive`
    
- `validate_replay`
    

Crash recovery SHALL be supported. Partial writes SHALL be detectable. Tail corruption SHALL be recoverable.

## 5. Storage Architecture

Storage SHALL be local-first and append-only.

## 5.1 Canonical persistence layer

The authoritative store is a JSONL append-only journal:

text

`data/ └── journal/     └── transitions.jsonl`

## 5.2 Optional layers

- segment files
    
- frozen archives
    
- rebuildable indexes
    

## 5.3 Required files

text

`data/ ├── journal/ │   └── transitions.jsonl ├── segments/ │   └── segment_000001.aion ├── archives/ │   └── archive_000001.aion └── indexes/     ├── transition.idx    └── replay_digest.txt`

## 5.4 Storage rules

- Journal is authoritative.
    
- Archives are frozen snapshots.
    
- Indexes are accelerators only.
    
- Indexes MUST be rebuildable.
    
- Storage layers MUST support recovery after crash or tail truncation.
    

## 6. Directory Tree

## Repository layout

text

`k501-aionarc/ ├── pyproject.toml ├── README.md ├── LICENSE ├── Makefile ├── .gitignore ├── src/ │   └── k501/ │       ├── __init__.py │       ├── core/ │       │   ├── __init__.py │       │   ├── canonical.py │       │   ├── transition.py │       │   ├── projection.py │       │   ├── replay.py │       │   └── validator.py │       ├── storage/ │       │   ├── __init__.py │       │   ├── journal.py │       │   ├── segment_store.py │       │   ├── archive_store.py │       │   └── index_store.py │       ├── graph/ │       │   ├── __init__.py │       │   ├── models.py │       │   ├── store.py │       │   └── validator.py │       ├── evidence/ │       │   ├── __init__.py │       │   ├── proof.py │       │   ├── audit.py │       │   ├── receipt.py │       │   └── pointer.py │       ├── api/ │       │   ├── __init__.py │       │   └── routes/ │       └── cli/ │           ├── __init__.py │           └── main.py ├── tests/ │   ├── unit/ │   ├── integration/ │   └── e2e/ └── docs/     └── adr/`

## 7. Package Layout

## 7.1 Core

`core/` contains canonical serialization, transition schema, projection logic, replay logic, and validators.

## 7.2 Storage

`storage/` contains the authoritative journal and its accelerators:

- `journal.py`
    
- `segment_store.py`
    
- `archive_store.py`
    
- `index_store.py`
    

## 7.3 Graph

`graph/` contains transition-centric graph models and validators. Graph is reconstructable and never authoritative.

## 7.4 Evidence

`evidence/` MAY survive only if all records are transition-backed. If not transition-backed, they are legacy and should be removed.

## 7.5 API and CLI

`api/` and `cli/` are operational surfaces. They do not define truth; they expose kernel operations.

## 8. Dataclass Schemas

## 8.1 Transition schema

python

`@dataclass(frozen=True) class Transition:     transition_id: str    before_state_id: str | None    after_state_id: str    transition_type: str    timestamp_ns: int    content: dict[str, Any]    provenance_transition_ids: list[str]    metadata: dict[str, Any]`

## Constraints

- `timestamp_ns` is explicit input.
    
- `timestamp_ns` is an integer nanosecond epoch.
    
- `timestamp_ns` participates in occurrence, not identity.
    
- Identity MUST be derived from all identity fields via RFC8785 canonicalization.
    

## 8.2 StateObject schema

python

`@dataclass(frozen=True) class StateObject:     state_id: str    transition_id: str    object_type: str    namespace: str    version: str    payload: dict[str, Any]    validation: dict[str, Any]    trust: dict[str, Any]    lineage: dict[str, Any]`

## Constraints

- StateObject SHALL be a projection.
    
- StateObject SHALL be disposable.
    
- StateObject SHALL be rebuildable from transitions alone.
    

## 8.3 Graph node schema

python

`@dataclass(frozen=True) class TransitionNode:     node_id: str    transition_id: str    transition_type: str    timestamp_ns: int    attributes: dict[str, Any]`

## 8.4 Graph edge schema

python

`@dataclass(frozen=True) class TransitionEdge:     edge_id: str    source_id: str    edge_type: str    target_id: str    attributes: dict[str, Any]`

## 9. JSON Schemas

## 9.1 Transition JSON schema

json

`{   "type": "object",  "required": [    "transition_id",    "before_state_id",    "after_state_id",    "transition_type",    "timestamp_ns",    "content",    "provenance_transition_ids",    "metadata"  ],  "properties": {    "transition_id": { "type": "string" },    "before_state_id": { "type": ["string", "null"] },    "after_state_id": { "type": "string" },    "transition_type": { "type": "string" },    "timestamp_ns": { "type": "integer" },    "content": { "type": "object" },    "provenance_transition_ids": {      "type": "array",      "items": { "type": "string" }    },    "metadata": { "type": "object" }  },  "additionalProperties": false }`

## 9.2 StateObject JSON schema

json

`{   "type": "object",  "required": [    "state_id",    "transition_id",    "object_type",    "namespace",    "version",    "payload",    "validation",    "trust",    "lineage"  ],  "properties": {    "state_id": { "type": "string" },    "transition_id": { "type": "string" },    "object_type": { "type": "string" },    "namespace": { "type": "string" },    "version": { "type": "string" },    "payload": { "type": "object" },    "validation": { "type": "object" },    "trust": { "type": "object" },    "lineage": { "type": "object" }  },  "additionalProperties": false }`

## 9.3 Graph edge schema

json

`{   "type": "object",  "required": ["edge_id", "source_id", "edge_type", "target_id", "attributes"],  "properties": {    "edge_id": { "type": "string" },    "source_id": { "type": "string" },    "edge_type": { "type": "string" },    "target_id": { "type": "string" },    "attributes": { "type": "object" }  },  "additionalProperties": false }`

## 10. RFC8785 Serialization

Use `rfc8785.dumps()` as the canonical primitive.[[datatracker.ietf](https://datatracker.ietf.org/doc/html/rfc8785)]

## Interfaces

python

`def canonical_bytes(obj) -> bytes def canonical_string(obj) -> str def canonical_hash(obj) -> str`

## Example

python

`payload = {     "after_state_id": "state:001",    "before_state_id": None,    "transition_type": "create" } canonical = rfc8785.dumps(payload)`

If the library returns bytes, preserve bytes for hashing; only decode when string output is required.

## 11. Journal Format

The journal is authoritative append-only JSONL.

## File

`data/journal/transitions.jsonl`

## Record format

One canonical JSON object per line:

json

`{"transition_id":"...","before_state_id":null,"after_state_id":"...","transition_type":"create","timestamp_ns":0,"content":{},"provenance_transition_ids":[],"metadata":{}}`

## Rules

- One transition per line.
    
- Canonical JSON only.
    
- No in-place modification.
    
- No deletion.
    
- No rewriting for normal operation.
    

## 12. Segment Format

Segments are optional write-ahead or rotation units.

## File

`data/segments/segment_000001.aion`

## Suggested structure

- header
    
- framed records
    
- trailer checksum
    
- segment digest
    

## Record framing

Each record SHOULD contain:

- record length
    
- canonical payload bytes
    
- checksum
    

## Segment purpose

- tail recovery
    
- bounded compaction
    
- archival rotation
    
- fast rebuild
    

Segments are accelerators, not truth.

## 13. Archive Format

Archives are frozen snapshots.

## File

`data/archives/archive_000001.aion`

## Properties

- immutable
    
- content-addressed or segment-derived
    
- replayable
    
- deterministic
    

## Archive contents

- ordered transition IDs
    
- optional full transition payloads
    
- archive digest
    
- head transition ID
    
- transition count
    

## 14. Replay Semantics

Replay reconstructs state from the authoritative transition stream.

## Replay algorithm

1. Read transitions in canonical order.
    
2. Verify each record hash and schema.
    
3. Verify identity hash for each transition.
    
4. Rebuild projections.
    
5. Rebuild graph topology.
    
6. Compute ordered stream digest.
    
7. Compare against stored replay digest.
    
8. Emit validation result.
    

## Digest algorithm

replay_digest=SHA256(RFC8785([transition_id1,…,transition_idn]))\text{replay\_digest} = SHA256(\text{RFC8785}([\text{transition\_id}_1, \dots, \text{transition\_id}_n]))replay_digest=SHA256(RFC8785([transition_id1​,…,transition_idn​]))

## Additional replay invariants

Store and validate:

- `HEAD_TRANSITION_ID`
    
- `STREAM_LENGTH`
    
- `STREAM_DIGEST`
    

This distinguishes full archive identity from prefix identity.

## 15. Projection Semantics

StateObjects are derived by folding transitions.

## Projection algorithm

- Initialize empty projection state.
    
- Apply transitions in canonical order.
    
- Materialize StateObject on demand.
    
- Discard and rebuild as necessary.
    

Projection is replayable and disposable.

## 16. Graph Model

The graph is transition-centric.

## Nodes

- `TransitionNode`
    

## Edges

- `DERIVED_FROM`
    
- `VALIDATED_BY`
    
- `AUDITED_BY`
    
- `SUPERSEDES`
    
- `REFERENCES`
    

## Graph rules

- Graph SHALL be reconstructable from transitions.
    
- Graph SHALL NOT be authoritative persistence.
    
- Graph MAY be materialized for traversal and validation.
    
- Graph topology MUST be reproducible.
    

## 17. Validators

Required validators:

- `IdentityValidator`
    
- `ReplayValidator`
    
- `ChronologyValidator`
    
- `DAGValidator`
    
- `SegmentValidator`
    
- `ArchiveValidator`
    

## 17.1 IdentityValidator

Confirms `transition_id` matches canonical hash of identity fields.

## 17.2 ReplayValidator

Compares:

- ordered transition IDs
    
- derived projections
    
- replay digest
    
- graph topology
    

## 17.3 ChronologyValidator

Checks:

- explicit `timestamp_ns`
    
- monotonic ordering rules where required
    
- no future-dated transitions outside policy
    

## 17.4 DAGValidator

Checks transition graph for cycles in ancestry relations.

## 17.5 SegmentValidator

Checks:

- framing
    
- checksum
    
- tail completeness
    
- recoverability
    

## 17.6 ArchiveValidator

Checks:

- frozen immutability
    
- digest consistency
    
- head and length consistency
    
- replayability
    

## 18. Runtime Operations

## 18.1 `append_transition`

- validate input
    
- compute transition ID
    
- append canonical record
    
- update index
    
- update digest
    
- optionally rotate segment
    
- return transition ID
    

## 18.2 `project_state`

- locate target state
    
- replay relevant transitions
    
- materialize StateObject
    
- return disposable projection
    

## 18.3 `build_graph`

- derive nodes and edges from transitions
    
- validate DAG properties
    
- persist only derived artifacts if configured
    

## 18.4 `freeze_archive`

- stop writes or freeze current head
    
- seal current segment/archive
    
- write archive digest
    
- mark archive immutable
    

## 18.5 `replay_archive`

- load archive
    
- verify archive digest
    
- reconstruct transitions
    
- rebuild projections and graph
    
- validate equivalence
    

## 18.6 `validate_replay`

- compare original and replayed stream digests
    
- compare ordered IDs
    
- compare projections
    
- compare graph topology
    
- emit deterministic validation result
    

## 19. CLI Commands

Recommended CLI surface:

text

`k501 init k501 append k501 project k501 graph build k501 archive freeze k501 archive replay k501 validate replay k501 validate segment k501 validate archive k501 rebuild index k501 inspect head`

## 20. API Endpoints

If exposed over HTTP, APIs must remain operational surfaces only.

## Recommended endpoints

- `POST /transitions`
    
- `GET /transitions/{transition_id}`
    
- `GET /states/{state_id}`
    
- `POST /replay/validate`
    
- `POST /graph/build`
    
- `GET /graph/{node_id}`
    
- `GET /archives/{archive_id}`
    
- `POST /archives/{archive_id}/replay`
    

## 21. Boot Sequence Diagram

text

`BOOTFRAME_0   ↓ load config   ↓ BOOTFRAME_1   ↓ open journal / rebuild index   ↓ BOOTFRAME_2   ↓ verify digest / scan tail   ↓ BOOTFRAME_3   ↓ activate runtime`

## 22. State Machine

text

`EMPTY -> ACTIVE -> FROZEN -> ARCHIVED    ↘                 ↘    recoverable        replayable`

## Allowed transitions

- `EMPTY` → `ACTIVE`
    
- `ACTIVE` → `FROZEN`
    
- `FROZEN` → `ARCHIVED`
    
- `ACTIVE` → recovery
    
- `FROZEN` → recovery
    
- `ARCHIVED` → replay
    

## 23. Crash Recovery

## Required properties

- Partial writes SHALL be detectable.
    
- Tail corruption SHALL be recoverable.
    
- Incomplete segments SHALL be truncatable.
    
- Rebuild from journal SHALL be possible.
    

## Recovery algorithm

1. Scan journal/segment tail.
    
2. Validate framing and checksum.
    
3. Truncate incomplete tail.
    
4. Rebuild index.
    
5. Recompute replay digest.
    
6. Rebuild projections if needed.
    
7. Resume from last valid head.
    

## 24. Storage Lifecycle

1. Append transitions to journal.
    
2. Periodically rotate to segment.
    
3. Freeze segment into archive.
    
4. Rebuild or discard indexes as needed.
    
5. Verify digest equality at each lifecycle boundary.
    

## 25. Test Plan

Use `pytest`, `ruff`, and `mypy`.

## Unit tests

- Replay determinism
    
- Duplicate detection
    
- Projection reconstruction
    
- Segment rebuild
    
- Archive replay
    

## Integration tests

- 100000 transitions replay
    
- crash recovery after tail truncation
    
- index rebuild equivalence
    
- archive freeze and replay parity
    

## End-to-end tests

- archive
    
- restore
    
- rebuild
    
- digest equality
    

## 26. Migration Strategy

The current repository should be migrated in phases.

## KEEP

- `src/k501/core/transition.py` if aligned with `IDENTITY_AXIOM_0`
    
- `src/k501/storage/index_store.py` if it becomes a rebuildable accelerator
    
- `src/k501/storage/archive_store.py` if it becomes frozen archive layer
    
- `src/k501/storage/evidence_store.py` only if it is transition-backed
    
- existing validation pipeline tests, if they are still semantically valid
    

## PROJECTION

- `frame.py`
    
- `snapshot.py`
    
- `state_object.py`
    
- any module that reconstructs state from transitions
    
- any view-only object that is not canonical truth
    

## STORAGE

- `journal.py`
    
- `segment_store.py`
    
- `archive_store.py`
    
- `index_store.py`
    

## LEGACY

- `proof.py`
    
- `audit.py`
    
- `receipt.py`
    
- `pointer.py`
    
- `kernel.py`
    
- `axiom.py` if it overlaps the new axiom modules and does not encode the canonical contract cleanly
    

## REMOVE

- `__pycache__`
    
- generated artifacts
    
- non-reconstructable semantic stores
    
- any mutable provenance dictionaries in core state
    

## 27. Existing Module Classification

Based on your current repository tree, the likely classification is:

|Module|Classification|Notes|
|---|---|---|
|`core/archive.py`|PROJECTION|likely derived archive semantics|
|`core/axiom.py`|LEGACY|replace with explicit axiom modules|
|`core/frame.py`|PROJECTION|likely legacy state container|
|`core/freeze.py`|PROJECTION|freeze is a transition, not a noun store|
|`core/kernel.py`|LEGACY|likely too broad / ontology-bundled|
|`core/lifecycle.py`|PROJECTION|lifecycle should be runtime state machine|
|`core/snapshot.py`|PROJECTION|disposable projection|
|`core/state_object.py`|PROJECTION|canonical StateObject projection|
|`evidence/audit.py`|LEGACY or KEEP|keep only if transition-backed|
|`evidence/index.py`|STORAGE|accelerator / index surface|
|`evidence/pointer.py`|LEGACY or KEEP|keep only if pointer is a transition-backed reference|
|`evidence/proof.py`|LEGACY or KEEP|keep only if proof is a transition|
|`evidence/receipt.py`|LEGACY or KEEP|keep only if receipt is a transition|
|`storage/archive_store.py`|STORAGE|required|
|`storage/evidence_store.py`|STORAGE or REMOVE|only if strictly journal-backed|
|`storage/index_store.py`|STORAGE|required as rebuildable accelerator|
|`agent/`|LEGACY|outside core kernel unless explicitly needed|
|`retrieval/`|LEGACY|derived querying, not kernel truth|
|`graph/`|PROJECTION|reconstructable topology|
|`api/`|OPERATIONS|exposure layer|
|`workers/`|OPERATIONS|optional runtime orchestration|
|`embeddings/`|REMOVE|unless strictly required and transition-backed|
|`observability/`|OPERATIONS|optional telemetry, not truth|

## 28. Recommended Engineering Milestones

## Milestone A: Canonical kernel

- canonical serialization
    
- transition identity
    
- replay digest
    
- projection fold
    
- validator core
    

## Milestone B: Storage correctness

- journal writer
    
- segment rotation
    
- index rebuild
    
- tail recovery
    
- archive freeze
    

## Milestone C: Graph and provenance

- transition graph
    
- lineage traversal
    
- provenance transitions
    
- DAG validation
    

## Milestone D: Operational surfaces

- CLI
    
- API
    
- runtime lifecycle
    
- boot sequence
    

## Milestone E: Scale and confidence

- 100000-transition replay test
    
- archive restore parity
    
- digest equality checks
    
- crash recovery tests
    

## 29. Immediate Design Corrections

The chat history already pointed to the critical corrections that should be carried into this specification:

- use `rfc8785.dumps()` for canonicalization[[github](https://github.com/trailofbits/rfc8785.py)]
    
- split identity from occurrence
    
- use explicit `timestamp_ns`
    
- make provenance transition-derived
    
- prefer stream digest over accidental insertion-order assumptions
    
- treat projection as disposable and reproducible
    

Those changes are the difference between an exploratory system and a deterministic engineering kernel.

## 30. Final Architectural Summary

K501–AIONARC is best understood as:

text

`Transition Stream   ↓ Projection Layer   ↓ StateObjects   ↓ Provenance Graph   ↓ Replay Validator`

That model is internally consistent, reconstructable, and deterministic. The journal is truth; the graph is derived; the projections are disposable; the replay validator is the integrity gate. The system’s real ontology is not “memory” or “knowledge” but **append-only reconstructability**.

If you want, I can turn this into a formal ADR-style document set, or generate the exact `src/` skeleton and file contents for the new architecture.