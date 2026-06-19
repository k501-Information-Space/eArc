Below is **Phase 1, Step 1** of the K501-Aionarc implementation: the core ontology runtime primitives, stable ID generation, and unit tests.

---

## 1. `src/k501/core/__init__.py`

python

`""" K501 Core Ontology Package Exports all core primitives: - Axiom - Kernel - Frame - Snapshot - Freeze - StateObject - StateTransition """ from .axiom import Axiom from .kernel import Kernel from .frame import Frame from .snapshot import Snapshot from .freeze import Freeze from .state_object import StateObject from .lifecycle import StateTransition __all__ = [     "Axiom",    "Kernel",    "Frame",    "Snapshot",    "Freeze",    "StateObject",    "StateTransition", ]`

---

## 2. `src/k501/core/axiom.py`

python

`""" Axiom: Root layer anchoring deterministic origin. An Axiom is the immutable foundation for all state objects. It defines the canonical origin point for the entire memory system. """ from dataclasses import dataclass, field from datetime import datetime from typing import Any, Dict, Final from ..utils.ids import create_deterministic_id from ..utils.hashing import hash_content @dataclass(frozen=True) class Axiom:     """Immutable root axiom for K501-Aionarc."""         axiom_id: str    name: str    description: str    created_at: datetime    canonical: bool = True    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        name: str,        description: str,        created_at: datetime,        metadata: Dict[str, Any] = {},    ) -> "Axiom":        """Create a new Axiom with deterministic ID."""        content = f"{name}:{description}:{created_at.isoformat()}"        axiom_id = create_deterministic_id("axiom", content)                 return cls(            axiom_id=axiom_id,            name=name,            description=description,            created_at=created_at,            canonical=True,            metadata=metadata,        )         def to_dict(self) -> Dict[str, Any]:        """Convert to dictionary."""        return {            "axiom_id": self.axiom_id,            "name": self.name,            "description": self.description,            "created_at": self.created_at.isoformat(),            "canonical": self.canonical,            "metadata": self.metadata,        }         def to_json(self) -> str:        """Convert to JSON string."""        import json        return json.dumps(self.to_dict(), indent=2)`

---

## 3. `src/k501/core/kernel.py`

python

`""" Kernel: Runtime engine for execution and task dispatch. The Kernel manages: - Task dispatch - Frame creation - Deterministic transitions - Runtime state """ from dataclasses import dataclass, field from datetime import datetime from typing import Any, Dict, List, Optional from ..utils.ids import create_deterministic_id from .frame import Frame @dataclass class Kernel:     """Runtime engine for K501-Aionarc."""         kernel_id: str    axiom_id: str    created_at: datetime    status: str = "active"  # active, frozen, archived    active_frames: List[str] = field(default_factory=list)    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        axiom_id: str,        created_at: datetime,        metadata: Dict[str, Any] = {},    ) -> "Kernel":        """Create a new Kernel with deterministic ID."""        content = f"{axiom_id}:{created_at.isoformat()}:kernel"        kernel_id = create_deterministic_id("kernel", content)                 return cls(            kernel_id=kernel_id,            axiom_id=axiom_id,            created_at=created_at,            status="active",            metadata=metadata,        )         def add_frame(self, frame_id: str) -> None:        """Register a frame with this kernel."""        if frame_id not in self.active_frames:            self.active_frames.append(frame_id)         def remove_frame(self, frame_id: str) -> None:        """Remove a frame from this kernel."""        if frame_id in self.active_frames:            self.active_frames.remove(frame_id)         def to_dict(self) -> Dict[str, Any]:        """Convert to dictionary."""        return {            "kernel_id": self.kernel_id,            "axiom_id": self.axiom_id,            "created_at": self.created_at.isoformat(),            "status": self.status,            "active_frames": self.active_frames,            "metadata": self.metadata,        }`

---

## 4. `src/k501/core/frame.py`

python

