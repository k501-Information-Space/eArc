Absolutely — this is the correct strategic focus. Below is the **formal specification** of the three foundational components that determine whether K501-Aionarc becomes an executable system:

1. **StateObject Schema** (universal memory primitive)
    
2. **Transition Matrix** (lifecycle validation rules)
    
3. **Provenance Graph Schema** (lineage and ancestry relationships)
    

These specifications are implementation-ready and map directly to the JSON schemas already defined.

---

## 1. Formal StateObject Schema Specification

## Purpose

The StateObject is the **universal memory primitive** for K501-Aionarc. Every entity in the system (Frame, Snapshot, Freeze, Archive, Proof, Audit, Claim, Belief) must be representable as a StateObject.

## Core Structure

json

`{   "state_id": "deterministic_id",  "axiom_id": "root_axiom_id",  "namespace": "logical_namespace",  "version": "schema_version",  "object_type": "primitive_type",  "origin": {    "frame_id": "string",    "snapshot_id": "string",    "freeze_id": "string",    "archive_id": "string"  },  "lineage": {    "derived_from": ["id1", "id2"],    "ancestor_chain": ["id1", "id2", "id3"],    "transitive_root": "id"  },  "validation": {    "proof_id": "string",    "audit_id": "string",    "receipt_id": "string",    "status": "pending|validated|rejected|superseded"  },  "trust": {    "belief_status": "unknown|candidate|accepted|contested|rejected",    "confidence": 0.0,    "support_score": 0.0  },  "time": {    "created_at": "ISO8601",    "updated_at": "ISO8601",    "time_anchor": "string",    "valid_from": "ISO8601",    "valid_to": "ISO8601"  },  "retrieval": {    "chunk_ids": ["id1", "id2"],    "embedding_ids": ["id1", "id2"],    "graph_refs": ["id1", "id2"]  },  "provenance": {    "source": "string",    "writer": "string",    "tool_chain": ["tool1", "tool2"],    "signature": "string"  },  "payload": {    "content_hash": "sha256_hash",    "summary": "string",    "metadata": {}  },  "metadata": {} }`

## Required Fields (Invariant)

|Field|Type|Constraint|
|---|---|---|
|`state_id`|string|Deterministic, unique, start with type prefix|
|`axiom_id`|string|Must reference root axiom|
|`namespace`|string|Must be non-empty, slash-separated hierarchy|
|`version`|string|Must match `X.Y.Z` pattern|
|`object_type`|enum|Must be one of 16 primitive types|

## Object Type Enum

python

`ObjectType = {     "axiom", "kernel", "frame", "snapshot", "freeze", "archive",    "chunk", "embedding", "proof", "audit", "receipt",    "claim", "belief", "namespace", "pointer", "time_anchor" }`

## Validation Status Enum

python

`ValidationStatus = {     "pending",      # awaiting validation    "validated",    # proof and audit passed    "rejected",     # proof or audit failed    "superseded"    # replaced by newer version }`

## Belief Status Enum

python

`BeliefStatus = {     "unknown",      # no belief assigned    "candidate",    # proposed but not validated    "accepted",     # validated and trusted    "contested",    # conflicting beliefs exist    "rejected"      # invalidated }`

---

## 2. Formal Transition Matrix Specification

## Purpose

The transition matrix defines **allowed state transitions** for each object type. It prevents invalid lifecycle states and ensures deterministic evolution.

## State Enum

python

`State = {     "ACTIVE",       # mutable, runtime state    "FROZEN",       # immutable, sealed state    "ARCHIVED",     # append-only, historical state    "VALIDATED",    # proof and audit passed    "REJECTED",     # proof or audit failed    "CANDIDATE",    # proposed belief    "ACCEPTED",     # trusted belief    "CONTESTED",    # conflicting beliefs    "SUPERSEDED"    # replaced by newer version }`

## Transition Matrix (Allowed Transitions)

python

`TRANSITION_MATRIX = {     # Runtime objects    "frame": {        "ACTIVE → FROZEN": True,        "FROZEN → ARCHIVED": True,        "ACTIVE → ARCHIVED": False,  # must freeze first        "ARCHIVED → ACTIVE": False,  # immutable        "ARCHIVED → FROZEN": False,  # immutable    },         "snapshot": {        "ACTIVE → FROZEN": True,        "FROZEN → ACTIVE": False,  # immutable        "FROZEN → ARCHIVED": False,  # must go through Freeze    },         "freeze": {        "FROZEN → ARCHIVED": True,        "ARCHIVED → FROZEN": False,  # immutable    },         "archive": {        "ARCHIVED → ARCHIVED": True,  # append-only, can be extended        "ARCHIVED → FROZEN": False,  # immutable        "ARCHIVED → ACTIVE": False,  # immutable    },         # Validation objects    "proof": {        "PENDING → VALIDATED": True,        "PENDING → REJECTED": True,        "VALIDATED → REJECTED": False,  # immutable once validated        "REJECTED → VALIDATED": False,  # immutable once rejected        "VALIDATED → SUPERSEDED": True,  # replaced by newer proof    },         "audit": {        "PENDING → VALIDATED": True,        "PENDING → REJECTED": True,        "VALIDATED → REJECTED": False,  # immutable        "REJECTED → VALIDATED": False,  # immutable    },         # Governance objects    "claim": {        "ACTIVE → VALIDATED": True,        "ACTIVE → REJECTED": True,        "VALIDATED → REJECTED": False,  # must supersede        "VALIDATED → SUPERSEDED": True,        "REJECTED → VALIDATED": False,    },         "belief": {        "CANDIDATE → ACCEPTED": True,        "CANDIDATE → REJECTED": True,        "ACCEPTED → CONTESTED": True,  # conflict discovered        "ACCEPTED → REJECTED": True,   # invalidated        "CONTESTED → ACCEPTED": True,   # conflict resolved        "CONTESTED → REJECTED": True,        "REJECTED → ACCEPTED": False,  # must be re-claimed    }, }`

