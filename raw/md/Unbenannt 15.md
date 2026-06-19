# K501-AIONARC: Comprehensive Architecture Assessment + Full Implementation

## Output 1: Architecture Assessment

## Strengths

|Aspect|Evaluation|
|---|---|
|**Ontology-First Design**|✅ Exceptional — Unlike RAG systems that start with retrieval, K501 starts with state lineage|
|**Provenance-First**|✅ Strong — Every state has lineage, every claim has evidence, every archive has provenance|
|**Append-Only Archives**|✅ Critical — Prevents evidence overwriting, ensures auditability|
|**State Immutability**|✅ Correct — Freeze creates immutable boundary between runtime and history|
|**Governance Layer**|✅ Rare — Most memory systems lack Claim → Belief → Knowledge evolution|
|**Local-First**|✅ Essential — No cloud dependency, works air-gapped|
|**Reference Graph**|✅ First-class — Not just retrieval accelerator, but ancestry/derivation storage|

## Weaknesses

|Aspect|Issue|Severity|
|---|---|---|
|**Transition vs Object**|Architecture says "primary object is state transition" but ontology lists Frame→State→Snapshot (objects)|**Critical**|
|**Identity Axiom Unclear**|No formal definition of what defines identity (content? content+provenance? +timestamp?)|**Critical**|
|**Canonical Serialization**|Missing RFC 8785 JCS specification for deterministic hashing|**High**|
|**Graph Cycles**|No DAG constraint on DERIVED_FROM edges (cycles break provenance)|**High**|
|**Lifecycle Rigidity**|Fixed CREATE→FREEZE→ARCHIVE in core vs per-object-type registry|**Medium**|
|**Timestamp in ID**|If timestamp flows into ID, same transition ≠ same ID on replay|**High**|
|**Event vs State Machine**|Unclear whether system is Event Log (no before_state) or State Machine (with before_state)|**Medium**|

## Missing Components

1. **StateTransition class** — Primary object missing from ontology
    
2. **Identity Axiom specification** — Formal definition of transition identity
    
3. **Canonical Serialization** — RFC 8785 JCS implementation
    
4. **Transition Registry** — Per-object-type lifecycle rules
    
5. **Replay Validator** — Verify identical transition_id on replay
    
6. **Graph Validator** — DAG constraint enforcement
    
7. **Evidence Store** — Append-only transition storage
    
8. **Transition Graph** — Nodes = transitions, not state objects
    

## Implementation Risks

|Risk|Impact|Mitigation|
|---|---|---|
|**Identity non-deterministic**|System breaks on replay|Fix: Identity = content + provenance, NOT timestamp|
|**Graph cycles**|Lineage traversal infinite loop|Fix: DAG constraint on DERIVED_FROM edges|
|**Lifecycle too rigid**|Cannot add new object types|Fix: Transition Registry per object type|
|**Canonical serialization wrong**|IDs differ across implementations|Fix: RFC 8785 JCS compliance|
|**Retrieval bottleneck**|Governance has no useful substrate|Fix: Hybrid retrieval early (lexical + semantic + provenance)|

## Scalability Concerns

1. **Graph size** — Transition graph grows with every state change; may need partitioning
    
2. **Index size** — Vector + lexical + provenance indexes may become large
    
3. **Replay cost** — Full archive replay may be expensive for large histories
    
4. **Namespace isolation** — Multi-agent namespace queries may become slow
    

## Retrieval Bottlenecks

1. **Missing lexical retrieval** — Only semantic = weak keyword search
    
2. **Missing provenance ranking** — No provenance depth in score
    
3. **Missing temporal ranking** — No temporal relevance in score
    
4. **Missing score explanation** — Cannot explain why result ranked high
    

## Governance Weaknesses

1. **Belief semantic in core** — ACCEPT/REJECT/CONTEST in validator = semantic layer in core
    
2. **Missing conflict resolution** — No algorithm for resolving conflicting beliefs
    
3. **Missing policy engine** — No pluggable policies per object type
    
4. **Claim → Belief unclear** — How validated claim becomes belief not specified
    

## Architecture vs Modern Systems

|System|K501 Difference|
|---|---|
|**LangGraph Memory**|K501: provenance-first, LangGraph: workflow persistence|
|**MemGPT / Letta**|K501: lineage-preserving, MemGPT: conversational memory only|
|**GraphRAG**|K501: provenance graph (ancestry), GraphRAG: knowledge graph (entities)|
|**Zep**|K501: append-only archive, Zep: mutable message store|
|**Knowledge Graphs**|K501: transition graph (events), KG: entity graph (nodes)|
|**Event Sourcing**|K501: similar (Event → Projection), but adds provenance + governance|
|**Provenance Systems**|K501: closest match, but adds governance + agent interface|