`""" Frame: Executable or observable state slice. A Frame bridges runtime and archive. It carries namespace, pointer, timestamp, and lineage metadata. """ from dataclasses import dataclass, field from datetime import datetime from typing import Any, Dict, List, Optional from ..utils.ids import create_deterministic_id from .kernel import Kernel @dataclass class Frame:     """Executable or observable state slice."""         frame_id: str    kernel_id: str    namespace: str    status: str = "active"  # active, frozen, archived    created_at: datetime    snapshot_id: Optional[str] = None    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        kernel_id: str,        namespace: str,        created_at: datetime,        metadata: Dict[str, Any] = {},    ) -> "Frame":        """Create a new Frame with deterministic ID."""        content = f"{kernel_id}:{namespace}:{created_at.isoformat()}:frame"        frame_id = create_deterministic_id("frame", content)                 return cls(            frame_id=frame_id,            kernel_id=kernel_id,            namespace=namespace,            status="active",            created_at=created_at,            metadata=metadata,        )         def to_dict(self) -> Dict[str, Any]:        """Convert to dictionary."""        return {            "frame_id": self.frame_id,            "kernel_id": self.kernel_id,            "namespace": self.namespace,            "status": self.status,            "created_at": self.created_at.isoformat(),            "snapshot_id": self.snapshot_id,            "metadata": self.metadata,        }         def freeze(self) -> None:        """Mark frame as frozen."""        self.status = "frozen"         def archive(self) -> None:        """Mark frame as archived."""        self.status = "archived"         def link_snapshot(self, snapshot_id: str) -> None:        """Link frame to a snapshot."""        self.snapshot_id = snapshot_id`

---

## 5. `src/k501/core/snapshot.py`

python

`""" Snapshot: Consistent view of state for freeze and archive. A Snapshot captures a point-in-time state of a Frame. """ from dataclasses import dataclass, field from datetime import datetime from typing import Any, Dict, Optional from ..utils.ids import create_deterministic_id from ..utils.hashing import hash_content from .frame import Frame @dataclass(frozen=True) class Snapshot:     """Consistent point-in-time view of state."""         snapshot_id: str    frame_id: str    created_at: datetime    state_hash: str    freeze_id: Optional[str] = None    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        frame_id: str,        created_at: datetime,        state_data: Any,        metadata: Dict[str, Any] = {},    ) -> "Snapshot":        """Create a new Snapshot with deterministic ID."""        state_hash = hash_content(state_data)        content = f"{frame_id}:{created_at.isoformat()}:{state_hash}"        snapshot_id = create_deterministic_id("snapshot", content)                 return cls(            snapshot_id=snapshot_id,            frame_id=frame_id,            created_at=created_at,            state_hash=state_hash,            metadata=metadata,        )         def to_dict(self) -> Dict[str, Any]:        """Convert to dictionary."""        return {            "snapshot_id": self.snapshot_id,            "frame_id": self.frame_id,            "created_at": self.created_at.isoformat(),            "state_hash": self.state_hash,            "freeze_id": self.freeze_id,            "metadata": self.metadata,        }         def link_freeze(self, freeze_id: str) -> None:        """Link snapshot to a freeze (mutable via this method)."""        # Note: This breaks frozen=True, but we need it for linking        import dataclasses        object.__setattr__(self, "freeze_id", freeze_id)`

---

## 6. `src/k501/core/freeze.py`

python

`""" Freeze: Sealed immutable record of Snapshot. A Freeze is the first governance boundary where mutable state becomes historical evidence. """ from dataclasses import dataclass, field from datetime import datetime from typing import Any, Dict, Optional from ..utils.ids import create_deterministic_id from ..utils.hashing import hash_content from .snapshot import Snapshot @dataclass(frozen=True) class Freeze:     """Sealed immutable record of a Snapshot."""         freeze_id: str    snapshot_id: str    created_at: datetime    content_hash: str    archive_id: Optional[str] = None    reason: str = ""    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        snapshot_id: str,        created_at: datetime,        content: Any,        reason: str = "",        metadata: Dict[str, Any] = {},    ) -> "Freeze":        """Create a new Freeze with deterministic ID."""        content_hash = hash_content(content)        content_str = f"{snapshot_id}:{created_at.isoformat()}:{content_hash}"        freeze_id = create_deterministic_id("freeze", content_str)                 return cls(            freeze_id=freeze_id,            snapshot_id=snapshot_id,            created_at=created_at,            content_hash=content_hash,            reason=reason,            metadata=metadata,        )         def to_dict(self) -> Dict[str, Any]:        """Convert to dictionary."""        return {            "freeze_id": self.freeze_id,            "snapshot_id": self.snapshot_id,            "created_at": self.created_at.isoformat(),            "content_hash": self.content_hash,            "archive_id": self.archive_id,            "reason": self.reason,            "metadata": self.metadata,        }         def link_archive(self, archive_id: str) -> None:        """Link freeze to an archive."""        import dataclasses        object.__setattr__(self, "archive_id", archive_id)`

---

## 7. `src/k501/core/state_object.py`

python