## Validation Function

python

`def validate_transition(     object_type: str,    from_state: State,    to_state: State, ) -> bool:     """    Validate if a state transition is allowed.         Returns True if valid, False if invalid.    """    allowed = TRANSITION_MATRIX.get(object_type, {})    transition_key = f"{from_state} → {to_state}"    return allowed.get(transition_key, False)`

## Allowed Transitions Lookup

python

`def get_allowed_transitions(object_type: str) -> List[State]:     """    Get all allowed states for an object type.         Returns list of states that object can transition to.    """    return list(TRANSITION_MATRIX.get(object_type, {}).keys())`

---

## 3. Formal Provenance Graph Schema Specification

## Purpose

The provenance graph is a **deterministic reference graph** that encodes derivation, ancestry, validation, temporal anchoring, and namespace relationships. It makes lineage queries **native** rather than inferred from text.

## Core Structure

json

`{   "root_node_id": "string",  "nodes": [    {      "node_id": "string",      "node_type": "primitive_type",      "state_ref": "state_object_id",      "attributes": {        "created_at": "ISO8601",        "namespace": "string",        "confidence": 0.0      }    }  ],  "edges": [    {      "source_id": "string",      "edge_type": "relationship_type",      "target_id": "string",      "attributes": {        "created_at": "ISO8601",        "validated_by": "proof_id",        "time_anchor": "string"      }    }  ] }`

## Node Type Enum

python

`NodeType = {     "axiom", "kernel", "frame", "snapshot", "freeze", "archive",    "proof", "audit", "claim", "belief", "namespace", "pointer", "time_anchor" }`

## Edge Type Enum

python

`EdgeType = {     # Derivation relationships    "derived_from",    "ancestor",    "transitive_root",         # Validation relationships    "validated_by",    "audited_by",    "rejected_by",         # Ownership relationships    "belongs_to",    "owned_by",         # Reference relationships    "references",    "referenced_by",         # Temporal relationships    "temporal_before",    "temporal_after",    "concurrent_with",         # Supersession relationships    "supersedes",    "superseded_by" }`

## Graph Query Patterns

## Pattern 1: Lineage Traversal

python

`def lineage(object_id: str) -> List[str]:     """    Get all ancestors of an object.         Returns transitive ancestry chain.    """    return graph.traverse(        start=object_id,        edge_types=["derived_from", "ancestor"],        direction="backward"    )`

## Pattern 2: Provenance Chain

python

`def provenance(object_id: str) -> Dict[str, List[str]]:     """    Get proof and audit chain for an object.         Returns dict with proof_ids and audit_ids.    """    proofs = graph.traverse(        start=object_id,        edge_types=["validated_by"],        direction="backward"    )    audits = graph.traverse(        start=object_id,        edge_types=["audited_by"],        direction="backward"    )    return {"proofs": proofs, "audits": audits}`

## Pattern 3: Temporal Filter

python

`def before_time_anchor(object_id: str, time_anchor: str) -> List[str]:     """    Get all objects before a time anchor.         Returns objects with temporal_before relationship.    """    return graph.traverse(        start=object_id,        edge_types=["temporal_before"],        direction="backward",        time_filter=time_anchor    )`

## Pattern 4: Namespace Filter

python

`def in_namespace(object_id: str, namespace: str) -> List[str]:     """    Get all objects in a namespace.         Returns objects with belongs_to relationship.    """    return graph.traverse(        start=object_id,        edge_types=["belongs_to"],        direction="backward",        namespace_filter=namespace    )`

## Query Language (SPARQL-like)

python

`query = {     "start_nodes": ["frame:123"],    "edge_filters": ["derived_from", "validated_by"],    "depth": 5,    "time_anchor": "2026-06-01T00:00:00Z",    "namespace": "research" } result = graph.query(query)`

## Graph Traversal API

python

`class ProvenanceGraph:     def add_node(self, node_id: str, node_type: NodeType, attributes: Dict) -> bool:        """Add a node to the graph."""         def add_edge(self, source_id: str, edge_type: EdgeType, target_id: str, attributes: Dict) -> bool:        """Add an edge to the graph."""         def traverse(        self,        start: str,        edge_types: List[EdgeType],        direction: str = "backward",        depth: int = 10,        time_filter: Optional[str] = None,        namespace_filter: Optional[str] = None,    ) -> List[str]:        """Traverse the graph with filters."""         def lineage(self, object_id: str) -> List[str]:        """Get lineage chain for an object."""         def provenance(self, object_id: str) -> Dict[str, List[str]]:        """Get proof and audit chain for an object."""`

---

## Integration with Implementation

These formal specifications map directly to:

1. **`src/k501/core/state_object.py`** — implements StateObject schema
    
2. **`src/k501/core/lifecycle.py`** — implements transition matrix
    
3. **`src/k501/graph/models.py`** — implements graph node/edge types
    
4. **`src/k501/graph/traverse.py`** — implements traversal API
    
5. **`src/k501/graph/query.py`** — implements query language
    

---

## Next Step

These specifications are now **ready to implement**. The next action is:

1. **Verify** that existing code in `src/k501/core/` matches these specs
    
2. **Update** any mismatches
    
3. **Implement** `src/k501/graph/models.py` and `src/k501/graph/traverse.py` to match the graph schema
    

If you want, I can generate the **implementation code** for the graph subsystem next.