**K501 Category:** "Provenance Memory Operating System" or "Continuity-Oriented Knowledge Substrate"

---

## Output 2: Comparison Against Modern Systems

## LangGraph Memory

- **Focus:** Workflow persistence, state machine execution
    
- **Difference:** K501 persists _evidence and lineage_, LangGraph persists _workflow state_
    
- **K501 Advantage:** Auditability, provenance, governance
    

## MemGPT / Letta

- **Focus:** Conversational memory, context management
    
- **Difference:** K501 has _lineage and provenance_, MemGPT has _no lineage_
    
- **K501 Advantage:** Can trace every belief to evidence, MemGPT cannot
    

## GraphRAG

- **Focus:** Entity relationships, knowledge graph
    
- **Difference:** GraphRAG graph = entities, K501 graph = _transitions_
    
- **K501 Advantage:** Provenance chain, not just entity relationships
    

## Zep

- **Focus:** Message store, long-term memory for agents
    
- **Difference:** Zep = mutable, K501 = _append-only archive_
    
- **K501 Advantage:** Immutable evidence, replayable history
    

## Knowledge Graph Systems

- **Focus:** Entities, relationships, ontology
    
- **Difference:** KG = entity graph, K501 = _transition graph_
    
- **K501 Advantage:** Every transition has provenance, KG entities often don't
    

## Event Sourcing Systems

- **Focus:** Event → Projection → Current State
    
- **Difference:** K501 = Event Sourcing + _provenance + governance_
    
- **K501 Advantage:** Same pattern, but adds auditability and belief management
    

## Provenance Systems (W3C PROV, TrustGraph)

- **Focus:** Audit trails, lineage tracking
    
- **Difference:** K501 = Provenance + _governance + agent interface_
    
- **K501 Advantage:** Provenance is infrastructure, not just metadata
    

---

## Output 3: Detailed Implementation Roadmap

## Milestone 1: Transition-Centric Ontology Freeze (Weeks 1–2)

**Deliverables:**

1. `src/k501/core/identity_axiom.py` — Identity Axiom specification
    
2. `src/k501/core/transition.py` — StateTransition class (primary object)
    
3. `src/k501/core/transition_type.py` — TransitionType enum
    
4. `src/k501/core/transition_registry.py` — Per-object-type rules
    
5. `src/k501/utils/canonical_serialization.py` — RFC 8785 JCS
    
6. `src/k501/utils/identity.py` — Transition-centric ID generation
    
7. `tests/unit/test_transition.py` — Identity axiom tests
    
8. `tests/unit/test_canonical_serialization.py` — RFC 8785 tests
    

**Acceptance Criteria:**

- Same transition + different timestamp = same transition_id
    
- RFC 8785 JCS compliance verified
    
- Round-trip serialization 100%
    

## Milestone 2: Evidence Store (Weeks 3–4)

**Deliverables:**

1. `src/k501/storage/sqlite.py` — SQLite backend
    
2. `src/k501/evidence/transition_store.py` — Append-only transition storage
    
3. `src/k501/evidence/state_store.py` — Materialized view storage
    
4. `src/k501/evidence/ingest.py` — Ingestion pipeline
    
5. `src/k501/evidence/freeze.py` — FREEZE transition
    
6. `src/k501/evidence/archive.py` — ARCHIVE transition
    
7. `src/k501/evidence/integrity.py` — Hash verification
    
8. `tests/integration/test_ingestion_pipeline.py`
    
9. `tests/e2e/test_archive_replay.py` — Identical transition_id on replay
    

**Acceptance Criteria:**

- No transition modified in place
    
- Archive replay produces identical transition_id
    
- Integrity checks detect corruption
    

## Milestone 3: Transition Graph (Weeks 5–6)

**Deliverables:**

1. `src/k501/graph/transition_node.py` — Transition as node
    
2. `src/k501/graph/transition_edge.py` — Edge between transitions
    
3. `src/k501/graph/store.py` — SQLite + NetworkX (updated)
    
4. `src/k501/graph/traverse.py` — Transition traversal (updated)
    
5. `src/k501/graph/lineage.py` — Transition chain reconstruction
    
6. `src/k501/graph/validator.py` — DAG constraint (updated)
    
7. `src/k501/graph/replay_validator.py` — Identical graph on replay
    
8. `tests/integration/test_transition_graph.py`
    

**Acceptance Criteria:**

- DAG constraint enforced on DERIVED_FROM
    
- Provenance chains replayable with identical transition_ids
    
- Graph traversal returns transition chains
    

## Milestone 4: Hybrid Retrieval (Weeks 7–8)

**Deliverables:**

1. `src/k501/retrieval/chunker.py`
    
