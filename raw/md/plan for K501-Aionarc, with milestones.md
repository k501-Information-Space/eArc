Below is a formal engineering plan for K501-Aionarc, with milestones, acceptance criteria, and subsystem interfaces. It is organized so you can hand it to an engineering team and execute incrementally without collapsing the architecture back into generic RAG.[[arxiv](https://arxiv.org/html/2605.30771v1)]

## Program Definition

**Program name:** K501-Aionarc Provenance Memory System  
**Mission:** Build a local-first, provenance-first memory substrate that separates evidence, retrieval, and trust, and exposes them to reasoning agents through stable interfaces.[[vonng](https://vonng.com/en/ai/agent-os/)]  
**Primary design rule:** No derived state may overwrite evidence; every belief must remain traceable to a proof and audit chain.[[aevum](https://aevum.build/guides/mcp-audit-trail/)]

## System Boundaries

The system has five major subsystems: Evidence Store, Reference Graph, Retrieval Engine, Governance Engine, and Agent Interface. Evidence is immutable, retrieval is multi-signal, governance adjudicates truth, and agents consume only trusted state objects rather than raw archive text. This boundary is important because it prevents the retrieval layer from becoming the de facto truth layer, which is a common failure mode in memory systems.[[arxiv](https://arxiv.org/pdf/2603.18330v1.pdf)]

## Milestone Plan

## Milestone 1: Canonical ontology freeze

Define the root ontology and object model, including Axiom, Kernel, Frame, Snapshot, Freeze, Archive, State Object, Proof, Audit, Claim, Belief, Namespace, Pointer, and Time Anchor. This milestone is about schema stability, lifecycle rules, and deterministic IDs rather than feature breadth.[[aevum](https://aevum.build/guides/mcp-audit-trail/)]

**Deliverables**

- Ontology specification.
    
- Versioned JSON schemas for all primitives.
    
- Transition matrix for allowed state changes.
    
- Stable ID and namespace rules.
    

**Acceptance criteria**

- Every object type has a unique schema version and stable identifier.
    
- Any object can be reconstructed from stored evidence and lineage metadata.
    
- Invalid state transitions are rejected by schema or policy validation.
    
- A full round-trip serialization/deserialization test passes at 100% for all core primitives.
    

## Milestone 2: Evidence and archive substrate

Implement append-only ingestion for documents, manifests, chunks, and frozen state artifacts. Evidence must be immutable, content-addressable where possible, and linked to provenance metadata from the moment of ingestion.[[arxiv](https://arxiv.org/html/2605.30771v1)]

**Deliverables**

- Append-only evidence store.
    
- Snapshot and freeze pipeline.
    
- Proof and audit record persistence.
    
- Integrity verification for archive records.
    

**Acceptance criteria**

- No evidence record can be modified in place.
    
- Every archive item has an auditable origin chain.
    
- Archive replay reconstructs the same state hash on repeated runs.
    
- Integrity checks detect corruption, missing lineage, or partial writes.
    

## Milestone 3: Reference Graph

Build the deterministic reference graph as a first-class subsystem. This graph must encode derivation, ancestry, validation, temporal anchoring, and namespace relationships so lineage queries are native rather than inferred from text.[[docs.trustgraph](https://docs.trustgraph.ai/overview/retrieval.html)]

**Deliverables**

- Graph schema with node and edge types.
    
- Lineage traversal API.
    
- Time-aware and namespace-aware query support.
    
- Provenance chain reconstruction endpoint.
    

**Acceptance criteria**

- Queries such as “derived from Snapshot S before Time Anchor T and validated by Proof P” return correct results.
    
- Graph traversal returns both direct and transitive ancestry.
    
- Every graph edge maps back to a source evidence record.
    
- Provenance chains are replayable end to end.
    

## Milestone 4: Retrieval engine

Replace similarity-only retrieval with hybrid retrieval. The ranker must combine semantic similarity, lexical match, temporal relevance, provenance depth, proof status, audit status, and belief confidence.[[arxiv](https://arxiv.org/html/2603.28444v1)]

**Deliverables**

- Vector retrieval index.
    
- Lexical/keyword retrieval index.
    
- Multi-signal ranker.
    
- Retrieval explanation payloads.
    

**Acceptance criteria**

- Retrieval returns State Objects, not only chunks.
    
- Rank explanations include the signals used in scoring.
    
- Hybrid retrieval outperforms baseline vector-only search on a labeled query set.
    
- Provenance-aware ranking improves precision for lineage queries.
    

## Milestone 5: Governance engine

Introduce claim, validation, and belief management. This layer adjudicates whether evidence can become operational knowledge and resolves contradictions, stale facts, and confidence decay.[[arxiv](https://arxiv.org/pdf/2603.18330v1.pdf)]

**Deliverables**

- Claim registry.
    
- Validation workflows.
    
- Belief scoring and supersession rules.
    
- Contradiction resolution policies.
    

**Acceptance criteria**

- Every claim must link to evidence and validation metadata.
    
- Contradictions are detected and represented, not overwritten.
    
- Belief state changes are explainable and reproducible.
    
- Governance outputs are deterministic under identical evidence and policy.
    

## Milestone 6: Agent interface

Expose the system to agents through a stable memory API and, optionally, MCP-compatible tools. Agents should query trusted state, lineage, and proof chains rather than raw archive content.[[arxiv](https://arxiv.org/html/2509.22814v1)]

**Deliverables**

- Read-only memory tool APIs.
    
- Provenance lookup tools.
    
- Audit replay endpoints.
    
- Agent-safe state object access.
    

**Acceptance criteria**

- Agents can request evidence, claims, beliefs, audits, and graph traversals through defined interfaces.
    
- Tool calls are logged with replayable provenance.
    
- No agent can mutate evidence directly.
    
- Multi-agent namespace isolation is enforced.
    

## Subsystem Interfaces

## 1) Evidence Store API

**Purpose:** Store immutable source evidence and frozen artifacts.  
**Core operations**

- `ingest_evidence(source, metadata) -> evidence_id`
    
- `freeze_state(frame_id) -> freeze_id`
    
- `store_archive(object) -> archive_id`
    
- `verify_integrity(object_id) -> status`
    

**Required guarantees**

- Append-only writes.
    
- Content hash or stable record hash.
    
- Original source metadata preserved.
    
- No overwrite semantics.
    

## 2) Reference Graph API

**Purpose:** Navigate derivation and trust relationships.  
**Core operations**

- `add_node(object_type, object_id, attributes)`
    
- `add_edge(source_id, edge_type, target_id, attributes)`
    
- `traverse(start_id, edge_filters, depth) -> subgraph`
    
- `lineage(object_id) -> ancestry_chain`
    
- `provenance(object_id) -> proof_audit_chain`
    

**Required guarantees**

- Every edge is evidence-backed.
    
- Traversal supports temporal and namespace constraints.
    
- Graph state is queryable independently of text retrieval.
    

## 3) Retrieval API

**Purpose:** Return ranked memory candidates for reasoning.  
**Core operations**

- `search(query, filters) -> ranked_results`
    
- `search_hybrid(query, lexical, semantic, temporal, provenance) -> ranked_results`
    
- `explain_rank(result_id) -> score_breakdown`
    
- `retrieve_state_object(query) -> state_objects`
    

**Required guarantees**

- Results include provenance metadata.
    
- Ranking is decomposable and explainable.
    
- Retrieval supports both semantic and deterministic filters.
    
- Search can return graph context with the result set.
    

## 4) Governance API

**Purpose:** Convert evidence into trusted operational beliefs.  
**Core operations**

- `create_claim(evidence_refs, assertion) -> claim_id`
    
- `validate_claim(claim_id, policy) -> validation_id`
    
- `update_belief(claim_id, confidence, status) -> belief_id`
    
- `resolve_conflict(claim_ids) -> resolution_id`
    

**Required guarantees**

- Claims are immutable once issued.
    
- Validation references policies and evidence.
    
- Beliefs are derived, not raw evidence.
    
- Conflict resolution is recorded and replayable.
    

## 5) Agent Memory API

**Purpose:** Allow autonomous systems to reason over trusted memory.  
**Core operations**

- `get_context(task_id, scope, trust_threshold) -> context_bundle`
    
- `lookup_proof(object_id) -> proof_chain`
    
- `inspect_audit(object_id) -> audit_chain`
    
- `query_lineage(object_id, time_window) -> graph_path`
    

**Required guarantees**

- Read-only by default.
    
- Trust thresholds are enforced.
    
- Context bundles distinguish evidence from belief.
    
- Every call produces an auditable event.
    

## Validation Strategy

Validation should be split into four classes: schema validation, integrity validation, retrieval validation, and governance validation. Schema validation ensures objects conform to ontology; integrity validation ensures records are uncorrupted; retrieval validation measures ranking and recall quality; governance validation ensures beliefs are only derived from properly supported claims. This layered validation matters because a system can be syntactically correct but epistemically wrong.[[arxiv](https://arxiv.org/html/2605.30771v1)]

## Required test suites

- Round-trip object tests.
    
- Provenance replay tests.
    
- Retrieval benchmark tests.
    
- Contradiction resolution tests.
    
- Multi-agent isolation tests.
    
- Audit chain verification tests.
    

## Metrics and Acceptance Targets

## Core system metrics

- Archive integrity: 100%.
    
- Provenance completeness: >99% of state objects with full lineage.
    
- Retrieval precision: measurable improvement over vector-only baseline.
    
- Retrieval explainability: 100% of ranked results include score decomposition.
    
- Audit replay fidelity: 100% match on deterministic replay.
    
- Belief consistency: no unsupported belief transitions in test corpus.
    

## Readiness thresholds

- **Archive-ready:** Milestones 1–2 complete.
    
- **Continuity-ready:** Milestones 1–4 complete.
    
- **Governance-ready:** Milestones 1–5 complete.
    
- **Agent-ready:** Milestones 1–6 complete.
    

## Delivery Sequence

The recommended execution order is:

1. Freeze ontology.
    
2. Build immutable evidence substrate.
    
3. Add the reference graph.
    
4. Implement hybrid retrieval.
    
5. Add governance and beliefs.
    
6. Expose agent interfaces.
    

This order is intentionally conservative because retrieval without governance will recreate standard RAG, while governance without provenance will create unverifiable logic.

## Architectural Exit Criteria

The project should be considered successful when:

- A query can traverse from result to evidence to proof to audit without ambiguity.
    
- The system can distinguish evidence, claim, and belief.
    
- Retrieval returns trusted state objects, not only chunks.
    
- Agents can operate using memory that is lineage-aware and audit-backed.
    
- The architecture remains local-first and fully reproducible under deterministic inputs.
    

## Final Definition

K501-Aionarc’s engineering objective is to become a **provenance-driven memory substrate** with explicit evidence, graph, governance, and agent interfaces. That is the right formal shape for what the system is becoming, and it is the correct basis for implementation.[[vonng](https://vonng.com/en/ai/agent-os/)]

Would you like me to turn this into a subsystem-by-subsystem spec with interface schemas and a milestone Gantt-style timeline?