`""" StateObject: Universal memory primitive for K501-Aionarc. Contains evidence, lineage, trust, retrieval links, and provenance. """ from dataclasses import dataclass, field from datetime import datetime from enum import Enum from typing import Any, Dict, List, Optional from ..utils.ids import create_deterministic_id from ..utils.hashing import hash_content class ObjectType(Enum):     """Type of memory primitive."""    AXIOM = "axiom"    KERNEL = "kernel"    FRAME = "frame"    SNAPSHOT = "snapshot"    FREEZE = "freeze"    ARCHIVE = "archive"    CHUNK = "chunk"    EMBEDDING = "embedding"    PROOF = "proof"    AUDIT = "audit"    RECEIPT = "receipt"    CLAIM = "claim"    BELIEF = "belief"    NAMESPACE = "namespace"    POINTER = "pointer"    TIME_ANCHOR = "time_anchor" class ValidationStatus(Enum):     """Validation status of a state object."""    PENDING = "pending"    VALIDATED = "validated"    REJECTED = "rejected"    SUPERSEDED = "superseded" class BeliefStatus(Enum):     """Belief status for reasoning."""    UNKNOWN = "unknown"    CANDIDATE = "candidate"    ACCEPTED = "accepted"    CONTESTED = "contested"    REJECTED = "rejected" @dataclass class StateObject:     """Universal memory primitive for K501-Aionarc."""         state_id: str    axiom_id: str    namespace: str    version: str    object_type: ObjectType    origin: Dict[str, Optional[str]] = field(default_factory=dict)    lineage: Dict[str, List[str]] = field(default_factory=dict)    validation: Dict[str, Any] = field(default_factory=dict)    trust: Dict[str, Any] = field(default_factory=dict)    time: Dict[str, Any] = field(default_factory=dict)    retrieval: Dict[str, List[str]] = field(default_factory=dict)    provenance: Dict[str, Any] = field(default_factory=dict)    payload: Dict[str, Any] = field(default_factory=dict)    metadata: Dict[str, Any] = field(default_factory=dict)         @classmethod    def create(        cls,        axiom_id: str,        namespace: str,        object_type: ObjectType,        created_at: datetime,        payload: Any,        version: str = "1.0.0",        metadata: Dict[str, Any] = {},    ) -> "StateObject":        """Create a new StateObject with deterministic ID."""        content_hash = hash_content(payload)        content_str = f"{axiom_id}:{namespace}:{object_type.value}:{created_at.isoformat()}:{content_hash}"        state_id = create_deterministic_id("state", content_str)                 return cls(            state_id=state_id,            axiom_id=axiom_id,            namespace=namespace,            version=version,            object_type=object_type,            created_at=created_at,            payload={"content_hash": content_hash, "metadata": metadata},            metadata=metadata,        )         def to_dict(self) -> Dict[str, Any]:        """Convert to dictionary."""        return {            "state_id": self.state_id,            "axiom_id": self.axiom_id,            "namespace": self.namespace,            "version": self.version,            "object_type": self.object_type.value,            "origin": self.origin,            "lineage": self.lineage,            "validation": self.validation,            "trust": self.trust,            "time": self.time,            "retrieval": self.retrieval,            "provenance": self.provenance,            "payload": self.payload,            "metadata": self.metadata,        }         def to_json(self) -> str:        """Convert to JSON string."""        import json        return json.dumps(self.to_dict(), indent=2)         def add_lineage(self, relation: str, object_id: str) -> None:        """Add a lineage relationship."""        if relation not in self.lineage:            self.lineage[relation] = []        if object_id not in self.lineage[relation]:            self.lineage[relation].append(object_id)         def set_validation(self, proof_id: str, audit_id: str, status: ValidationStatus) -> None:        """Set validation metadata."""        self.validation = {            "proof_id": proof_id,            "audit_id": audit_id,            "status": status.value,        }         def set_belief(self, status: BeliefStatus, confidence: float, support_score: float) -> None:        """Set belief metadata."""        self.trust = {            "belief_status": status.value,            "confidence": confidence,            "support_score": support_score,        }`

---

## 8. `src/k501/core/lifecycle.py`

python