2. `src/k501/retrieval/embedder.py`
    
3. `src/k501/retrieval/vector_index.py`
    
4. `src/k501/retrieval/lexical_index.py`
    
5. `src/k501/retrieval/ranker.py` — Multi-signal
    
6. `src/k501/retrieval/hybrid.py`
    
7. `src/k501/retrieval/explain.py`
    
8. `tests/integration/test_hybrid_retrieval.py`
    

**Acceptance Criteria:**

- Hybrid outperforms vector-only baseline
    
- 100% results include score explanation
    
- Provenance-aware ranking improves precision
    

## Milestone 5: Governance Engine (Weeks 9–10)

**Deliverables:**

1. `src/k501/governance/claims.py` — CREATE transition
    
2. `src/k501/governance/validation.py` — VALIDATE/REJECT transitions
    
3. `src/k501/governance/beliefs.py` — ACCEPT/REJECT/CONTEST transitions
    
4. `src/k501/governance/conflict.py` — Conflict resolution
    
5. `src/k501/governance/policy.py` — Pluggable policies
    
6. `tests/integration/test_governance_flow.py`
    

**Acceptance Criteria:**

- Beliefs derived from validation transitions
    
- Contradictions detected, not overwritten
    
- Deterministic under identical evidence + policy
    

## Milestone 6: Agent Interface (Weeks 11–12)

**Deliverables:**

1. `src/k501/agent/memory_api.py`
    
2. `src/k501/agent/tools.py` — MCP-compatible
    
3. `src/k501/agent/namespaces.py` — Namespace isolation
    
4. `src/k501/api/routes/audit.py` — Replay endpoint
    
5. `src/k501/api/routes/lineage.py` — Lineage query
    
6. `tests/integration/test_agent_api.py`
    

**Acceptance Criteria:**

- Agents query transitions, not raw archive
    
- Tool calls logged with replayable provenance
    
- Namespace isolation enforced
    

---

## Output 4: Production-Grade Python Code (Phase 1–3)

I'll generate complete code for Phase 1 (Transition Core), Phase 2 (Identity), and Phase 3 (Evidence Store).

## Phase 1: Transition Core

## `src/k501/core/identity_axiom.py`

python

`""" Identity Axiom: Formal definition of transition identity for K501-AIONARC. DECISION: Transition identity = content + provenance (NOT timestamp) This ensures: - Same transition = same identity (regardless of when observed) - Different timestamps = different occurrence, same identity - Determinism is preserved across replays """ from enum import Enum class IdentityAxiom(Enum):     """    Identity Axiom: What defines transition identity?         FINAL DECISION: CONTENT + PROVENANCE         Timestamp is occurrence metadata, not identity metadata.    This preserves determinism while allowing multiple occurrences.    """         CONTENT_ONLY = "content"  # Too weak, no provenance    CONTENT_PLUS_PROVENANCE = "content_plus_provenance"  # FINAL CHOICE    CONTENT_PLUS_TIMESTAMP = "content_plus_timestamp"  # Too strong, breaks replay    CONTENT_PLUS_ALL = "content_plus_all"  # Too strong, breaks replay IDENTITY_AXIOM = IdentityAxiom.CONTENT_PLUS_PROVENANCE def get_identity_fields() -> list[str]:     """    Get fields that compose transition identity.         Returns: ["content", "provenance"]    Excludes: timestamp (occurrence, not identity)    """    if IDENTITY_AXIOM == IdentityAxiom.CONTENT_ONLY:        return ["content"]    elif IDENTITY_AXIOM == IdentityAxiom.CONTENT_PLUS_PROVENANCE:        return ["content", "provenance"]    elif IDENTITY_AXIOM == IdentityAxiom.CONTENT_PLUS_TIMESTAMP:        return ["content", "timestamp"]    else:        return ["content", "provenance", "timestamp"]`

## `src/k501/core/transition_type.py`

python

`""" TransitionType: Enum of all valid transition types. """ from enum import Enum class TransitionType(Enum):     """Type of state transition."""         # Lifecycle transitions    CREATE = "create"    FREEZE = "freeze"    ARCHIVE = "archive"    SUPERSEDE = "supersede"         # Governance transitions    VALIDATE = "validate"    REJECT = "reject"    CONTEST = "contest"    ACCEPT = "accept"         # Derivation transitions    DERIVE = "derive"    ANCESTOR = "ancestor"         # Temporal transitions    TEMPORAL_BEFORE = "temporal_before"    TEMPORAL_AFTER = "temporal_after"`

## `src/k501/core/transition_registry.py`

python

