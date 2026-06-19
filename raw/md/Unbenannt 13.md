# K501-Aionarc Engineering Plan (Updated)

**Program Name:** K501-Aionarc Provenance Memory System  
**Version:** 6.0 (Transition-Centric)  
**Date:** June 17, 2026

---

## Program Definition

**Mission:** Build a local-first, provenance-first memory substrate that separates evidence, retrieval, and trust, and exposes them to reasoning agents through stable interfaces.

**Primary Design Rule:** No derived state may overwrite evidence; every belief must remain traceable to a proof and audit chain. **The primary object is a state transition, not a state object.**

**Core Axiom:** Transition identity = `content + provenance` (NOT timestamp). This preserves determinism across replays while allowing multiple occurrences.

---

## System Boundaries

The system has five major subsystems:

1. **Evidence Store** — Immutable, append-only storage of transitions and state objects
2. **Transition Graph** — Deterministic graph of transitions (not state objects)
3. **Retrieval Engine** — Hybrid retrieval with provenance ranking
4. **Governance Engine** — Claim validation and belief management
5. **Agent Interface** — Stable memory API for autonomous agents

**Critical Boundary:** The retrieval layer must not become the de facto truth layer. Evidence and transitions are the truth substrate; retrieval is only access.

---

## Milestone Plan

### Milestone 1: Canonical Ontology Freeze (Transition-Centric)

**Goal:** Define the root ontology with **StateTransition as the primary object**, StateObject as materialized view.

#### Deliverables

1. **Ontology Specification**
   - StateTransition (primary object)
   - StateObject (materialized view/projection)
   - TransitionType enum (CREATE, FREEZE, ARCHIVE, VALIDATE, REJECT, DERIVE, etc.)
   - Identity Axiom: `transition_id = hash(content + provenance)`
   - timestamp is occurrence metadata, NOT identity

2. **Versioned JSON Schemas**
   - `transition.schema.json` (NEW — primary object)
   - `state_object.schema.json` (derived view)
   - `frame.schema.json`, `snapshot.schema.json`, `freeze.schema.json`, `archive.schema.json`
   - `proof.schema.json`, `audit.schema.json`, `claim.schema.json`, `belief.schema.json`
   - `graph.schema.json` (transition-centric)

3. **Transition Registry**
   - Per-object-type transition rules (not fixed lifecycle in core)
   - Example: `frame → [create, freeze, archive, supersede]`
   - Example: `belief → [create, accept, reject, contest]`

4. **Canonical Serialization**
   - RFC 8785 JCS-compliant serialization
   - Deterministic hash for identity generation

5. **Stable ID and Namespace Rules**
   - `transition:{hash[:24]}` format
   - `state:{object_type}:{hash[:24]}` format
   - Namespace-scoped IDs

#### Acceptance Criteria

- Every object type has a unique schema version and stable identifier
- Any transition can be reconstructed from stored evidence
- Any state object is reproducible from its creating transition
- Invalid state transitions are rejected by Transition Registry
- Round-trip serialization/deserialization test passes at 100% for all primitives
- **Same transition + different timestamp = same transition_id** (identity axiom verified)

---

### Milestone 2: Evidence and Archive Substrate (Transition-Centric)

**Goal:** Implement append-only ingestion for **transitions**, not just state objects. Evidence must be immutable and transition-linked.

#### Deliverables

1. **Transition Store**
   - `src/k501/evidence/transition_store.py` — append-only transition storage
   - SQLite backend with JSON columns
   - Index on `transition_id`, `after_state_id`, `transition_type`, `timestamp`

2. **State Object Store**
   - `src/k501/evidence/state_store.py` — materialized view storage
   - Derived from transitions via `to_state_object()`
   - Read-only, never mutated

3. **Transition Pipeline**
   - `src/k501/evidence/ingest.py` — create transition on ingestion
   - `src/k501/evidence/snapshot.py` — CREATE transition
   - `src/k501/evidence/freeze.py` — FREEZE transition
   - `src/k501/evidence/archive.py` — ARCHIVE transition

