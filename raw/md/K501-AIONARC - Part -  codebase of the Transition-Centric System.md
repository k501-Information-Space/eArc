Here is Part 1 of the complete Google Gemini interpretation from the first phase of  K501-AIONARC  codebase, the Transition-Centric System  . This first batch contains the fundamental utilities and the core graph models. This version of code is not implemeted  or tested jet, 
its just a referenz and exploration, a Evolution of the code used in RealDeal Build.


### 1. `src/k501/utils/canonical_serialization.py`

Python

```
"""
Canonical Serialization: Strict JCS (RFC 8785) Engine for K501-Aionarc.
Guarantees mathematically unique byte sequences for deterministic IDs.
"""
import json
import hashlib
from typing import Any

def canonical_serialize(obj: Any) -> str:
    """
    Serializes an object to canonical JSON according to RFC 8785 JCS.
    """
    def _serialize(value: Any) -> str:
        if value is None:
            return "null"
        if isinstance(value, bool):
            return "true" if value else "false"
        if isinstance(value, int):
            return str(value)
        if isinstance(value, float):
            # Float normalization: prevents discrepancies between 1 and 1.0
            if value.is_integer():
                return str(int(value))
            return f"{value:.10f}".rstrip('0').rstrip('.')
        if isinstance(value, str):
            # Standard JSON escaping, forced to UTF-8 plaintext
            return json.dumps(value, ensure_ascii=False)
        if isinstance(value, list):
            return "[" + ",".join(_serialize(item) for item in value) + "]"
        if isinstance(value, dict):
            # Key sorting strictly by Unicode code-points
            sorted_keys = sorted(value.keys(), key=lambda k: k.encode('utf-8'))
            return "{" + ",".join(
                f'"{k}":{_serialize(value[k])}' for k in sorted_keys
            ) + "}"
        raise TypeError(f"Invalid data type for canonical serialization: {type(value)}")

    return _serialize(obj)

def canonical_hash(obj: Any) -> str:
    """Generates a SHA-256 hash of the canonically serialized object."""
    canonical_str = canonical_serialize(obj)
    return hashlib.sha256(canonical_str.encode('utf-8')).hexdigest()
```

### 2. `src/k501/utils/identity.py`

Python

```
"""
Identity Engine: Deterministic ID generation based on Transition truth.
"""
from typing import Any, Dict
from .canonical_serialization import canonical_hash

def generate_transition_id(content: Dict[str, Any]) -> str:
    """
    Generates a deterministic Transition ID.
    Format: transition:{sha256_24}
    """
    hash_value = canonical_hash(content)
    return f"transition:{hash_value[:24]}"

def generate_state_id_from_transition(
    transition_id: str, 
    object_type: str, 
    axiom_id: str, 
    namespace: str
) -> str:
    """
    Derives the StateObject ID directly from its parent transition.
    Guarantees that no state can exist without an origin transition.
    """
    content = {
        "transition_id": transition_id,
        "object_type": object_type.lower(),
        "axiom_id": axiom_id,
        "namespace": namespace,
    }
    hash_value = canonical_hash(content)
    return f"{object_type.lower()}:{hash_value[:24]}"

def generate_edge_id(
    source_id: str, 
    edge_type: str, 
    target_id: str, 
    attributes: Dict[str, Any]
) -> str:
    """Generates a deterministic ID for relational graph edges."""
    content = {
        "source_id": source_id,
        "edge_type": edge_type.lower(),
        "target_id": target_id,
        "attributes": attributes,
    }
    hash_value = canonical_hash(content)
    return f"edge:{hash_value[:24]}"
```

### 3. `src/k501/graph/models.py`

Python