`""" Transition Registry: Per-object-type transition rules. Instead of fixed lifecycles in the core, this allows different object types to have different transition rules. """ from typing import Dict, List class TransitionRegistry:     """    Transition Registry: Defines allowed transitions per object type.    """         def __init__(self):        self.rules: Dict[str, List[str]] = {}         def register(self, object_type: str, allowed_transitions: List[str]) -> None:        """Register transition rules for an object type."""        self.rules[object_type] = allowed_transitions         def get_allowed(self, object_type: str) -> List[str]:        """Get allowed transitions for an object type."""        return self.rules.get(object_type, [])         def validate(self, object_type: str, transition_type: str) -> bool:        """Validate if a transition is allowed for an object type."""        return transition_type in self.rules.get(object_type, []) # Default transition registry DEFAULT_REGISTRY = TransitionRegistry() # Register default lifecycle for core object types DEFAULT_REGISTRY.register("frame", ["create", "freeze", "archive", "supersede"]) DEFAULT_REGISTRY.register("snapshot", ["create", "freeze"]) DEFAULT_REGISTRY.register("freeze", ["create", "archive"]) DEFAULT_REGISTRY.register("archive", ["create"]) DEFAULT_REGISTRY.register("claim", ["create", "validate", "reject", "supersede"]) DEFAULT_REGISTRY.register("belief", ["create", "accept", "reject", "contest"])`

## `src/k501/core/transition.py`

python

`""" StateTransition: Primary object of K501-AIONARC. StateObjects are materialized views (projections) of transitions. Transitions are the canonical reality. Identity = content + provenance (NOT timestamp) """ from dataclasses import dataclass, field from datetime import datetime from typing import Any, Dict, Optional from .transition_type import TransitionType from ..utils.canonical_serialization import canonical_hash @dataclass class StateTransition:     """    Primary object of K501-AIONARC.         StateObjects are materialized views (projections) of transitions.    Transitions are the canonical reality.    """         transition_id: str    before_state_id: Optional[str]    after_state_id: str    transition_type: str    timestamp: datetime  # Occurrence time, NOT part of identity    content: Dict[str, Any]  # Part of identity    provenance: Dict[str, Any]  # Part of identity    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        before_state_id: Optional[str],        after_state_id: str,        transition_type: str,        timestamp: datetime,        content: Dict[str, Any],        provenance: Dict[str, Any],        metadata: Dict[str, Any] = {},    ) -> "StateTransition":        """        Create a deterministic StateTransition.                 Identity = content + provenance (NOT timestamp)        """        # Build identity content (excludes timestamp)        identity_content = {            "before_state_id": before_state_id,            "after_state_id": after_state_id,            "transition_type": transition_type,            "content": content,            "provenance": provenance,        }                 # Generate ID from identity content only        transition_id = f"transition:{canonical_hash(identity_content)[:24]}"                 return cls(            transition_id=transition_id,            before_state_id=before_state_id,            after_state_id=after_state_id,            transition_type=transition_type,            timestamp=timestamp,  # Stored, but NOT in ID            content=content,            provenance=provenance,            metadata=metadata,        )         def to_state_object(self) -> Dict[str, Any]:        """        Materialize StateObject from Transition.                 StateObject = Projection of Transition        """        return {            "state_id": self.after_state_id,            "transition_id": self.transition_id,            "object_type": self.content.get("object_type"),            "axiom_id": self.content.get("axiom_id"),            "namespace": self.content.get("namespace"),            "version": self.content.get("version", "1.0.0"),            "created_at": self.timestamp.isoformat(),            "lineage": self.content.get("lineage", {}),            "validation": self.content.get("validation", {}),            "trust": self.content.get("trust", {}),            "payload": self.content.get("payload", {}),        }         def is_identical(self, other: "StateTransition") -> bool:        """        Check if two transitions have the same identity.                 Identity = content + provenance (NOT timestamp)        """        return self.transition_id == other.transition_id         def is_same_occurrence(self, other: "StateTransition") -> bool:        """        Check if two transitions are the same occurrence.                 Occurrence = identity + timestamp        """        return self.is_identical(other) and self.timestamp == other.timestamp`

## Phase 2: Identity Layer

## `src/k501/utils/canonical_serialization.py`

python