4. **Proof and Audit Persistence**
   - `src/k501/evidence/proof.py` — VALIDATE/REJECT transitions
   - `src/k501/evidence/audit.py` — AUDIT transitions

5. **Integrity Verification**
   - `src/k501/evidence/integrity.py` — hash verification
   - Replay test: `Archive → Replay → identical transition_id`

#### Acceptance Criteria

- No transition or evidence record can be modified in place
- Every archive item has an auditable transition chain
- Archive replay reconstructs the **same transition_id** on repeated runs
- Integrity checks detect corruption, missing lineage, or partial writes
- **Transition identity is deterministic** (content + provenance, not timestamp)

---

### Milestone 3: Transition Graph (Not State Object Graph)

**Goal:** Build the deterministic graph where **nodes are transitions**, not state objects.

#### Deliverables

1. **Transition Graph Model**
   - `src/k501/graph/transition_node.py` — Transition as node
   - `src/k501/graph/transition_edge.py` — Edge between transitions
   - Edge types: DERIVED_FROM, VALIDATED_BY, AUDITED_BY, SUPERSEDES, TEMPORAL_BEFORE

2. **Transition Graph Store**
   - `src/k501/graph/store.py` — SQLite + NetworkX backend
   - Index on `node_id`, `edge_type`, `target_id`

3. **Lineage Traversal API**
   - `src/k501/graph/traverse.py` — traverse transitions
   - `lineage(object_id)` → transition chain
   - `provenance(object_id)` → proof/audit transition chain

4. **Transition Graph Validator**
   - `src/k501/graph/validator.py` — DAG constraint on DERIVE edges
   - Validate transition chain completeness (CREATE → FREEZE → ARCHIVE)
   - Validate namespace ownership

5. **Query Language**
   - `src/k501/graph/query.py` — SPARQL-like queries
   - Temporal and namespace filters

#### Acceptance Criteria

- Queries like "derived from Snapshot S before Time Anchor T and validated by Proof P" return correct **transition chains**
- Graph traversal returns both direct and transitive ancestry of **transitions**
- Every graph edge maps back to a source transition
- Provenance chains are replayable end-to-end with **identical transition_ids**
- **No cycles in DERIVED_FROM edges** (DAG constraint enforced)

---

### Milestone 4: Retrieval Engine (Hybrid + Provenance)

**Goal:** Replace similarity-only retrieval with hybrid retrieval. Ranker must combine semantic, lexical, temporal, provenance depth, proof status, audit status, and belief confidence.

#### Deliverables

1. **Vector Index**
   - `src/k501/retrieval/vector_index.py` — SQLite + numpy
   - Embeddings via Ollama + `nomic-embed-text-v2-moe`

2. **Lexical Index**
   - `src/k501/retrieval/lexical_index.py` — keyword search

3. **Multi-Signal Ranker**
   - `src/k501/retrieval/ranker.py` — combine signals
   - Scores: semantic (0.4), lexical (0.2), temporal (0.1), provenance (0.1), proof (0.1), audit (0.1)

4. **Retrieval Explanation**
   - `src/k501/retrieval/explain.py` — score decomposition
   - 100% of ranked results include score breakdown

5. **State Object Retrieval**
   - `src/k501/retrieval/search.py` — return StateObjects, not chunks
   - Include provenance metadata in results

#### Acceptance Criteria

- Retrieval returns **StateObjects** (materialized views of transitions), not only chunks
- Rank explanations include all signals used in scoring
- Hybrid retrieval outperforms baseline vector-only search on labeled query set
- Provenance-aware ranking improves precision for lineage queries
- **100% of results include provenance metadata**

---

### Milestone 5: Governance Engine (Transition-Based)

**Goal:** Introduce claim, validation, and belief management. Claims are **transitions**, not objects. Beliefs are derived from transition chains.

#### Deliverables