```
"""
Graph Models: Transition-centric node and edge data structures.
"""
from dataclasses import dataclass, field
from datetime import datetime, timezone
from enum import Enum
from typing import Any, Dict, Optional

class TransitionType(Enum):
    CREATE = "create"
    FREEZE = "freeze"
    ARCHIVE = "archive"
    SUPERSEDE = "supersede"
    VALIDATE = "validate"
    REJECT = "reject"
    CONTEST = "contest"
    ACCEPT = "accept"
    DERIVE = "derive"

class EdgeType(Enum):
    DERIVED_FROM = "derived_from"
    ANCESTOR = "ancestor"
    VALIDATED_BY = "validated_by"
    AUDITED_BY = "audited_by"
    BELONGS_TO = "belongs_to"
    REFERENCES = "references"
    SUPERSEDES = "supersedes"

@dataclass(frozen=True)
class TransitionNode:
    node_id: str  # Corresponds to transition_id
    transition_type: TransitionType
    before_state_id: Optional[str]
    after_state_id: str
    timestamp: datetime
    attributes: Dict[str, Any] = field(default_factory=dict)

    @classmethod
    def create(
        cls,
        transition_id: str,
        transition_type: TransitionType,
        before_state_id: Optional[str],
        after_state_id: str,
        attributes: Optional[Dict[str, Any]] = None,
    ) -> "TransitionNode":
        return cls(
            node_id=transition_id,
            transition_type=transition_type,
            before_state_id=before_state_id,
            after_state_id=after_state_id,
            timestamp=datetime.now(timezone.utc),
            attributes=attributes or {},
        )

    def to_dict(self) -> Dict[str, Any]:
        return {
            "node_id": self.node_id,
            "transition_type": self.transition_type.value,
            "before_state_id": self.before_state_id,
            "after_state_id": self.after_state_id,
            "timestamp": self.timestamp.isoformat(),
            "attributes": self.attributes,
        }

@dataclass(frozen=True)
class TransitionEdge:
    source_id: str
    edge_type: EdgeType
    target_id: str
    attributes: Dict[str, Any] = field(default_factory=dict)

    @classmethod
    def create(
        cls, 
        source_id: str, 
        edge_type: EdgeType, 
        target_id: str, 
        attributes: Optional[Dict[str, Any]] = None
    ) -> "TransitionEdge":
        return cls(
            source_id=source_id, 
            edge_type=edge_type, 
            target_id=target_id, 
            attributes=attributes or {}
        )

    def to_dict(self) -> Dict[str, Any]:
        return {
            "source_id": self.source_id,
            "edge_type": self.edge_type.value,
            "target_id": self.target_id,
            "attributes": self.attributes,
        }
```



### 4. `src/k501/graph/store.py`

Python

