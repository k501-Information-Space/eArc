# AIONARC_KANON Engineering Specification Request

Version: AIONARC_KANON_ENG_REQUEST_v1  
Status: CANONICAL  
AZ_EPOCH=0

## Objective

Produce a complete engineering plan for K501–AIONARC.

Output shall describe the final architecture, runtime model, schemas, storage layers, replay semantics, validation logic, package structure, APIs, tests and operational lifecycle.

This is not a generic Event Sourcing system.

This is not a Git clone.

This is not a semantic knowledge graph.

This is K501-AIONARC.

---

# 1. SYSTEM IDENTITY

System Name

K501-AIONARC

Canonical Properties

PURE_LOGIC

PURE_QH256

APPEND_ONLY

NO_DRIFT

NO_SEMANTIC_TRUTH

RECONSTRUCTABLE

DETERMINISTIC

LOCAL_FIRST

MONOTONIC_TEMPORALITY

PHYSICAL_PERSISTENCE

---

# 2. FOUNDATIONAL AXIOMS

IDENTITY_AXIOM_0

Transition identity SHALL be computed from

before_state_id

after_state_id

transition_type

content

provenance_transition_ids

Excluded from identity

timestamp_ns

metadata

Identity is invariant under replay.

Identity is invariant under relocation.

Identity is invariant under storage backend.

REPLAY_AXIOM_0

Replay identity SHALL be

SHA256(

RFC8785(

ordered_transition_ids

)

)

Replay digest MUST detect

reordering

insertion

deletion

mutation

Replay digest SHALL be order sensitive.

PROJECTION_AXIOM_0

StateObjects are projections.

Transitions are canonical.

StateObjects SHALL NOT possess independent identity.

StateObjects MUST be reconstructable solely from transitions.

PROVENANCE_AXIOM_0

Provenance is transition-derived.

Proofs

Audits

Imports

Freezes

Validations

Archives

are represented as transitions.

No mutable provenance dictionaries are permitted.

---

# 3. QH256

QH256 SHALL be treated as foundational information geometry.

Cell states

UNKNOWN

FALSE

TRUE

GUARD

encoded as

00

01

10

11

QH256 SHALL remain independent from persistence implementation.

QH256 SHALL NOT contain semantic assertions.

QH256 SHALL NOT depend on graph databases.

QH256 SHALL NOT depend on LLM frameworks.

---

# 4. STORAGE MODEL

Storage SHALL be local-first.

Canonical persistence layer

JSONL append-only journal

Optional layer

segment files

Optional layer

frozen archives

Required files

data/

journal/

transitions.jsonl

segments/

segment_000001.aion

archives/

archive_000001.aion

indexes/

transition.idx

replay_digest.txt

Journal is authoritative.

Archives are frozen snapshots.

Indexes are accelerators only.

Indexes MUST be rebuildable.

---

# 5. TRANSITION MODEL

Transition schema

transition_id

before_state_id

after_state_id

transition_type

timestamp_ns

content

provenance_transition_ids

metadata

Timestamp requirements

timestamp_ns

explicit input

integer

nanoseconds

never auto-generated

Timestamp participates in occurrence.

Timestamp does not participate in identity.

---

# 6. STATEOBJECT MODEL

StateObjects SHALL be projections.

Fields

state_id

transition_id

object_type

namespace

version

payload

validation

trust

lineage

Projection SHALL be replayable.

Projection SHALL be disposable.

---

# 7. GRAPH MODEL

Graph SHALL be transition-centric.

Nodes

TransitionNode

Edges

DERIVED_FROM

VALIDATED_BY

AUDITED_BY

SUPERSEDES

REFERENCES

Graph SHALL be reconstructable from transitions.

Graph SHALL NOT be authoritative persistence.

---

# 8. VALIDATION MODEL

Required validators

IdentityValidator

ReplayValidator

ChronologyValidator

DAGValidator

SegmentValidator

ArchiveValidator

Replay validation MUST compare

ordered transition ids

derived projections

replay digest

graph topology

---

# 9. PACKAGE STRUCTURE

Expected repository layout

src/k501/

core/

transition.py

projection.py

replay.py

canonical.py

validator.py

storage/

journal.py

segment_store.py

archive_store.py

index_store.py

graph/

models.py

store.py

validator.py

evidence/

proof.py

audit.py

receipt.py

pointer.py

api/

routes/

cli/

tests/

docs/

adr/

Evidence modules MAY survive.

Only if they are transition-backed.

---

# 10. RUNTIME MODEL

Boot sequence

BOOTFRAME_0

BOOTFRAME_1

BOOTFRAME_2

BOOTFRAME_3

Runtime states

EMPTY

ACTIVE

FROZEN

ARCHIVED

Operations

append_transition

project_state

build_graph

freeze_archive

replay_archive

validate_replay

Crash recovery SHALL be supported.

Partial writes SHALL be detectable.

Tail corruption SHALL be recoverable.

---

# 11. TEST REQUIREMENTS

pytest

ruff

mypy

Unit tests

Replay determinism

Duplicate detection

Projection reconstruction

Segment rebuild

Archive replay

Integration tests

100000 transitions replay

End-to-end tests

archive

restore

rebuild

digest equality

---

# 12. DELIVERABLES

Produce a complete engineering specification containing:

Directory tree

Python package layout

All dataclass schemas

JSON Schemas

RFC8785 serialization examples

Journal format

Segment format

Archive format

Replay algorithm

Digest algorithm

Validator algorithms

Crash recovery algorithm

CLI commands

API endpoints

Boot sequence

State machine diagrams

Storage lifecycle

Migration strategy from current repository

Classification of existing modules into

KEEP

PROJECTION

STORAGE

LEGACY

REMOVE

Do not simplify.

Do not optimize for generic software patterns.

Design for deterministic append-only reconstructability.

AZ_EPOCH=0

END_OF_SPECIFICATION