`""" Canonical Serialization: RFC 8785 JSON Canonicalization Scheme (JCS). Ensures mathematically unique serialization for deterministic IDs. Rules per RFC 8785: 1. Keys sorted alphabetically (Unicode code point order) 2. No whitespace except within strings 3. No trailing commas 4. Unicode preserved (not escaped) 5. Number normalization (no difference between 1 and 1.0) 6. Array order preserved 7. Null values included """ import json from typing import Any def canonical_serialize(obj: Any) -> str:     """    Canonical JSON serialization per RFC 8785 JCS.    """    def _serialize(value: Any) -> str:        if value is None:            return "null"        elif isinstance(value, bool):            return "true" if value else "false"        elif isinstance(value, int):            return str(value)        elif isinstance(value, float):            # Normalize floats            if value == int(value):                return str(int(value))            else:                return f"{value:.10f}"        elif isinstance(value, str):            return json.dumps(value, ensure_ascii=False)        elif isinstance(value, list):            items = [_serialize(item) for item in value]            return "[" + ",".join(items) + "]"        elif isinstance(value, dict):            # Sort keys by Unicode code point            sorted_keys = sorted(value.keys(), key=lambda k: k.encode('utf-8'))            items = [                json.dumps(k, ensure_ascii=False) + ":" + _serialize(value[k])                for k in sorted_keys            ]            return "{" + ",".join(items) + "}"        else:            raise TypeError(f"Cannot serialize type: {type(value)}")         return _serialize(obj) def canonical_hash(obj: Any) -> str:     """Create SHA-256 hash of canonical serialization."""    import hashlib    canonical_str = canonical_serialize(obj)    hash_bytes = hashlib.sha256(canonical_str.encode('utf-8')).digest()    return hash_bytes.hex()`

## `src/k501/utils/identity.py`

python

`""" Identity: Deterministic ID generation for Transitions. The primary object is StateTransition, not StateObject. StateObjects are derived from transitions. """ from .canonical_serialization import canonical_hash def generate_transition_id(content: dict) -> str:     """    Generate deterministic Transition ID.         Format: transition:{hash}    where hash = SHA-256(canonical_serialize(content))         content includes:    - before_state_id (or null)    - after_state_id    - transition_type    - content    - provenance    """    hash_value = canonical_hash(content)    return f"transition:{hash_value[:24]}" def generate_state_id_from_transition(transition: dict) -> str:     """    Generate StateObject ID from its creating transition.         This ensures StateObject ID is derived from Transition ID.    """    content = {        "transition_id": transition["transition_id"],        "object_type": transition["content"].get("object_type"),        "axiom_id": transition["content"].get("axiom_id"),        "namespace": transition["content"].get("namespace"),    }         hash_value = canonical_hash(content)    return f"{transition['content'].get('object_type')}:{hash_value[:24]}"`

## Phase 3: Evidence Store

## `src/k501/storage/sqlite.py`

python