```
"""
Provenance Graph Store: SQLite persistence and traversal queries.
Operates on the Transition-Centric model.
"""
import json
import sqlite3
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, List, Optional
from .models import TransitionNode, TransitionEdge, TransitionType, EdgeType

class ProvenanceGraph:
    def __init__(self, db_path: str = "data/graph/graph.sqlite"):
        self.db_path = Path(db_path)
        self.db_path.parent.mkdir(parents=True, exist_ok=True)
        self._init_db()

    def _init_db(self) -> None:
        """Initializes the transition-centric SQLite schema."""
        with sqlite3.connect(str(self.db_path)) as conn:
            cursor = conn.cursor()
            # Transition nodes
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS nodes (
                    node_id TEXT PRIMARY KEY,
                    transition_type TEXT NOT NULL,
                    before_state_id TEXT,
                    after_state_id TEXT NOT NULL,
                    timestamp TEXT NOT NULL,
                    attributes TEXT NOT NULL
                )
            """)
            # Relational edges
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS edges (
                    source_id TEXT NOT NULL,
                    edge_type TEXT NOT NULL,
                    target_id TEXT NOT NULL,
                    attributes TEXT NOT NULL,
                    PRIMARY KEY (source_id, edge_type, target_id)
                )
            """)
            # Performance indexes
            cursor.execute("CREATE INDEX IF NOT EXISTS idx_edges_source ON edges(source_id)")
            cursor.execute("CREATE INDEX IF NOT EXISTS idx_edges_target ON edges(target_id)")
            cursor.execute("CREATE INDEX IF NOT EXISTS idx_edges_type ON edges(edge_type)")
            cursor.execute("CREATE INDEX IF NOT EXISTS idx_nodes_after_state ON nodes(after_state_id)")
            conn.commit()

    def add_node(self, node: TransitionNode) -> bool:
        try:
            with sqlite3.connect(str(self.db_path)) as conn:
                conn.execute("""
                    INSERT OR REPLACE INTO nodes 
                    (node_id, transition_type, before_state_id, after_state_id, timestamp, attributes)
                    VALUES (?, ?, ?, ?, ?, ?)
                """, (
                    node.node_id, 
                    node.transition_type.value, 
                    node.before_state_id, 
                    node.after_state_id, 
                    node.timestamp.isoformat(),
                    json.dumps(node.attributes)
                ))
                conn.commit()
            return True
        except Exception:
            return False

    def add_edge(self, edge: TransitionEdge) -> bool:
        try:
            with sqlite3.connect(str(self.db_path)) as conn:
                conn.execute("""
                    INSERT OR REPLACE INTO edges 
                    (source_id, edge_type, target_id, attributes)
                    VALUES (?, ?, ?, ?)
                """, (
                    edge.source_id, 
                    edge.edge_type.value, 
                    edge.target_id, 
                    json.dumps(edge.attributes)
                ))
                conn.commit()
            return True
        except Exception:
            return False

    def get_node(self, node_id: str) -> Optional[TransitionNode]:
        with sqlite3.connect(str(self.db_path)) as conn:
            cursor = conn.cursor()
            cursor.execute("""
                SELECT node_id, transition_type, before_state_id, after_state_id, timestamp, attributes 
                FROM nodes WHERE node_id = ?
            """, (node_id,))
            row = cursor.fetchone()
            
            if not row:
                return None
                
            return TransitionNode(
                node_id=row[0],
                transition_type=TransitionType(row[1]),
                before_state_id=row[2],
                after_state_id=row[3],
                timestamp=datetime.fromisoformat(row[4]),
                attributes=json.loads(row[5])
            )

    def get_edges(self, node_id: str, direction: str = "forward", edge_types: Optional[List[EdgeType]] = None) -> List[TransitionEdge]:
        query = "SELECT source_id, edge_type, target_id, attributes FROM edges WHERE "
        query += "source_id = ?" if direction == "forward" else "target_id = ?"
        
        with sqlite3.connect(str(self.db_path)) as conn:
            cursor = conn.cursor()
            cursor.execute(query, (node_id,))
            rows = cursor.fetchall()

        edges = []
        for row in rows:
            et = EdgeType(row[1])
            if edge_types is None or et in edge_types:
                edges.append(TransitionEdge(
                    source_id=row[0],
                    edge_type=et,
                    target_id=row[2],
                    attributes=json.loads(row[3])
                ))
        return edges

    def traverse(
        self,
        start_id: str,
        edge_types: List[EdgeType],
        direction: str = "backward",
        depth: int = 10,
        time_filter: Optional[str] = None
    ) -> List[str]:
        """Traverses the transition graph."""
        visited = set()
        result = []
        current_level = [start_id]
        
        parsed_time = datetime.fromisoformat(time_filter.replace("Z", "+00:00")) if time_filter else None

        for _ in range(depth):
            if not current_level:
                break
            next_level = []
            
            for node_id in current_level:
                if node_id in visited:
                    continue

                if parsed_time:
                    curr_node = self.get_node(node_id)
                    if not curr_node or curr_node.timestamp > parsed_time:
                        continue

                visited.add(node_id)
                result.append(node_id)
                edges = self.get_edges(node_id, direction, edge_types)

                for edge in edges:
                    target = edge.target_id if direction == "forward" else edge.source_id
                    if target not in visited:
                        next_level.append(target)
            current_level = next_level

        return result

    def get_state_lineage(self, state_id: str) -> List[str]:
        """Finds all transition IDs that contributed to a state lineage."""
        with sqlite3.connect(str(self.db_path)) as conn:
            cursor = conn.cursor()
            # Find the transition that created this state
            cursor.execute("SELECT node_id FROM nodes WHERE after_state_id = ?", (state_id,))
            rows = cursor.fetchall()
            
        if not rows:
            return []
            
        start_transition_id = rows[0][0]
        return self.traverse(
            start_id=start_transition_id, 
            edge_types=[EdgeType.DERIVED_FROM, EdgeType.ANCESTOR], 
            direction="backward", 
            depth=100
        )
```