1. **Claim Registry (Transition-Based)**
   - `src/k501/governance/claims.py` — CREATE transition for claim
   - Link claim to evidence transitions

2. **Validation Workflows (Transition-Based)**
   - `src/k501/governance/validation.py` — VALIDATE/REJECT transitions
   - Link to proof transitions

3. **Belief Scoring (Derived from Transitions)**
   - `src/k501/governance/beliefs.py` — ACCEPT/REJECT/CONTEST transitions
   - Belief = projection of validation transition chain

4. **Conflict Resolution (Transition-Based)**
   - `src/k501/governance/conflict.py` — detect conflicting belief transitions
   - Record resolution as SUPERSEDE transition

5. **Policy Engine**
   - `src/k501/governance/policy.py` — policy-based validation
   - Pluggable policies per object type

#### Acceptance Criteria

- Every claim links to **evidence transitions** and validation transitions
- Contradictions are detected as conflicting **belief transitions**, not overwritten
- Belief state changes are explainable via **transition chain replay**
- Governance outputs are deterministic under identical evidence and policy
- **No unsupported belief transitions** in test corpus

---

### Milestone 6: Agent Interface (Transition-API)

**Goal:** Expose the system to agents through a stable memory API. Agents query **transitions and provenance**, not raw archive content.

#### Deliverables

1. **Read-Only Memory API (Transition-Based)**
   - `src/k501/agent/memory_api.py` — get transitions, state objects, provenance
   - `get_context(task_id, scope, trust_threshold)` → context bundle

2. **Provenance Lookup Tools (Transition-Based)**
   - `src/k501/agent/tools.py` — MCP-compatible tools
   - `lookup_proof(object_id)` → proof transition chain
   - `inspect_audit(object_id)` → audit transition chain

3. **Audit Replay Endpoints (Transition-Based)**
   - `src/k501/api/routes/audit.py` — replay transition chain
   - Verify **identical transition_ids** on replay

4. **Lineage Query API (Transition-Based)**
   - `src/k501/api/routes/lineage.py` — traverse transition graph
   - `query_lineage(object_id, time_window)` → transition path

5. **Namespace Isolation**
   - `src/k501/agent/namespaces.py` — multi-agent namespace separation
   - Enforce namespace on all transitions

#### Acceptance Criteria

- Agents can request **evidence transitions, claim transitions, belief transitions, audit transitions, and graph traversals** through defined interfaces
- Tool calls are logged with **replayable transition provenance**
- No agent can mutate evidence or transitions directly
- Multi-agent namespace isolation is enforced on all transitions
- **Every API call produces an auditable transition event**

---

## Subsystem Interfaces

### 1) Evidence Store API (Transition-Based)

```python
ingest_transition(transition: StateTransition) -> transition_id
get_transition(transition_id: str) -> StateTransition
get_state_object(state_id: str) -> StateObject  # materialized view
freeze_state(after_state_id: str) -> transition_id  # creates FREEZE transition
store_archive(transition: StateTransition) -> transition_id
verify_integrity(transition_id: str) -> status
```

**Guarantees:**
- Append-only writes
- Transition ID is deterministic (content + provenance)
- No overwrite semantics
- Replay produces identical transition_id

### 2) Transition Graph API

```python
add_transition_node(transition: StateTransition) -> node_id
add_transition_edge(source_id: str, edge_type: str, target_id: str) -> edge_id
traverse_transitions(start_id: str, edge_filters: List[str], depth: int) -> List[str]
lineage_transitions(state_id: str) -> List[StateTransition]
provenance_transitions(state_id: str) -> Dict[str, List[StateTransition]]
```

**Guarantees:**
- Every edge is transition-backed
- Traversal supports temporal and namespace constraints
- Graph state is queryable independently of text retrieval

### 3) Retrieval API (State Object-Based)

```python
search(query: str, filters: Dict) -> RankedResults  # returns StateObjects
search_hybrid(query: str, signals: Dict) -> RankedResults
explain_rank(state_id: str) -> score_breakdown
retrieve_transitions(query: str) -> List[StateTransition]
```