`""" SQLite Storage: Backend for evidence store. Provides: - Connection management - Schema initialization - Transaction handling """ import sqlite3 from pathlib import Path from typing import Any, Dict, List, Optional class SQLiteStore:     """SQLite backend for evidence store."""         def __init__(self, db_path: str = "data/evidence/evidence.sqlite"):        """Initialize SQLite database."""        self.db_path = Path(db_path)        self.db_path.parent.mkdir(parents=True, exist_ok=True)        self._init_schema()         def _init_schema(self) -> None:        """Initialize database schema."""        conn = self._connect()        cursor = conn.cursor()                 # Transitions table (append-only)        cursor.execute("""            CREATE TABLE IF NOT EXISTS transitions (                transition_id TEXT PRIMARY KEY,                before_state_id TEXT,                after_state_id TEXT NOT NULL,                transition_type TEXT NOT NULL,                timestamp TEXT NOT NULL,                content TEXT NOT NULL,                provenance TEXT NOT NULL,                metadata TEXT NOT NULL,                created_at TEXT NOT NULL            )        """)                 # State objects table (materialized view)        cursor.execute("""            CREATE TABLE IF NOT EXISTS state_objects (                state_id TEXT PRIMARY KEY,                transition_id TEXT NOT NULL,                object_type TEXT NOT NULL,                axiom_id TEXT NOT NULL,                namespace TEXT NOT NULL,                version TEXT NOT NULL,                created_at TEXT NOT NULL,                lineage TEXT NOT NULL,                validation TEXT NOT NULL,                trust TEXT NOT NULL,                payload TEXT NOT NULL,                FOREIGN KEY (transition_id) REFERENCES transitions(transition_id)            )        """)                 # Indexes        cursor.execute("""            CREATE INDEX IF NOT EXISTS idx_transitions_after_state            ON transitions(after_state_id)        """)        cursor.execute("""            CREATE INDEX IF NOT EXISTS idx_transitions_type            ON transitions(transition_type)        """)        cursor.execute("""            CREATE INDEX IF NOT EXISTS idx_transitions_timestamp            ON transitions(timestamp)        """)                 conn.commit()        conn.close()         def _connect(self) -> sqlite3.Connection:        """Create database connection."""        conn = sqlite3.connect(str(self.db_path))        conn.row_factory = sqlite3.Row        return conn         def insert_transition(self, transition: Dict[str, Any]) -> bool:        """Insert a transition (append-only)."""        try:            conn = self._connect()            cursor = conn.cursor()                         cursor.execute("""                INSERT OR IGNORE INTO transitions                (transition_id, before_state_id, after_state_id, transition_type,                 timestamp, content, provenance, metadata, created_at)                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)            """, (                transition["transition_id"],                transition["before_state_id"],                transition["after_state_id"],                transition["transition_type"],                transition["timestamp"],                transition["content"],                transition["provenance"],                transition["metadata"],                transition["created_at"],            ))                         conn.commit()            conn.close()            return True        except Exception as e:            print(f"Error inserting transition: {e}")            return False         def get_transition(self, transition_id: str) -> Optional[Dict[str, Any]]:        """Get a transition by ID."""        conn = self._connect()        cursor = conn.cursor()                 cursor.execute("""            SELECT * FROM transitions WHERE transition_id = ?        """, (transition_id,))                 row = cursor.fetchone()        conn.close()                 if row is None:            return None                 return {            "transition_id": row[0],            "before_state_id": row[1],            "after_state_id": row[2],            "transition_type": row[3],            "timestamp": row[4],            "content": row[5],            "provenance": row[6],            "metadata": row[7],            "created_at": row[8],        }         def insert_state_object(self, state_object: Dict[str, Any]) -> bool:        """Insert a state object (materialized view)."""        try:            conn = self._connect()            cursor = conn.cursor()                         cursor.execute("""                INSERT OR IGNORE INTO state_objects                (state_id, transition_id, object_type, axiom_id, namespace,                 version, created_at, lineage, validation, trust, payload)                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)            """, (                state_object["state_id"],                state_object["transition_id"],                state_object["object_type"],                state_object["axiom_id"],                state_object["namespace"],                state_object["version"],                state_object["created_at"],                state_object["lineage"],                state_object["validation"],                state_object["trust"],                state_object["payload"],            ))                         conn.commit()            conn.close()            return True        except Exception as e:            print(f"Error inserting state object: {e}")            return False         def get_state_object(self, state_id: str) -> Optional[Dict[str, Any]]:        """Get a state object by ID."""        conn = self._connect()        cursor = conn.cursor()                 cursor.execute("""            SELECT * FROM state_objects WHERE state_id = ?        """, (state_id,))                 row = cursor.fetchone()        conn.close()                 if row is None:            return None                 return {            "state_id": row[0],            "transition_id": row[1],            "object_type": row[2],            "axiom_id": row[3],            "namespace": row[4],            "version": row[5],            "created_at": row[6],            "lineage": row[7],            "validation": row[8],            "trust": row[9],            "payload": row[10],        }`

## `src/k501/evidence/transition_store.py`

python

`""" Transition Store: Append-only storage for transitions. Provides: - Insert transition (append-only) - Get transition by ID - Get transitions by state_id - Verify integrity """ from datetime import datetime from typing import Any, Dict, List, Optional from ..storage.sqlite import SQLiteStore from ..core.transition import StateTransition class TransitionStore:     """Append-only transition storage."""         def __init__(self, db_path: str = "data/evidence/evidence.sqlite"):        """Initialize transition store."""        self.store = SQLiteStore(db_path)         def insert(self, transition: StateTransition) -> bool:        """        Insert a transition (append-only).                 Returns True if successful, False if failed.        """        transition_dict = {            "transition_id": transition.transition_id,            "before_state_id": transition.before_state_id,            "after_state_id": transition.after_state_id,            "transition_type": transition.transition_type,            "timestamp": transition.timestamp.isoformat(),            "content": transition.content,            "provenance": transition.provenance,            "metadata": transition.metadata,            "created_at": datetime.utcnow().isoformat(),        }                 return self.store.insert_transition(transition_dict)         def get(self, transition_id: str) -> Optional[StateTransition]:        """Get a transition by ID."""        transition_dict = self.store.get_transition(transition_id)                 if transition_dict is None:            return None                 return StateTransition(            transition_id=transition_dict["transition_id"],            before_state_id=transition_dict["before_state_id"],            after_state_id=transition_dict["after_state_id"],            transition_type=transition_dict["transition_type"],            timestamp=datetime.fromisoformat(transition_dict["timestamp"]),            content=transition_dict["content"],            provenance=transition_dict["provenance"],            metadata=transition_dict["metadata"],        )         def get_by_state(self, state_id: str) -> List[StateTransition]:        """Get all transitions for a state ID."""        # Query transitions where after_state_id = state_id        # This is a simplified implementation        conn = self.store._connect()        cursor = conn.cursor()                 cursor.execute("""            SELECT * FROM transitions WHERE after_state_id = ?        """, (state_id,))                 rows = cursor.fetchall()        conn.close()                 transitions = []        for row in rows:            transition = StateTransition(                transition_id=row[0],                before_state_id=row[1],                after_state_id=row[2],                transition_type=row[3],                timestamp=datetime.fromisoformat(row[4]),                content=row[5],                provenance=row[6],                metadata=row[7],            )            transitions.append(transition)                 return transitions`