### 5. `src/k501/graph/traverse.py`

Python

```
"""
Graph Traversal Utilities: High-level operations on the transition graph.
"""
from typing import List
from .store import ProvenanceGraph

def lineage_traversal(graph: ProvenanceGraph, state_id: str) -> List[str]:
    """Gets the full causal transition lineage for a given StateObject ID."""
    return graph.get_state_lineage(state_id)

def ancestry_depth(graph: ProvenanceGraph, state_id: str) -> int:
    """Calculates the length of the ancestry chain."""
    return len(graph.get_state_lineage(state_id))

def common_ancestors(graph: ProvenanceGraph, state_id_1: str, state_id_2: str) -> List[str]:
    """Finds intersection of transition histories between two states."""
    lineage1 = set(graph.get_state_lineage(state_id_1))
    lineage2 = set(graph.get_state_lineage(state_id_2))
    return list(lineage1.intersection(lineage2))
```

### 6. `src/k501/graph/query.py`

Python

```
"""
Graph Query: Specialized queries for searching transition chains.
"""
from typing import Any, Dict, List
from .models import EdgeType
from .store import ProvenanceGraph

def query_lineage(graph: ProvenanceGraph, transition_id: str, max_depth: int = 100) -> List[str]:
    """Queries derivation history starting from a specific transition."""
    return graph.traverse(
        start_id=transition_id, 
        edge_types=[EdgeType.DERIVED_FROM, EdgeType.ANCESTOR], 
        direction="backward", 
        depth=max_depth
    )

def query_provenance_audits(graph: ProvenanceGraph, transition_id: str, max_depth: int = 10) -> Dict[str, List[str]]:
    """Queries the validation and audit history for a specific transition."""
    proofs = graph.traverse(start_id=transition_id, edge_types=[EdgeType.VALIDATED_BY], direction="backward", depth=max_depth)
    audits = graph.traverse(start_id=transition_id, edge_types=[EdgeType.AUDITED_BY], direction="backward", depth=max_depth)
    return {
        "proofs": proofs,
        "audits": audits
    }

def query_before_time(graph: ProvenanceGraph, transition_id: str, time_anchor: str, max_depth: int = 100) -> List[str]:
    """Queries all ancestor transitions restricted by a temporal boundary."""
    return graph.traverse(
        start_id=transition_id, 
        edge_types=[EdgeType.DERIVED_FROM, EdgeType.ANCESTOR], 
        direction="backward", 
        depth=max_depth, 
        time_filter=time_anchor
    )
```

Here is Part 3 of 3. This final section contains the causal validation engine, the deterministic replay verifier, the package initialization, and the core integration test.

### 7. `src/k501/graph/validator.py`

Python