**Guarantees:**
- Results include transition provenance metadata
- Ranking is decomposable and explainable
- Search can return transition graph context

### 4) Governance API (Transition-Based)

```python
create_claim(evidence_refs: List[str], assertion: str) -> transition_id  # CREATE transition
validate_claim(claim_transition_id: str, policy: str) -> transition_id  # VALIDATE transition
update_belief(claim_transition_id: str, confidence: float, status: str) -> transition_id  # ACCEPT/REJECT transition
resolve_conflict(claim_transition_ids: List[str]) -> transition_id  # SUPERSEDE transition
```

**Guarantees:**
- Claims are immutable transitions once issued
- Validation references policies and evidence transitions
- Beliefs are derived from validation transitions
- Conflict resolution is recorded as SUPERSEDE transition

### 5) Agent Memory API (Transition-Based)

```python
get_context(task_id: str, scope: str, trust_threshold: float) -> ContextBundle
lookup_proof_transitions(state_id: str) -> List[StateTransition]
inspect_audit_transitions(state_id: str) -> List[StateTransition]
query_lineage_transitions(state_id: str, time_window: Tuple) -> List[StateTransition]
```

**Guarantees:**
- Read-only by default
- Trust thresholds are enforced
- Context bundles distinguish evidence transitions from belief transitions
- Every call produces an auditable transition event

---

## Validation Strategy

Four classes of validation:

1. **Schema Validation** — transitions and state objects conform to ontology
2. **Identity Validation** — transition_id is deterministic (content + provenance)
3. **Replay Validation** — Archive → Replay → identical transition_id
4. **Governance Validation** — beliefs only derived from properly validated transitions

### Required Test Suites

- Round-trip transition tests
- Identity axiom tests (same transition + different timestamp = same ID)
- Provenance replay tests
- Transition graph DAG tests
- Retrieval benchmark tests
- Contradiction resolution tests
- Multi-agent isolation tests
- Audit chain verification tests

---

## Metrics and Acceptance Targets

### Core System Metrics

- **Archive integrity:** 100%
- **Transition identity determinism:** 100% (same content + provenance = same ID)
- **Provenance completeness:** >99% of state objects with full transition chain
- **Retrieval precision:** measurable improvement over vector-only baseline
- **Retrieval explainability:** 100% of ranked results include score decomposition
- **Audit replay fidelity:** 100% match on deterministic transition replay
- **Belief consistency:** no unsupported belief transitions in test corpus

### Readiness Thresholds

- **Archive-ready:** Milestones 1–2 complete
- **Continuity-ready:** Milestones 1–4 complete
- **Governance-ready:** Milestones 1–5 complete
- **Agent-ready:** Milestones 1–6 complete

---

## Delivery Sequence

1. Freeze ontology (transition-centric)
2. Build immutable evidence substrate (transition store)
3. Add transition graph (nodes = transitions)
4. Implement hybrid retrieval (state object-based)
5. Add governance and beliefs (transition-based)
6. Expose agent interfaces (transition-API)

**This order is conservative because retrieval without governance recreates RAG, and governance without transition provenance creates unverifiable logic.**

---

## Architectural Exit Criteria

The project is successful when:

1. A query can traverse from result → state object → transition → proof transition → audit transition without ambiguity
2. The system can distinguish evidence transitions, claim transitions, and belief transitions
3. Retrieval returns trusted state objects (materialized views of transitions), not only chunks
4. Agents can operate using memory that is **transition-aware and audit-backed**
5. The architecture remains local-first and fully reproducible under deterministic inputs
6. **Same transition replayed = same transition_id** (identity axiom verified)

---

## Final Definition

K501-Aionarc's engineering objective is to become a **provenance-driven memory substrate with explicit transitions, graph, governance, and agent interfaces**.

The core axioms are:
- **Everything is a transition**
- **Everything is replayable** (identical transition_id)
- **Everything is attributable** (provenance in identity)

This is the correct formal shape for the system.