`""" Lifecycle: State transition matrix and validation. Defines allowed transitions between states and validates them. """ from dataclasses import dataclass from enum import Enum from typing import Dict, List, Set class State(Enum):     """State in the lifecycle."""    ACTIVE = "active"    FROZEN = "frozen"    ARCHIVED = "archived"    VALIDATED = "validated"    REJECTED = "rejected" @dataclass class StateTransition:     """Represents a state transition."""    from_state: State    to_state: State    object_type: str    reason: str = ""         def is_valid(self) -> bool:        """Check if this transition is allowed."""        allowed = TRANSITION_MATRIX.get(self.object_type, set())        return self.from_state in allowed and self.to_state in allowed # Transition matrix: allowed states for each object type TRANSITION_MATRIX: Dict[str, Set[State]] = {     "frame": {State.ACTIVE, State.FROZEN, State.ARCHIVED},    "snapshot": {State.ACTIVE, State.FROZEN},    "freeze": {State.FROZEN, State.ARCHIVED},    "archive": {State.ARCHIVED},    "proof": {State.VALIDATED, State.REJECTED},    "audit": {State.VALIDATED, State.REJECTED},    "claim": {State.ACTIVE, State.VALIDATED, State.REJECTED},    "belief": {State.CANDIDATE, State.ACCEPTED, State.CONTESTED, State.REJECTED}, } def validate_transition(     object_type: str,    from_state: State,    to_state: State, ) -> bool:     """Validate a state transition."""    allowed = TRANSITION_MATRIX.get(object_type, set())    return from_state in allowed and to_state in allowed def get_allowed_transitions(object_type: str) -> List[State]:     """Get all allowed states for an object type."""    return list(TRANSITION_MATRIX.get(object_type, set()))`

---

## 9. `src/k501/utils/__init__.py`

python

`"""K501 Utils Package""" from .ids import create_deterministic_id, create_hash_id from .hashing import hash_content __all__ = ["create_deterministic_id", "create_hash_id", "hash_content"]`

---

## 10. `src/k501/utils/ids.py`

python

`""" ID Generation: Deterministic and hash-based identifiers. Provides: - Deterministic IDs (content-based) - Hash-based IDs - Namespace-scoped IDs """ import hashlib import uuid from typing import Optional def create_hash_id(content: str) -> str:     """Create a hash-based ID from content."""    hash_bytes = hashlib.sha256(content.encode()).digest()    return hash_bytes.hex()[:16] def create_deterministic_id(     prefix: str,    content: str,    namespace: Optional[str] = None, ) -> str:     """    Create a deterministic ID from content.         Format: {prefix}:{namespace}:{hash}    """    if namespace:        content = f"{namespace}:{content}"         hash_bytes = hashlib.sha256(content.encode()).digest()    hash_str = hash_bytes.hex()[:24]         return f"{prefix}:{hash_str}" def create_namespace_id(namespace: str) -> str:     """Create a namespace-scoped ID."""    hash_bytes = hashlib.sha256(namespace.encode()).digest()    return f"ns:{hash_bytes.hex()[:16]}" def create_uuid() -> str:     """Create a random UUID (for non-deterministic use)."""    return str(uuid.uuid4())`

---

## 11. `src/k501/utils/hashing.py`

python

`""" Hashing: Content hashing utilities. Provides: - SHA-256 content hashing - Hash verification """ import hashlib from typing import Any def hash_content(content: Any) -> str:     """    Hash content using SHA-256.         Handles any Python object by converting to JSON string.    """    import json    if isinstance(content, str):        content_str = content    else:        content_str = json.dumps(content, sort_keys=True)         hash_bytes = hashlib.sha256(content_str.encode()).digest()    return hash_bytes.hex() def verify_hash(content: Any, expected_hash: str) -> bool:     """Verify content matches expected hash."""    actual_hash = hash_content(content)    return actual_hash == expected_hash`

---

## 12. `tests/unit/test_state_object.py`

python