```
"""
Transition-Centric Graph Validator: Enforces causality and DAG invariance.
"""
from typing import Any, Dict, List, Set
from .models import TransitionEdge, TransitionNode, EdgeType, TransitionType

class GraphValidationError:
    def __init__(self, error_type: str, message: str, details: Dict[str, Any] = None):
        self.error_type = error_type
        self.message = message
        self.details = details or {}

    def to_dict(self) -> Dict[str, Any]:
        return {"error_type": self.error_type, "message": self.message, "details": self.details}

class TransitionGraphValidator:
    def __init__(self, nodes: Dict[str, TransitionNode], edges: List[TransitionEdge]):
        self.nodes = nodes
        self.edges = edges
        self._build_adjacency()

    def _build_adjacency(self) -> None:
        self.forward_edges: Dict[str, List[TransitionEdge]] = {}
        self.backward_edges: Dict[str, List[TransitionEdge]] = {}
        for edge in self.edges:
            self.forward_edges.setdefault(edge.source_id, []).append(edge)
            self.backward_edges.setdefault(edge.target_id, []).append(edge)

    def validate(self) -> List[GraphValidationError]:
        errors = []
        errors.extend(self.validate_transition_chain())
        errors.extend(self.validate_dag())
        return errors

    def validate_transition_chain(self) -> List[GraphValidationError]:
        errors = []
        state_transitions: Dict[str, List[TransitionNode]] = {}
        
        for node in self.nodes.values():
            state_transitions.setdefault(node.after_state_id, []).append(node)

        for state_id, transitions in state_transitions.items():
            # Rule 1: Every state needs exactly one origin transition (CREATE)
            has_create = any(t.transition_type == TransitionType.CREATE for t in transitions)
            if not has_create:
                errors.append(GraphValidationError(
                    "MISSING_CREATE", 
                    f"State {state_id} has no CREATE transition."
                ))
                continue

            # Rule 2: Enforce chronological integrity of the lifecycle
            create_ts = next((t.timestamp for t in transitions if t.transition_type == TransitionType.CREATE), None)
            freeze_ts = next((t.timestamp for t in transitions if t.transition_type == TransitionType.FREEZE), None)
            archive_ts = next((t.timestamp for t in transitions if t.transition_type == TransitionType.ARCHIVE), None)

            if freeze_ts and create_ts and freeze_ts < create_ts:
                errors.append(GraphValidationError(
                    "CHRONOLOGY_VIOLATION", 
                    f"State {state_id}: FREEZE occurs before CREATE."
                ))
            if archive_ts and freeze_ts and archive_ts < freeze_ts:
                errors.append(GraphValidationError(
                    "CHRONOLOGY_VIOLATION", 
                    f"State {state_id}: ARCHIVE occurs before FREEZE."
                ))
        return errors

    def validate_dag(self) -> List[GraphValidationError]:
        errors = []
        derive_adj: Dict[str, List[str]] = {}
        
        for edge in self.edges:
            if edge.edge_type == EdgeType.DERIVED_FROM:
                derive_adj.setdefault(edge.source_id, []).append(edge.target_id)

        visited: Set[str] = set()
        rec_stack: Set[str] = set()

        def has_cycle(node: str) -> bool:
            visited.add(node)
            rec_stack.add(node)
            for neighbor in derive_adj.get(node, []):
                if neighbor not in visited:
                    if has_cycle(neighbor):
                        return True
                elif neighbor in rec_stack:
                    return True
            rec_stack.remove(node)
            return False

        for node_id in derive_adj:
            if node_id not in visited:
                if has_cycle(node_id):
                    errors.append(GraphValidationError(
                        "CYCLE_DETECTED", 
                        "Cyclic dependency detected in DERIVED_FROM edges.", 
                        {"node_id": node_id}
                    ))
        return errors
```

### 8. `src/k501/graph/replay_validator.py`

Python