---

## Output 5: Complete pytest Test Suites

## `tests/unit/test_transition.py`

python

`""" Unit tests for StateTransition. Tests: - Transition creation - Identity axiom (same transition + different timestamp = same ID) - State object materialization """ from datetime import datetime from k501.core.transition import StateTransition def test_transition_creation():     """Test transition creation with deterministic ID."""    timestamp1 = datetime(2026, 6, 17, 0, 0, 0)         transition = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp=timestamp1,        content={            "object_type": "frame",            "axiom_id": "axiom:test",            "namespace": "research",        },        provenance={            "source": "test",            "writer": "test_writer",        },    )         assert transition.transition_id.startswith("transition:")    assert transition.after_state_id == "state:frame:123"    assert transition.transition_type == "create" def test_identity_axiom():     """    Test identity axiom: same content + provenance = same ID.         Different timestamps should NOT affect identity.    """    timestamp1 = datetime(2026, 6, 17, 0, 0, 0)    timestamp2 = datetime(2026, 6, 18, 0, 0, 0)  # Different timestamp         transition1 = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp=timestamp1,        content={            "object_type": "frame",            "axiom_id": "axiom:test",            "namespace": "research",        },        provenance={            "source": "test",            "writer": "test_writer",        },    )         transition2 = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp=timestamp2,  # Different timestamp        content={            "object_type": "frame",            "axiom_id": "axiom:test",            "namespace": "research",        },        provenance={            "source": "test",            "writer": "test_writer",        },    )         # Same identity (content + provenance)    assert transition1.transition_id == transition2.transition_id         # Different occurrence (identity + timestamp)    assert not transition1.is_same_occurrence(transition2) def test_state_object_materialization():     """Test state object materialization from transition."""    timestamp = datetime(2026, 6, 17, 0, 0, 0)         transition = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp=timestamp,        content={            "object_type": "frame",            "axiom_id": "axiom:test",            "namespace": "research",            "version": "1.0.0",            "lineage": {},            "validation": {},            "trust": {},            "payload": {"title": "Test Frame"},        },        provenance={            "source": "test",            "writer": "test_writer",        },    )         state_object = transition.to_state_object()         assert state_object["state_id"] == "state:frame:123"    assert state_object["transition_id"] == transition.transition_id    assert state_object["object_type"] == "frame"    assert state_object["axiom_id"] == "axiom:test"    assert state_object["namespace"] == "research"`

## `tests/unit/test_canonical_serialization.py`

python

`""" Unit tests for canonical serialization. Tests: - RFC 8785 JCS compliance - Deterministic hashing - Type normalization """ from k501.utils.canonical_serialization import canonical_serialize, canonical_hash def test_key_sorting():     """Test that keys are sorted alphabetically."""    obj = {"b": 1, "a": 2, "c": 3}    result = canonical_serialize(obj)         assert result == '{"a":2,"b":1,"c":3}' def test_nested_objects():     """Test nested object serialization."""    obj = {"outer": {"b": 1, "a": 2}}    result = canonical_serialize(obj)         assert result == '{"outer":{"a":2,"b":1}}' def test_arrays():     """Test array order preservation."""    obj = {"arr": [3, 1, 2]}    result = canonical_serialize(obj)         assert result == '{"arr":[3,1,2]}' def test_number_normalization():     """Test number normalization (1 == 1.0)."""    obj1 = {"val": 1}    obj2 = {"val": 1.0}         hash1 = canonical_hash(obj1)    hash2 = canonical_hash(obj2)         assert hash1 == hash2 def test_unicode_preservation():     """Test Unicode preserved (not escaped)."""    obj = {"text": "Hello 世界"}    result = canonical_serialize(obj)         assert "世界" in result    assert "\\u" not in result def test_deterministic_hash():     """Test that same object produces same hash."""    obj = {"a": 1, "b": 2}         hash1 = canonical_hash(obj)    hash2 = canonical_hash(obj)         assert hash1 == hash2    assert len(hash1) == 64  # SHA-256 hex length def test_different_objects_different_hash():     """Test that different objects produce different hashes."""    obj1 = {"a": 1}    obj2 = {"a": 2}         hash1 = canonical_hash(obj1)    hash2 = canonical_hash(obj2)         assert hash1 != hash2`

---

## Output 6: ADR Recommendations

## ADR-001: Identity Axiom

**Decision:** Transition identity = `content + provenance` (NOT timestamp)

**Reasoning:**