`""" Unit tests for StateObject. Tests: - Round-trip serialization - Lineage attachment - Validation and belief setting """ import json from datetime import datetime from k501.core.state_object import StateObject, ObjectType, ValidationStatus, BeliefStatus def test_state_object_creation():     """Test StateObject creation with deterministic ID."""    created_at = datetime(2026, 6, 17, 0, 0, 0)         obj = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.FRAME,        created_at=created_at,        payload={"title": "Test Frame"},    )         assert obj.state_id.startswith("state:")    assert obj.axiom_id == "axiom:test"    assert obj.namespace == "research"    assert obj.object_type == ObjectType.FRAME    assert obj.version == "1.0.0" def test_state_object_roundtrip():     """Test round-trip serialization (dict -> obj -> dict)."""    created_at = datetime(2026, 6, 17, 0, 0, 0)         obj = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.FRAME,        created_at=created_at,        payload={"title": "Test Frame"},        metadata={"author": "test"},    )         # Convert to dict    obj_dict = obj.to_dict()         # Verify structure    assert "state_id" in obj_dict    assert "axiom_id" in obj_dict    assert "namespace" in obj_dict    assert "object_type" in obj_dict         # Convert to JSON and back    json_str = obj.to_json()    obj_dict2 = json.loads(json_str)         assert obj_dict == obj_dict2 def test_state_object_lineage():     """Test lineage attachment."""    created_at = datetime(2026, 6, 17, 0, 0, 0)         obj = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.FRAME,        created_at=created_at,        payload={"title": "Test"},    )         obj.add_lineage("derived_from", "snapshot:123")    obj.add_lineage("derived_from", "snapshot:456")    obj.add_lineage("ancestor", "frame:789")         assert obj.lineage["derived_from"] == ["snapshot:123", "snapshot:456"]    assert obj.lineage["ancestor"] == ["frame:789"] def test_state_object_validation():     """Test validation metadata."""    created_at = datetime(2026, 6, 17, 0, 0, 0)         obj = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.FRAME,        created_at=created_at,        payload={"title": "Test"},    )         obj.set_validation(        proof_id="proof:123",        audit_id="audit:456",        status=ValidationStatus.VALIDATED,    )         assert obj.validation["proof_id"] == "proof:123"    assert obj.validation["audit_id"] == "audit:456"    assert obj.validation["status"] == "validated" def test_state_object_belief():     """Test belief metadata."""    created_at = datetime(2026, 6, 17, 0, 0, 0)         obj = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.FRAME,        created_at=created_at,        payload={"title": "Test"},    )         obj.set_belief(        status=BeliefStatus.ACCEPTED,        confidence=0.95,        support_score=0.88,    )         assert obj.trust["belief_status"] == "accepted"    assert obj.trust["confidence"] == 0.95    assert obj.trust["support_score"] == 0.88`

---

## 13. `tests/unit/test_lineage.py`

python

`""" Unit tests for lineage reconstruction. Tests: - Lineage chain building - Ancestor traversal - Derived-from relationships """ from datetime import datetime from k501.core.state_object import StateObject, ObjectType from k501.core.lifecycle import validate_transition, State def test_lineage_chain():     """Test building a lineage chain."""    created_at = datetime(2026, 6, 17, 0, 0, 0)         # Create ancestors    ancestor = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.AXIOM,        created_at=created_at,        payload={"name": "Root"},    )         child = StateObject.create(        axiom_id="axiom:test",        namespace="research",        object_type=ObjectType.FRAME,        created_at=created_at,        payload={"name": "Child"},    )         child.add_lineage("derived_from", ancestor.state_id)    child.add_lineage("ancestor", ancestor.state_id)         assert child.lineage["derived_from"][0] == ancestor.state_id    assert child.lineage["ancestor"][0] == ancestor.state_id def test_transition_validation():     """Test state transition validation."""    # Frame can go from ACTIVE to FROZEN    assert validate_transition("frame", State.ACTIVE, State.FROZEN) is True         # Frame cannot go from ARCHIVED to ACTIVE    assert validate_transition("frame", State.ARCHIVED, State.ACTIVE) is False         # Archive is always ARCHIVED    assert validate_transition("archive", State.ARCHIVED, State.ARCHIVED) is True`

---

## 14. `tests/unit/test_integrity.py`

python

`""" Unit tests for hash verification. Tests: - Content hashing - Hash verification - Hash consistency """ from k501.utils.hashing import hash_content, verify_hash from k501.utils.ids import create_deterministic_id, create_hash_id def test_hash_content():     """Test content hashing."""    content = "test content"    hash1 = hash_content(content)    hash2 = hash_content(content)         assert hash1 == hash2    assert len(hash1) == 64  # SHA-256 hex length def test_hash_different_content():     """Test that different content produces different hashes."""    hash1 = hash_content("content 1")    hash2 = hash_content("content 2")         assert hash1 != hash2 def test_hash_verification():     """Test hash verification."""    content = "test content"    expected_hash = hash_content(content)         assert verify_hash(content, expected_hash) is True    assert verify_hash(content, "wrong_hash") is False def test_deterministic_id():     """Test deterministic ID generation."""    id1 = create_deterministic_id("frame", "test content")    id2 = create_deterministic_id("frame", "test content")         assert id1 == id2    assert id1.startswith("frame:")`

---

## Summary

You now have:

1. ✅ **Core primitives** (`axiom.py`, `kernel.py`, `frame.py`, `snapshot.py`, `freeze.py`, `state_object.py`, `lifecycle.py`)
    
2. ✅ **Stable ID generation** (`ids.py`, `hashing.py`)
    
3. ✅ **Unit tests** (`test_state_object.py`, `test_lineage.py`, `test_integrity.py`)
    

This completes **Phase 1, Step 1** of the K501-Aionarc implementation.

**Next step:** Run tests with `make test` to verify everything works, then proceed to **Phase 2: Evidence Store**.