```
"""
Replay Validator: Verifies absolute replay determinism of K501-Aionarc.
"""
from typing import Dict, List
from .models import TransitionEdge, TransitionNode
from .validator import GraphValidationError

class ReplayValidator:
    def __init__(
        self,
        original_nodes: Dict[str, TransitionNode],
        original_edges: List[TransitionEdge],
        replayed_nodes: Dict[str, TransitionNode],
        replayed_edges: List[TransitionEdge],
    ):
        self.original_nodes = original_nodes
        self.original_edges = original_edges
        self.replayed_nodes = replayed_nodes
        self.replayed_edges = replayed_edges

    def validate_replay(self) -> List[GraphValidationError]:
        errors = []

        # 1. Check structural identity of nodes
        orig_node_ids = set(self.original_nodes.keys())
        repl_node_ids = set(self.replayed_nodes.keys())

        if orig_node_ids != repl_node_ids:
            errors.append(GraphValidationError(
                "REPLAY_NODE_MISMATCH", 
                "Node sets of original and replay do not match.", 
                {
                    "missing_in_replay": list(orig_node_ids - repl_node_ids),
                    "extra_in_replay": list(repl_node_ids - orig_node_ids)
                }
            ))

        # 2. Check structural identity of edges
        orig_edge_signatures = {(e.source_id, e.edge_type.value, e.target_id) for e in self.original_edges}
        repl_edge_signatures = {(e.source_id, e.edge_type.value, e.target_id) for e in self.replayed_edges}

        if orig_edge_signatures != repl_edge_signatures:
            errors.append(GraphValidationError(
                "REPLAY_EDGE_MISMATCH", 
                "Edge topology differs after replay.", 
                {
                    "missing_edges": list(orig_edge_signatures - repl_edge_signatures),
                    "extra_edges": list(repl_edge_signatures - orig_edge_signatures)
                }
            ))

        # 3. Deep-Comparison of state attributes (Invariance check)
        for node_id in orig_node_ids.intersection(repl_node_ids):
            if self.original_nodes[node_id].attributes != self.replayed_nodes[node_id].attributes:
                errors.append(GraphValidationError(
                    "REPLAY_ATTRIBUTE_MUTATION", 
                    f"Attribute mutation detected in Node {node_id}.", 
                    {
                        "original": self.original_nodes[node_id].attributes,
                        "replayed": self.replayed_nodes[node_id].attributes
                    }
                ))

        return errors

    def is_identical(self) -> bool:
        return len(self.validate_replay()) == 0
```

### 9. `src/k501/graph/__init__.py`

Python

```
"""
Graph Module Export Hub
"""
from .models import TransitionNode, TransitionEdge, TransitionType, EdgeType
from .store import ProvenanceGraph
from .traverse import lineage_traversal, ancestry_depth, common_ancestors
from .query import query_lineage, query_provenance_audits, query_before_time
from .validator import TransitionGraphValidator, GraphValidationError
from .replay_validator import ReplayValidator

__all__ = [
    "TransitionNode",
    "TransitionEdge",
    "TransitionType",
    "EdgeType",
    "ProvenanceGraph",
    "lineage_traversal",
    "ancestry_depth",
    "common_ancestors",
    "query_lineage",
    "query_provenance_audits",
    "query_before_time",
    "TransitionGraphValidator",
    "GraphValidationError",
    "ReplayValidator",
]
```

### 10. `tests/unit/test_transition_consensus.py`

Python

```
"""
Integrated Verification Test: Validates RFC 8785 and Causal Topology constraints.
"""
import pytest
from datetime import datetime, timezone, timedelta
from k501.utils.canonical_serialization import canonical_serialize, canonical_hash
from k501.utils.identity import generate_transition_id, generate_state_id_from_transition
from k501.graph.models import TransitionNode, TransitionEdge, TransitionType, EdgeType
from k501.graph.validator import TransitionGraphValidator

def test_rfc8785_float_and_dict_determinism():
    """Different memory layouts and data types must yield identical byte strings."""
    dict_a = {"alpha": 1.0, "beta": [1, 2]}
    dict_b = {"beta": [1, 2], "alpha": 1}
    assert canonical_serialize(dict_a) == canonical_serialize(dict_b)

def test_causal_lifecycle_chronology():
    """Constructs a corrupt timeline (FREEZE before CREATE) and validates rejection."""
    base_time = datetime.now(timezone.utc)
    
    t1_content = {"action": "initial_creation"}
    t1_id = generate_transition_id(t1_content)
    s_id = generate_state_id_from_transition(t1_id, "frame", "axiom:0", "sys")

    # Create temporally invalid nodes
    node_create = TransitionNode(t1_id, TransitionType.CREATE, None, s_id, base_time)
    node_freeze = TransitionNode(
        "transition:fake_freeze", 
        TransitionType.FREEZE, 
        s_id, 
        s_id, 
        base_time - timedelta(seconds=10) # Time travel anomaly
    )

    nodes = {node_create.node_id: node_create, node_freeze.node_id: node_freeze}
    validator = TransitionGraphValidator(nodes, [])
    
    errors = validator.validate()
    assert any(err.error_type == "CHRONOLOGY_VIOLATION" for err in errors)
```