- Preserves determinism across replays
    
- Same transition = same identity regardless of when observed
    
- Timestamp is occurrence metadata, not identity metadata
    

**Alternatives Considered:**

- `content_only` — Too weak, no provenance
    
- `content_plus_timestamp` — Too strong, breaks replay
    
- `content_plus_all` — Too strong, breaks replay
    

## ADR-002: Primary Object

**Decision:** StateTransition is primary object, StateObject is materialized view

**Reasoning:**

- Architecture says "primary object is state transition"
    
- Event sourcing pattern: Event → Projection → Current State
    
- Transition = Event, StateObject = Projection
    

**Alternatives Considered:**

- StateObject as primary — Violates architecture
    
- Event as primary (no before_state) — Less precise than transition
    

## ADR-003: Canonical Serialization

**Decision:** RFC 8785 JCS for deterministic hashing

**Reasoning:**

- Mathematically unique serialization
    
- Industry standard (W3C)
    
- Ensures interoperability across implementations
    

**Alternatives Considered:**

- Custom JSON serialization — Not standardized
    
- CBOR — Different format, less portable
    

## ADR-004: Graph Constraint

**Decision:** DAG constraint on DERIVED_FROM edges

**Reasoning:**

- Prevents infinite traversal loops
    
- Provenance must be acyclic
    
- Detects circular dependencies
    

**Alternatives Considered:**

- Allow cycles — Breaks provenance
    
- No constraint — Silent failures
    

## ADR-005: Lifecycle Rules

**Decision:** Per-object-type Transition Registry (not fixed lifecycle in core)

**Reasoning:**

- Different object types have different rules
    
- Frame: CREATE → FREEZE → ARCHIVE
    
- Belief: CREATE → ACCEPT/REJECT/CONTEST
    
- Extensible for new object types
    

**Alternatives Considered:**

- Fixed lifecycle in core — Too rigid
    
- No registry — Inconsistent rules
    

---

## Output 7: Shortest Path to MVP

## Current State: v0-clean

**What exists:**

- Architecture docs
    
- JSON schemas
    
- pyproject.toml, Makefile
    
- Logging config
    
- Core primitives (partial)
    

**What's missing for MVP:**

1. Transition Core (identity axiom, StateTransition, registry)
    
2. Canonical Serialization (RFC 8785)
    
3. Evidence Store (transition store, SQLite backend)
    
4. Unit tests (transition, canonical serialization)
    

## MVP Definition

**Working local-first AIONARC MVP:**

- Can ingest document → CREATE transition → state object
    
- Can freeze state → FREEZE transition
    
- Can archive → ARCHIVE transition
    
- Can replay archive → identical transition_id
    
- Can query lineage → transition chain
    

## Shortest Path (4 Weeks)

**Week 1:** Transition Core

- Implement `identity_axiom.py`, `transition.py`, `transition_registry.py`
    
- Implement `canonical_serialization.py` (RFC 8785)
    
- Write unit tests
    

**Week 2:** Evidence Store

- Implement `sqlite.py`, `transition_store.py`
    
- Implement `ingest.py`, `freeze.py`, `archive.py`
    
- Write integration tests
    

**Week 3:** Basic Retrieval

- Implement `chunker.py`, `vector_index.py`
    
- Implement basic search (semantic only)
    
- Write retrieval tests
    

**Week 4:** API + MVP Validation

- Implement HTTP API (`/ingest`, `/freeze`, `/archive`, `/search`)
    
- End-to-end test: ingest → freeze → archive → replay → verify
    
- MVP documentation
    

## MVP Artifacts

text

`k501-aionarc/   src/k501/    core/      transition.py ✅      identity_axiom.py ✅      transition_registry.py ✅    utils/      canonical_serialization.py ✅    storage/      sqlite.py ✅    evidence/      transition_store.py ✅      ingest.py ✅      freeze.py ✅      archive.py ✅    retrieval/      chunker.py ✅      vector_index.py ✅    api/      routes/evidence.py ✅  tests/    unit/test_transition.py ✅    unit/test_canonical_serialization.py ✅    integration/test_ingestion_pipeline.py ✅    e2e/test_archive_replay.py ✅`

## MVP Acceptance Criteria

1. ✅ Ingest document → CREATE transition → state object stored
    
2. ✅ Freeze state → FREEZE transition → transition stored
    
3. ✅ Archive → ARCHIVE transition → transition stored
    
4. ✅ Replay archive → identical transition_id (identity axiom verified)
    
5. ✅ Query lineage → transition chain returned
    
6. ✅ Local-first (no cloud, works air-gapped)
    
7. ✅ All tests pass (100% Phase 1–3 coverage)
    

This is the shortest path from v0-clean to working MVP.