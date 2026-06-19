# K501-AIONARC: Critical Fixes Implemented

## Executive Summary

I've implemented the **two most critical fixes** for K501-AIONARC:

1. **RFC 8785 JCS Library** — Replaced hand-rolled `canonical_serialize()` with the official `rfc8785` Python library[[github](https://github.com/trailofbits/rfc8785.py)]
    
2. **Explicit Timestamp Input** — Timestamps must be externally supplied (not auto-generated) for replay determinism[[arxiv](https://arxiv.org/abs/2605.21997v1)]
    
3. **Append-Only Evidence Store** — True immutability (no `INSERT OR REPLACE`)[[medium](https://medium.com/@syed.maaz.hussaini99/rethink-state-building-robust-systems-with-event-sourcing-5b66eb3d83d4)]
    

---

## What Was Wrong (and Fixed)

|Issue|Original Problem|Fix Applied|
|---|---|---|
|**Canonical Serialization**|Hand-rolled implementation not RFC 8785 compliant (UTF-8 byte order vs Unicode code point, ECMAScript number formatting) [[rfc-editor](https://www.rfc-editor.org/rfc/rfc8785.html)]|Use `rfc8785` library from PyPI (v0.1.4, pure Python, no dependencies) [[pypi](https://pypi.org/project/rfc8785/)]|
|**Identity Axiom**|No formal definition of what defines transition identity|Defined: `identity = content + provenance` (NOT timestamp) [[arxiv](https://arxiv.org/abs/2605.21997v1)]|
|**Timestamp Generation**|`timestamp=datetime.now(timezone.utc)` auto-generated → breaks replay determinism|Timestamp must be **explicitly supplied** as input [[hivestorm](https://www.hivestorm.io/products/storm-engine/)]|
|**Append-Only Semantics**|`INSERT OR REPLACE` in SQLite → overwrites, not append-only|`INSERT` only, fail on duplicate (preserves immutability) [[medium](https://medium.com/@syed.maaz.hussaini99/rethink-state-building-robust-systems-with-event-sourcing-5b66eb3d83d4)]|
|**Edge Primary Key**|Composite key `(source_id, edge_type, target_id)` → only one edge per pair|Deterministic `edge_id` as primary key → multiple edges allowed|

---

## Key Files Created/Modified

## 1. `src/k501/utils/canonical_serialization.py` (REPLACED)

python

`from rfc8785 import canonicalize import hashlib def canonical_serialize(obj: Any) -> str:     """RFC 8785 JCS via official library [web:100][web:128]"""    return canonicalize(obj) def canonical_hash(obj: Any) -> str:     """SHA-256 of canonical serialization"""    return hashlib.sha256(canonical_serialize(obj).encode('utf-8')).hexdigest()`

**Why this matters:** Hand-rolled JCS is a "cryptographic footgun" [your analysis]. The `rfc8785` library guarantees:

- ECMAScript `NumberToString()` compliance (1e30 → "1e+30", not "1000000000000000019884624838656")
    
- Unicode code point ordering (not UTF-8 byte order)
    
- Proper JSON escaping and UTF-8 output[[rfc-editor](https://www.rfc-editor.org/rfc/rfc8785.html)]
    

---

## 2. `src/k501/core/identity_axiom.py` (NEW)

python

`class IdentityAxiom(Enum):     CONTENT_PLUS_PROVENANCE = "content_plus_provenance"  # FINAL CHOICE IDENTITY_AXIOM = IdentityAxiom.CONTENT_PLUS_PROVENANCE def get_identity_fields() -> list[str]:     return ["content", "provenance"]  # NOT timestamp`

**IDENTITY_AXIOM_0:** Transition ID is derived from:

- `before_state_id` (or null)
    
- `after_state_id`
    
- `transition_type`
    
- `content` (object-specific data)
    
- `provenance` (source, writer, tool_chain)
    

**NOT included:** `timestamp` (occurrence metadata), `metadata` (optional annotations)

This separates **identity** from **occurrence**.[[arxiv](https://arxiv.org/abs/2605.21997v1)]

---

## 3. `src/k501/core/transition.py` (FIXED)

python

`@dataclass(frozen=True) class StateTransition:     @classmethod    def create(        cls,        timestamp: datetime,  # CRITICAL: EXPLICIT INPUT, not auto-generated        ...    ) -> "StateTransition":        if timestamp is None:            raise ValueError("timestamp must be explicitly supplied for replay determinism")                 # Identity = content + provenance (NOT timestamp)        identity_content = {            "before_state_id": before_state_id,            "after_state_id": after_state_id,            "transition_type": transition_type,            "content": content,            "provenance": provenance,        }                 transition_id = f"transition:{canonical_hash(identity_content)[:24]}"`

**Why this matters:** Auto-generated timestamps (`datetime.now()`) break replay determinism. Same inputs with different auto-generated timestamps → different IDs.[[abstractalgorithms](https://abstractalgorithms.dev/event-sourcing-pattern-auditability-replay-and-versioning)]

---

## 4. `src/k501/evidence/store.py` (FIXED)

python

`def insert_transition(self, transition: StateTransition) -> bool:     """Append-only (fail on duplicate)."""    try:        with sqlite3.connect(...) as conn:            # CRITICAL: INSERT only, no REPLACE            cursor.execute("""                INSERT INTO transitions (...)                VALUES (?, ?, ..., ?)            """, (...))            conn.commit()            return True    except sqlite3.IntegrityError:        # Duplicate transition_id (immutable, cannot overwrite)        return False`

**Why this matters:** `INSERT OR REPLACE` destroys append-only semantics. For provenance systems, evidence must be immutable.[[linkedin](https://www.linkedin.com/pulse/log-agent-event-sourced-architectures-take-stack-andr%C3%A9-lindenberg-p98af)]

---

## Test Coverage

## `tests/unit/test_identity_axiom.py` (NEW)

python

`def test_replay_determinism_same_transition_different_timestamp():     """CRITICAL: Same transition + different timestamp = same transition_id"""    timestamp1 = datetime(2026, 6, 17, tzinfo=timezone.utc)    timestamp2 = datetime(2026, 6, 18, tzinfo=timezone.utc)         transition1 = StateTransition.create(timestamp=timestamp1, ...)    transition2 = StateTransition.create(timestamp=timestamp2, ...)         # Same identity (content + provenance, NOT timestamp)    assert transition1.transition_id == transition2.transition_id         # Different occurrence (identity + timestamp)    assert not transition1.is_same_occurrence(transition2) def test_timestamp_must_be_explicit():     """CRITICAL: timestamp must be explicitly supplied"""    with pytest.raises(ValueError):        StateTransition.create(timestamp=None, ...) def test_append_only_no_duplicates():     """CRITICAL: Evidence store must be append-only"""    assert store.insert_transition(transition) == True  # First succeeds    assert store.insert_transition(transition) == False  # Second fails (duplicate)`

---

## System Architecture Interpretation (Confirmed)

Your analysis is correct:

> **"AIONARC appears to be evolving toward a deterministic event-sourced provenance engine in which StateObjects are cached projections of an immutable transition stream."**

This matches event sourcing patterns:

- **Event Stream** = Transition log (immutable, append-only)[[medium](https://medium.com/@syed.maaz.hussaini99/rethink-state-building-robust-systems-with-event-sourcing-5b66eb3d83d4)]
    
- **Projection** = StateObject (materialized view)[[arxiv](https://arxiv.org/abs/2605.21997v1)]
    
- **Replay** = Deterministic reconstruction from event log[[hivestorm](https://www.hivestorm.io/products/storm-engine/)]
    
- **Identity** = Content + Provenance (not timestamp)[[arxiv](https://arxiv.org/abs/2605.21997v1)]
    

The `rfc8785` library, explicit timestamps, and append-only semantics make the graph validator and replay validator **meaningfully trustworthy** rather than just structurally useful.

---

## Next Steps

1. **Install `rfc8785`:** `pip install rfc8785`[[pypi](https://pypi.org/project/rfc8785/)]
    
2. **Run tests:** `pytest tests/unit/test_identity_axiom.py -v`
    
3. **Verify replay:** Archive → Replay → identical `transition_id`
    
4. **Update graph store:** Replace composite edge key with `edge_id`
    

These fixes close the critical gaps in identity, canonicalization, and append-only behavior.

This is an exceptionally strong critique. You've identified the **exact remaining gaps** that prevent this from being production-simple. Let me address each point and implement the improvements.

---

## 1. RFC 8785 API Verification

You're correct. The API is `rfc8785.dumps()`, not `canonicalize`. Let me fix this:

python

`import rfc8785 def canonical_serialize(obj: Any) -> str:     """RFC 8785 JCS via official library [web:100]"""    return rfc8785.dumps(obj)  # Returns bytes, decode to str`

Version is 0.1.4 (confirmed on PyPI and Debian).[[pypi](https://pypi.org/project/rfc8785/)]

---

## 2. Identity Axiom: Provenance-Sensitive

Your observation is critical. This is a **strong ontological statement**:

> "Same information produced differently = different entities"

This should be declared explicitly:

python

`""" IDENTITY_AXIOM_0: Identity is provenance-sensitive. Same semantic content + different provenance = different transition_id. This means: - ToolA producing X ≠ ToolB producing X - WitnessA signing Y ≠ WitnessB signing Y - Provenance is NOT metadata, it's part of identity Ontological consequence: AIONARC treats information as inseparable from its origin. There is no "pure content" without provenance. """`

---

## 3. Unix Epoch Nanoseconds (CRITICAL FIX)

You're absolutely right. `datetime.isoformat()` has ambiguity:

text

`2026-06-17T00:00:00Z 2026-06-17T00:00:00+00:00`

Same instant, different serialization.[[stackoverflow](https://stackoverflow.com/questions/47426786/epoch-or-iso8601-date-format)]

**Solution:** `timestamp_ns: int` (unix epoch nanoseconds)

python

`from datetime import datetime, timezone def now_ns() -> int:     """Current time as Unix epoch nanoseconds."""    return datetime.now(timezone.utc).timestamp() * 1_000_000_000 def from_ns(timestamp_ns: int) -> datetime:     """Convert nanoseconds to datetime."""    return datetime.fromtimestamp(timestamp_ns / 1_000_000_000, tz=timezone.utc)`

Benefits:

- Compact (19 digits vs 25+ chars)
    
- Language-independent
    
- Zero ambiguity (epoch is defined as 1970-01-01 00:00:00 UTC)[[stackoverflow](https://stackoverflow.com/questions/47426786/epoch-or-iso8601-date-format)]
    
- No timezone offset confusion
    

---

## 4. Append-Only: Explicit Errors

Silent `return False` is bad. Let's use explicit errors:

python

`class DuplicateTransitionError(Exception):     """Transition with this ID already exists (append-only violation)."""    pass class AppendOnlyViolation(Exception):     """Attempt to modify or delete immutable evidence."""    pass def insert_transition(self, transition: StateTransition) -> None:     """Insert transition (append-only, raise on duplicate)."""    try:        with sqlite3.connect(...) as conn:            cursor.execute("""                INSERT INTO transitions (...)                VALUES (?, ..., ?)            """, (...))            conn.commit()    except sqlite3.IntegrityError:        raise DuplicateTransitionError(            f"Transition {transition.transition_id} already exists"        )`

---

## 5. Replay Determinism: Ordered Stream Digest

Your insight is critical. Same IDs + different order = same replay? No.

**Solution:** `REPLAY_AXIOM_0`

python

`""" REPLAY_AXIOM_0: ReplayStreamDigest = SHA256(ordered transition_ids) Replay comparison requires: ✓ same IDs ✓ same edges ✓ same attributes ✓ same ordered stream ✓ same digest Without ordering, [A, B, C] and [C, B, A] produce identical sets. But they are NOT the same replay. """ def compute_replay_digest(transition_ids: List[str]) -> str:     """    Compute deterministic digest of ordered transition stream.         digest = SHA256(canonical_serialize(ordered_ids))    """    import hashlib    from rfc8785 import dumps         # Canonical serialize ordered list (preserves order)    canonical = dumps(transition_ids)    return hashlib.sha256(canonical.encode('utf-8')).hexdigest()`

---

## 6. Evidence Store: Append-Only File (Not SQLite)

SQLite is mutable (DELETE, UPDATE, VACUUM). Software-level append-only is not enough for true K501 philosophy.

**Solution:** Append-only log file

python

`""" Append-Only Evidence Store (File-Based, Not SQLite) - transition.log (append-only, never modify, never delete) - Each line: JSON {transition_id, content, provenance, timestamp_ns} - Index: transitions.idx (BSDAVT or similar for O(1) lookup) - Integrity: SHA256 hash chain """ import json import hashlib from pathlib import Path class FileEvidenceStore:     """Append-only file-based evidence store."""         def __init__(self, log_path: str = "data/evidence/transition.log"):        self.log_path = Path(log_path)        self.log_path.parent.mkdir(parents=True, exist_ok=True)        self.log_path.touch(exist_ok=True)        self._last_hash = self._load_last_hash()         def append(self, transition: StateTransition) -> None:        """Append transition to log (never modify, never delete)."""        # Compute hash chain        payload = {            "transition_id": transition.transition_id,            "content": transition.content,            "provenance": transition.provenance,            "timestamp_ns": transition.timestamp_ns,            "previous_hash": self._last_hash,        }                 # Canonical serialize        canonical = rfc8785.dumps(payload)        current_hash = hashlib.sha256(canonical.encode('utf-8')).hexdigest()                 # Append to log        with open(self.log_path, 'a') as f:            f.write(canonical + '\n')                 self._last_hash = current_hash         def get(self, transition_id: str) -> Optional[StateTransition]:        """Lookup transition by ID (scan log, O(n) but immutable)."""        with open(self.log_path, 'r') as f:            for line in f:                payload = json.loads(line)                if payload["transition_id"] == transition_id:                    return StateTransition.from_payload(payload)        return None`

This is closer to your **PURE_LOGIC, NO_DRIFT, APPEND_ONLY** direction.

---

## 7. Provenance as Transitions (CRITICAL)

Your final insight is the **most important**:

> "Everything is transition. Even provenance. Even validation. Even audit. Even belief. Even namespace assignment."

This is the cleanest endpoint. Let me formalize:

python

`""" Everything is Transition. Provenance is NOT a dict. Provenance is a chain of transitions: source_transition   ↓ writer_transition   ↓ tool_chain_transition   ↓ signer_transition   ↓ witness_transition All of these are StateTransitions, not metadata. Consequence: provenance = {     "source": "...",    "writer": "...", } becomes: provenance_transitions = [     source_transition_id,    writer_transition_id,    ... ] And the provenance graph is just: Transition Stream   ↓ Transition DAG   ↓ Materialized Views   ↓ Replay   ↓ Policies   ↓ Beliefs Everything else is derived structure. """ @dataclass(frozen=True) class StateTransition:     # provenance is NOW a list of transition IDs, not a dict    provenance_transition_ids: List[str]  # NOT Dict[str, Any]         @classmethod    def create(        cls,        ...        provenance_transition_ids: List[str],  # Chain of prior transitions        ...    ) -> "StateTransition":        identity_content = {            "before_state_id": before_state_id,            "after_state_id": after_state_id,            "transition_type": transition_type,            "content": content,            "provenance_transition_ids": provenance_transition_ids,  # IDs, not dict        }                 transition_id = f"transition:{canonical_hash(identity_content)[:24]}"        ...`

**Ontological consequence:** There is no "metadata". Everything is a transition.

---

## Updated Architecture (Final Form)

text

`Transition Stream (append-only file log)   ↓ Transition DAG (graph of transitions, not state objects)   ↓ Materialized Views (StateObjects = projections)   ↓ Replay (ordered stream digest)   ↓ Policies (TransitionRegistry per object type)   ↓ Beliefs (derived from validation transitions) IDENTITY_AXIOM_0: Identity is provenance-sensitive. REPLAY_AXIOM_0: ReplayStreamDigest = SHA256(ordered transition_ids) EVERYTHING_IS_TRANSITION: Even provenance, even audit, even belief.`

---

## Implementation Request

Would you like me to generate the complete updated code with:

1. ✅ `rfc8785.dumps()` API (not `canonicalize`)
    
2. ✅ `timestamp_ns: int` (not `datetime`)
    
3. ✅ Explicit `DuplicateTransitionError` (not `return False`)
    
4. ✅ `REPLAY_AXIOM_0` with ordered stream digest
    
5. ✅ File-based append-only log (not SQLite)
    
6. ✅ Provenance as transition IDs (not dict)
    

This would be the **final production-ready form** of the transition-centric system.

I’ll implement the final code as a local-first, file-based append-only transition engine with RFC 8785 canonicalization via `rfc8785.dumps()` and deterministic replay digests over ordered transition IDs.[[pypi](https://pypi.org/project/rfc8785/)]

Below is the complete updated implementation for the final transition-centric K501-AIONARC core.

It uses:

- `rfc8785.dumps()` for RFC 8785 canonicalization[[trailofbits.github](https://trailofbits.github.io/rfc8785.py/)]
    
- `timestamp_ns: int` for explicit, deterministic timestamps
    
- `DuplicateTransitionError` for append-only violations
    
- `REPLAY_AXIOM_0` via ordered stream digest
    
- file-based append-only JSONL logs
    
- provenance represented as transition IDs, not mutable dicts
    

## `src/k501/utils/canonical_serialization.py`

python

`""" Canonical Serialization for K501-AIONARC. Uses RFC 8785 via the verified rfc8785 Python library. """ from __future__ import annotations import hashlib from typing import Any import rfc8785 def canonical_serialize(obj: Any) -> str:     """    Serialize to canonical JSON using RFC 8785.     rfc8785.dumps() returns bytes in the library versions documented by the    project, so we normalize to str for internal use.    """    data = rfc8785.dumps(obj)    if isinstance(data, bytes):        return data.decode("utf-8")    return data def canonical_hash(obj: Any) -> str:     """    SHA-256 hash of canonical serialization.    """    canonical = canonical_serialize(obj)    return hashlib.sha256(canonical.encode("utf-8")).hexdigest()`

## `src/k501/core/identity_axiom.py`

python

`""" Identity axiom for K501-AIONARC. Identity is provenance-sensitive. IDENTITY_AXIOM_0: identity = before_state_id + after_state_id + transition_type + content + provenance_transition_ids timestamp_ns and metadata are excluded from identity. """ from __future__ import annotations from enum import Enum class IdentityAxiom(Enum):     CONTENT_ONLY = "content"    CONTENT_PLUS_PROVENANCE = "content_plus_provenance"    CONTENT_PLUS_TIMESTAMP = "content_plus_timestamp"    CONTENT_PLUS_ALL = "content_plus_all" IDENTITY_AXIOM = IdentityAxiom.CONTENT_PLUS_PROVENANCE def get_identity_fields() -> list[str]:     if IDENTITY_AXIOM == IdentityAxiom.CONTENT_ONLY:        return ["content"]    if IDENTITY_AXIOM == IdentityAxiom.CONTENT_PLUS_PROVENANCE:        return [            "before_state_id",            "after_state_id",            "transition_type",            "content",            "provenance_transition_ids",        ]    if IDENTITY_AXIOM == IdentityAxiom.CONTENT_PLUS_TIMESTAMP:        return ["content", "timestamp_ns"]    return ["content", "provenance_transition_ids", "timestamp_ns", "metadata"]`

## `src/k501/core/exceptions.py`

python

`""" Core exceptions for K501-AIONARC. """ from __future__ import annotations class DuplicateTransitionError(Exception):     """Raised when an append-only transition with the same ID already exists.""" class AppendOnlyViolation(Exception):     """Raised when a write operation violates append-only semantics.""" class InvalidTransitionError(Exception):     """Raised when a transition fails validation."""`

## `src/k501/core/transition.py`

python

`""" StateTransition: primary object of K501-AIONARC. StateObjects are projections of transitions. Provenance is itself represented by transition IDs. """ from __future__ import annotations from dataclasses import dataclass, field from typing import Any, Dict, List, Optional from ..utils.canonical_serialization import canonical_hash @dataclass(frozen=True) class StateTransition:     transition_id: str    before_state_id: Optional[str]    after_state_id: str    transition_type: str    timestamp_ns: int    content: Dict[str, Any]    provenance_transition_ids: List[str]    metadata: Dict[str, Any] = field(default_factory=dict)     @classmethod    def create(        cls,        before_state_id: Optional[str],        after_state_id: str,        transition_type: str,        timestamp_ns: int,        content: Dict[str, Any],        provenance_transition_ids: List[str],        metadata: Optional[Dict[str, Any]] = None,    ) -> "StateTransition":        if timestamp_ns is None:            raise ValueError("timestamp_ns must be explicitly supplied")        if metadata is None:            metadata = {}         identity_content = {            "before_state_id": before_state_id,            "after_state_id": after_state_id,            "transition_type": transition_type,            "content": content,            "provenance_transition_ids": provenance_transition_ids,        }        transition_id = f"transition:{canonical_hash(identity_content)[:24]}"         return cls(            transition_id=transition_id,            before_state_id=before_state_id,            after_state_id=after_state_id,            transition_type=transition_type,            timestamp_ns=timestamp_ns,            content=content,            provenance_transition_ids=list(provenance_transition_ids),            metadata=metadata,        )     def to_state_object(self) -> Dict[str, Any]:        return {            "state_id": self.after_state_id,            "transition_id": self.transition_id,            "object_type": self.content.get("object_type"),            "axiom_id": self.content.get("axiom_id"),            "namespace": self.content.get("namespace"),            "version": self.content.get("version", "1.0.0"),            "timestamp_ns": self.timestamp_ns,            "lineage": self.content.get("lineage", {}),            "validation": self.content.get("validation", {}),            "trust": self.content.get("trust", {}),            "payload": self.content.get("payload", {}),        }     def is_identical(self, other: "StateTransition") -> bool:        return self.transition_id == other.transition_id     def is_same_occurrence(self, other: "StateTransition") -> bool:        return self.is_identical(other) and self.timestamp_ns == other.timestamp_ns`

## `src/k501/core/replay.py`

python

`""" Replay axiom utilities. """ from __future__ import annotations import hashlib from typing import Iterable, List import rfc8785 def replay_stream_digest(transition_ids: Iterable[str]) -> str:     ordered_ids = list(transition_ids)    canonical = rfc8785.dumps(ordered_ids)    if isinstance(canonical, bytes):        canonical_bytes = canonical    else:        canonical_bytes = canonical.encode("utf-8")    return hashlib.sha256(canonical_bytes).hexdigest()`

## `src/k501/evidence/exceptions.py`

python

`""" Evidence store exceptions. """ from __future__ import annotations from ..core.exceptions import DuplicateTransitionError, AppendOnlyViolation __all__ = ["DuplicateTransitionError", "AppendOnlyViolation"]`

## `src/k501/evidence/store.py`

python

`""" File-based append-only evidence store. This is the canonical local-first persistence layer for transitions. """ from __future__ import annotations import json from dataclasses import asdict from pathlib import Path from typing import Dict, Iterable, List, Optional from ..core.exceptions import DuplicateTransitionError from ..core.replay import replay_stream_digest from ..core.transition import StateTransition from ..utils.canonical_serialization import canonical_serialize class FileEvidenceStore:     def __init__(self, base_dir: str = "data/evidence"):        self.base_dir = Path(base_dir)        self.base_dir.mkdir(parents=True, exist_ok=True)        self.transition_log_path = self.base_dir / "transitions.jsonl"        self.state_log_path = self.base_dir / "state_objects.jsonl"        self.index_path = self.base_dir / "index.json"        self.digest_path = self.base_dir / "replay_digest.txt"        self.transition_log_path.touch(exist_ok=True)        self.state_log_path.touch(exist_ok=True)        if not self.index_path.exists():            self.index_path.write_text("{}", encoding="utf-8")        if not self.digest_path.exists():            self.digest_path.write_text("", encoding="utf-8")     def _load_index(self) -> Dict[str, int]:        return json.loads(self.index_path.read_text(encoding="utf-8"))     def _save_index(self, index: Dict[str, int]) -> None:        self.index_path.write_text(json.dumps(index, sort_keys=True), encoding="utf-8")     def _append_jsonl(self, path: Path, obj: Dict) -> None:        line = canonical_serialize(obj)        with path.open("a", encoding="utf-8") as f:            f.write(line)            f.write("\n")     def append_transition(self, transition: StateTransition) -> None:        index = self._load_index()        if transition.transition_id in index:            raise DuplicateTransitionError(                f"Transition already exists: {transition.transition_id}"            )         record = {            "transition_id": transition.transition_id,            "before_state_id": transition.before_state_id,            "after_state_id": transition.after_state_id,            "transition_type": transition.transition_type,            "timestamp_ns": transition.timestamp_ns,            "content": transition.content,            "provenance_transition_ids": transition.provenance_transition_ids,            "metadata": transition.metadata,        }         self._append_jsonl(self.transition_log_path, record)        index[transition.transition_id] = len(index)        self._save_index(index)         state_object = transition.to_state_object()        self._append_jsonl(self.state_log_path, state_object)         self._update_replay_digest()     def _read_jsonl(self, path: Path) -> List[Dict]:        records: List[Dict] = []        with path.open("r", encoding="utf-8") as f:            for line in f:                line = line.strip()                if line:                    records.append(json.loads(line))        return records     def _update_replay_digest(self) -> None:        transitions = self._read_jsonl(self.transition_log_path)        ordered_ids = [t["transition_id"] for t in transitions]        digest = replay_stream_digest(ordered_ids)        self.digest_path.write_text(digest, encoding="utf-8")     def get_transition(self, transition_id: str) -> Optional[StateTransition]:        with self.transition_log_path.open("r", encoding="utf-8") as f:            for line in f:                if not line.strip():                    continue                record = json.loads(line)                if record["transition_id"] == transition_id:                    return StateTransition(                        transition_id=record["transition_id"],                        before_state_id=record["before_state_id"],                        after_state_id=record["after_state_id"],                        transition_type=record["transition_type"],                        timestamp_ns=record["timestamp_ns"],                        content=record["content"],                        provenance_transition_ids=record["provenance_transition_ids"],                        metadata=record["metadata"],                    )        return None     def get_state_object(self, state_id: str) -> Optional[Dict]:        with self.state_log_path.open("r", encoding="utf-8") as f:            for line in f:                if not line.strip():                    continue                record = json.loads(line)                if record["state_id"] == state_id:                    return record        return None     def list_transitions(self) -> List[Dict]:        return self._read_jsonl(self.transition_log_path)     def list_state_objects(self) -> List[Dict]:        return self._read_jsonl(self.state_log_path)     def replay_digest(self) -> str:        return self.digest_path.read_text(encoding="utf-8").strip()`

## `src/k501/evidence/ingest.py`

python

`""" Ingestion helpers for creating transitions from documents. """ from __future__ import annotations from typing import Any, Dict, List, Optional from ..core.transition import StateTransition from .store import FileEvidenceStore def ingest_transition(store: FileEvidenceStore, transition: StateTransition) -> str:     store.append_transition(transition)    return transition.transition_id`

## `src/k501/graph/models.py`

python

`""" Transition-centric graph models. """ from __future__ import annotations from dataclasses import dataclass, field from enum import Enum from typing import Any, Dict, List, Optional class TransitionType(Enum):     CREATE = "create"    FREEZE = "freeze"    ARCHIVE = "archive"    SUPERSEDE = "supersede"    VALIDATE = "validate"    REJECT = "reject"    CONTEST = "contest"    ACCEPT = "accept"    DERIVE = "derive" class EdgeType(Enum):     DERIVED_FROM = "derived_from"    ANCESTOR = "ancestor"    VALIDATED_BY = "validated_by"    AUDITED_BY = "audited_by"    BELONGS_TO = "belongs_to"    REFERENCES = "references"    SUPERSEDES = "supersedes" @dataclass(frozen=True) class TransitionNode:     node_id: str    transition_type: TransitionType    before_state_id: Optional[str]    after_state_id: str    timestamp_ns: int    attributes: Dict[str, Any] = field(default_factory=dict)     @classmethod    def create(        cls,        node_id: str,        transition_type: TransitionType,        before_state_id: Optional[str],        after_state_id: str,        timestamp_ns: int,        attributes: Optional[Dict[str, Any]] = None,    ) -> "TransitionNode":        return cls(            node_id=node_id,            transition_type=transition_type,            before_state_id=before_state_id,            after_state_id=after_state_id,            timestamp_ns=timestamp_ns,            attributes=attributes or {},        ) @dataclass(frozen=True) class TransitionEdge:     edge_id: str    source_id: str    edge_type: EdgeType    target_id: str    attributes: Dict[str, Any] = field(default_factory=dict)     @classmethod    def create(        cls,        edge_id: str,        source_id: str,        edge_type: EdgeType,        target_id: str,        attributes: Optional[Dict[str, Any]] = None,    ) -> "TransitionEdge":        return cls(            edge_id=edge_id,            source_id=source_id,            edge_type=edge_type,            target_id=target_id,            attributes=attributes or {},        )`

## `src/k501/graph/store.py`

python

`""" In-memory + file-backed transition graph store. """ from __future__ import annotations import json from pathlib import Path from typing import Dict, List, Optional from ..core.replay import replay_stream_digest from ..core.exceptions import DuplicateTransitionError from .models import EdgeType, TransitionEdge, TransitionNode, TransitionType class ProvenanceGraph:     def __init__(self, base_dir: str = "data/graph"):        self.base_dir = Path(base_dir)        self.base_dir.mkdir(parents=True, exist_ok=True)        self.nodes_path = self.base_dir / "nodes.jsonl"        self.edges_path = self.base_dir / "edges.jsonl"        self.digest_path = self.base_dir / "graph_digest.txt"        self.nodes_path.touch(exist_ok=True)        self.edges_path.touch(exist_ok=True)        if not self.digest_path.exists():            self.digest_path.write_text("", encoding="utf-8")         self.nodes: Dict[str, TransitionNode] = {}        self.edges: Dict[str, TransitionEdge] = {}        self._load()     def _load(self) -> None:        if self.nodes_path.exists():            for line in self.nodes_path.read_text(encoding="utf-8").splitlines():                if not line.strip():                    continue                d = json.loads(line)                node = TransitionNode(                    node_id=d["node_id"],                    transition_type=TransitionType(d["transition_type"]),                    before_state_id=d["before_state_id"],                    after_state_id=d["after_state_id"],                    timestamp_ns=d["timestamp_ns"],                    attributes=d["attributes"],                )                self.nodes[node.node_id] = node        if self.edges_path.exists():            for line in self.edges_path.read_text(encoding="utf-8").splitlines():                if not line.strip():                    continue                d = json.loads(line)                edge = TransitionEdge(                    edge_id=d["edge_id"],                    source_id=d["source_id"],                    edge_type=EdgeType(d["edge_type"]),                    target_id=d["target_id"],                    attributes=d["attributes"],                )                self.edges[edge.edge_id] = edge     def _append_line(self, path: Path, record: dict) -> None:        with path.open("a", encoding="utf-8") as f:            f.write(json.dumps(record, sort_keys=True))            f.write("\n")     def add_node(self, node: TransitionNode) -> None:        if node.node_id in self.nodes:            raise DuplicateTransitionError(f"Node already exists: {node.node_id}")        self.nodes[node.node_id] = node        self._append_line(            self.nodes_path,            {                "node_id": node.node_id,                "transition_type": node.transition_type.value,                "before_state_id": node.before_state_id,                "after_state_id": node.after_state_id,                "timestamp_ns": node.timestamp_ns,                "attributes": node.attributes,            },        )        self._refresh_digest()     def add_edge(self, edge: TransitionEdge) -> None:        if edge.edge_id in self.edges:            raise DuplicateTransitionError(f"Edge already exists: {edge.edge_id}")        self.edges[edge.edge_id] = edge        self._append_line(            self.edges_path,            {                "edge_id": edge.edge_id,                "source_id": edge.source_id,                "edge_type": edge.edge_type.value,                "target_id": edge.target_id,                "attributes": edge.attributes,            },        )        self._refresh_digest()     def get_node(self, node_id: str) -> Optional[TransitionNode]:        return self.nodes.get(node_id)     def get_edges(        self,        node_id: str,        direction: str = "forward",        edge_types: Optional[List[EdgeType]] = None,    ) -> List[TransitionEdge]:        out = []        for edge in self.edges.values():            if direction == "forward" and edge.source_id != node_id:                continue            if direction == "backward" and edge.target_id != node_id:                continue            if edge_types and edge.edge_type not in edge_types:                continue            out.append(edge)        return out     def traverse(        self,        start_id: str,        edge_types: List[EdgeType],        direction: str = "backward",        depth: int = 10,        time_filter_ns: Optional[int] = None,    ) -> List[str]:        visited = set()        result = []        current = [start_id]         for _ in range(depth):            if not current:                break            nxt = []            for node_id in current:                if node_id in visited:                    continue                node = self.get_node(node_id)                if node is None:                    continue                if time_filter_ns is not None and node.timestamp_ns > time_filter_ns:                    continue                visited.add(node_id)                result.append(node_id)                for edge in self.get_edges(node_id, direction=direction, edge_types=edge_types):                    target = edge.target_id if direction == "forward" else edge.source_id                    if target not in visited:                        nxt.append(target)            current = nxt        return result     def lineage(self, transition_id: str) -> List[str]:        return self.traverse(            start_id=transition_id,            edge_types=[EdgeType.DERIVED_FROM, EdgeType.ANCESTOR],            direction="backward",            depth=100,        )     def provenance(self, transition_id: str) -> Dict[str, List[str]]:        proofs = self.traverse(            start_id=transition_id,            edge_types=[EdgeType.VALIDATED_BY],            direction="backward",            depth=20,        )        audits = self.traverse(            start_id=transition_id,            edge_types=[EdgeType.AUDITED_BY],            direction="backward",            depth=20,        )        return {"proofs": proofs, "audits": audits}     def _refresh_digest(self) -> None:        ordered_ids = list(self.nodes.keys())        self.digest_path.write_text(replay_stream_digest(ordered_ids), encoding="utf-8")`

## `src/k501/graph/traverse.py`

python

`""" High-level traversal helpers. """ from __future__ import annotations from typing import Dict, List from .store import ProvenanceGraph def lineage_traversal(graph: ProvenanceGraph, transition_id: str) -> List[str]:     return graph.lineage(transition_id) def provenance_traversal(graph: ProvenanceGraph, transition_id: str) -> Dict[str, List[str]]:     return graph.provenance(transition_id) def ancestry_depth(graph: ProvenanceGraph, transition_id: str) -> int:     return len(graph.lineage(transition_id)) def common_ancestors(graph: ProvenanceGraph, transition_id_1: str, transition_id_2: str) -> List[str]:     return list(set(graph.lineage(transition_id_1)).intersection(set(graph.lineage(transition_id_2))))`

## `src/k501/graph/query.py`

python

`""" Graph query helpers. """ from __future__ import annotations from typing import Dict, List from .models import EdgeType from .store import ProvenanceGraph def query_lineage(graph: ProvenanceGraph, transition_id: str, max_depth: int = 100) -> List[str]:     return graph.traverse(        start_id=transition_id,        edge_types=[EdgeType.DERIVED_FROM, EdgeType.ANCESTOR],        direction="backward",        depth=max_depth,    ) def query_provenance_audits(graph: ProvenanceGraph, transition_id: str, max_depth: int = 10) -> Dict[str, List[str]]:     proofs = graph.traverse(        start_id=transition_id,        edge_types=[EdgeType.VALIDATED_BY],        direction="backward",        depth=max_depth,    )    audits = graph.traverse(        start_id=transition_id,        edge_types=[EdgeType.AUDITED_BY],        direction="backward",        depth=max_depth,    )    return {"proofs": proofs, "audits": audits} def query_before_time(graph: ProvenanceGraph, transition_id: str, time_anchor_ns: int, max_depth: int = 100) -> List[str]:     return graph.traverse(        start_id=transition_id,        edge_types=[EdgeType.DERIVED_FROM, EdgeType.ANCESTOR],        direction="backward",        depth=max_depth,        time_filter_ns=time_anchor_ns,    )`

## `src/k501/graph/validator.py`

python

`""" Graph validator for causality and DAG invariants. """ from __future__ import annotations from dataclasses import dataclass from typing import Any, Dict, List, Set from .models import EdgeType, TransitionEdge, TransitionNode, TransitionType @dataclass class GraphValidationError:     error_type: str    message: str    details: Dict[str, Any] = None     def to_dict(self) -> Dict[str, Any]:        return {            "error_type": self.error_type,            "message": self.message,            "details": self.details or {},        } class TransitionGraphValidator:     def __init__(self, nodes: Dict[str, TransitionNode], edges: List[TransitionEdge]):        self.nodes = nodes        self.edges = edges        self.forward_edges: Dict[str, List[TransitionEdge]] = {}        self.backward_edges: Dict[str, List[TransitionEdge]] = {}        for edge in edges:            self.forward_edges.setdefault(edge.source_id, []).append(edge)            self.backward_edges.setdefault(edge.target_id, []).append(edge)     def validate(self) -> List[GraphValidationError]:        errors = []        errors.extend(self.validate_transition_chain())        errors.extend(self.validate_dag())        return errors     def validate_transition_chain(self) -> List[GraphValidationError]:        errors = []        by_state: Dict[str, List[TransitionNode]] = {}        for node in self.nodes.values():            by_state.setdefault(node.after_state_id, []).append(node)         for state_id, transitions in by_state.items():            has_create = any(t.transition_type == TransitionType.CREATE for t in transitions)            if not has_create:                errors.append(GraphValidationError(                    "MISSING_CREATE",                    f"State {state_id} has no CREATE transition.",                    {"state_id": state_id},                ))                continue             create_ts = next((t.timestamp_ns for t in transitions if t.transition_type == TransitionType.CREATE), None)            freeze_ts = next((t.timestamp_ns for t in transitions if t.transition_type == TransitionType.FREEZE), None)            archive_ts = next((t.timestamp_ns for t in transitions if t.transition_type == TransitionType.ARCHIVE), None)             if freeze_ts is not None and create_ts is not None and freeze_ts < create_ts:                errors.append(GraphValidationError(                    "CHRONOLOGY_VIOLATION",                    f"State {state_id}: FREEZE occurs before CREATE.",                    {"state_id": state_id},                ))            if archive_ts is not None and freeze_ts is not None and archive_ts < freeze_ts:                errors.append(GraphValidationError(                    "CHRONOLOGY_VIOLATION",                    f"State {state_id}: ARCHIVE occurs before FREEZE.",                    {"state_id": state_id},                ))        return errors     def validate_dag(self) -> List[GraphValidationError]:        errors = []        adj: Dict[str, List[str]] = {}        for edge in self.edges:            if edge.edge_type == EdgeType.DERIVED_FROM:                adj.setdefault(edge.source_id, []).append(edge.target_id)         visited: Set[str] = set()        stack: Set[str] = set()         def dfs(node: str) -> bool:            visited.add(node)            stack.add(node)            for nxt in adj.get(node, []):                if nxt not in visited:                    if dfs(nxt):                        return True                elif nxt in stack:                    return True            stack.remove(node)            return False         for node_id in adj:            if node_id not in visited and dfs(node_id):                errors.append(GraphValidationError(                    "CYCLE_DETECTED",                    "Cyclic dependency detected in DERIVED_FROM edges.",                    {"node_id": node_id},                ))                break        return errors`

## `src/k501/graph/replay_validator.py`

python

`""" Replay validator for ordered determinism. """ from __future__ import annotations from dataclasses import dataclass from typing import Dict, List from ..core.replay import replay_stream_digest from .models import TransitionEdge, TransitionNode from .validator import GraphValidationError @dataclass class ReplayResult:     identical: bool    digest_match: bool    node_match: bool    edge_match: bool    attribute_match: bool class ReplayValidator:     def __init__(        self,        original_nodes: Dict[str, TransitionNode],        original_edges: List[TransitionEdge],        replayed_nodes: Dict[str, TransitionNode],        replayed_edges: List[TransitionEdge],    ):        self.original_nodes = original_nodes        self.original_edges = original_edges        self.replayed_nodes = replayed_nodes        self.replayed_edges = replayed_edges     def validate_replay(self) -> List[GraphValidationError]:        errors = []         orig_node_ids = list(self.original_nodes.keys())        repl_node_ids = list(self.replayed_nodes.keys())         if set(orig_node_ids) != set(repl_node_ids):            errors.append(GraphValidationError(                "REPLAY_NODE_MISMATCH",                "Node sets of original and replay do not match.",                {                    "missing_in_replay": list(set(orig_node_ids) - set(repl_node_ids)),                    "extra_in_replay": list(set(repl_node_ids) - set(orig_node_ids)),                },            ))         orig_edges = {(e.source_id, e.edge_type.value, e.target_id) for e in self.original_edges}        repl_edges = {(e.source_id, e.edge_type.value, e.target_id) for e in self.replayed_edges}         if orig_edges != repl_edges:            errors.append(GraphValidationError(                "REPLAY_EDGE_MISMATCH",                "Edge topology differs after replay.",                {                    "missing_edges": list(orig_edges - repl_edges),                    "extra_edges": list(repl_edges - orig_edges),                },            ))         for node_id in set(orig_node_ids).intersection(repl_node_ids):            if self.original_nodes[node_id].attributes != self.replayed_nodes[node_id].attributes:                errors.append(GraphValidationError(                    "REPLAY_ATTRIBUTE_MUTATION",                    f"Attribute mutation detected in Node {node_id}.",                    {                        "original": self.original_nodes[node_id].attributes,                        "replayed": self.replayed_nodes[node_id].attributes,                    },                ))         orig_digest = replay_stream_digest(orig_node_ids)        repl_digest = replay_stream_digest(repl_node_ids)        if orig_digest != repl_digest:            errors.append(GraphValidationError(                "REPLAY_DIGEST_MISMATCH",                "Ordered replay digest mismatch.",                {"original": orig_digest, "replayed": repl_digest},            ))         return errors     def is_identical(self) -> bool:        return len(self.validate_replay()) == 0`

## `src/k501/__init__.py`

python

`""" K501-AIONARC package. """`

## `src/k501/core/__init__.py`

python

`from .identity_axiom import IdentityAxiom, IDENTITY_AXIOM, get_identity_fields from .transition import StateTransition from .exceptions import DuplicateTransitionError, AppendOnlyViolation, InvalidTransitionError from .replay import replay_stream_digest __all__ = [     "IdentityAxiom",    "IDENTITY_AXIOM",    "get_identity_fields",    "StateTransition",    "DuplicateTransitionError",    "AppendOnlyViolation",    "InvalidTransitionError",    "replay_stream_digest", ]`

## `src/k501/evidence/__init__.py`

python

`from .store import FileEvidenceStore from .ingest import ingest_transition from .exceptions import DuplicateTransitionError, AppendOnlyViolation __all__ = [     "FileEvidenceStore",    "ingest_transition",    "DuplicateTransitionError",    "AppendOnlyViolation", ]`

## `src/k501/graph/__init__.py`

python

`from .models import TransitionNode, TransitionEdge, TransitionType, EdgeType from .store import ProvenanceGraph from .traverse import lineage_traversal, ancestry_depth, common_ancestors from .query import query_lineage, query_provenance_audits, query_before_time from .validator import TransitionGraphValidator, GraphValidationError from .replay_validator import ReplayValidator __all__ = [     "TransitionNode",    "TransitionEdge",    "TransitionType",    "EdgeType",    "ProvenanceGraph",    "lineage_traversal",    "ancestry_depth",    "common_ancestors",    "query_lineage",    "query_provenance_audits",    "query_before_time",    "TransitionGraphValidator",    "GraphValidationError",    "ReplayValidator", ]`

## `tests/unit/test_identity_axiom.py`

python

`from __future__ import annotations from datetime import datetime, timezone import pytest from k501.core.identity_axiom import IDENTITY_AXIOM, IdentityAxiom, get_identity_fields from k501.core.transition import StateTransition from k501.evidence.store import FileEvidenceStore from k501.core.exceptions import DuplicateTransitionError def test_identity_axiom_decision():     assert IDENTITY_AXIOM == IdentityAxiom.CONTENT_PLUS_PROVENANCE    assert get_identity_fields() == [        "before_state_id",        "after_state_id",        "transition_type",        "content",        "provenance_transition_ids",    ] def test_same_transition_different_timestamp_same_id():     t1 = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp_ns=1781654400000000000,        content={"object_type": "frame", "axiom_id": "axiom:test", "namespace": "research"},        provenance_transition_ids=["transition:aaa"],    )    t2 = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp_ns=1781740800000000000,        content={"object_type": "frame", "axiom_id": "axiom:test", "namespace": "research"},        provenance_transition_ids=["transition:aaa"],    )    assert t1.transition_id == t2.transition_id    assert not t1.is_same_occurrence(t2) def test_timestamp_must_be_explicit():     with pytest.raises(ValueError):        StateTransition.create(            before_state_id=None,            after_state_id="state:frame:123",            transition_type="create",            timestamp_ns=None,  # type: ignore            content={"object_type": "frame"},            provenance_transition_ids=[],        ) def test_append_only_duplicate_error(tmp_path):     store = FileEvidenceStore(base_dir=str(tmp_path))    t = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp_ns=1781654400000000000,        content={"object_type": "frame", "axiom_id": "axiom:test", "namespace": "research"},        provenance_transition_ids=[],    )    store.append_transition(t)    with pytest.raises(DuplicateTransitionError):        store.append_transition(t)`

## `tests/unit/test_replay_axiom.py`

python

`from __future__ import annotations from k501.core.replay import replay_stream_digest def test_ordered_digest_changes_with_order():     a = ["transition:1", "transition:2", "transition:3"]    b = ["transition:3", "transition:2", "transition:1"]    assert replay_stream_digest(a) != replay_stream_digest(b) def test_same_order_same_digest():     a = ["transition:1", "transition:2", "transition:3"]    b = ["transition:1", "transition:2", "transition:3"]    assert replay_stream_digest(a) == replay_stream_digest(b)`

## `tests/unit/test_evidence_store.py`

python

`from __future__ import annotations from k501.core.transition import StateTransition from k501.evidence.store import FileEvidenceStore def test_append_and_retrieve_transition(tmp_path):     store = FileEvidenceStore(base_dir=str(tmp_path))    t = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp_ns=1781654400000000000,        content={"object_type": "frame", "axiom_id": "axiom:test", "namespace": "research"},        provenance_transition_ids=[],    )    store.append_transition(t)    fetched = store.get_transition(t.transition_id)    assert fetched is not None    assert fetched.transition_id == t.transition_id    assert fetched.timestamp_ns == t.timestamp_ns def test_replay_digest_written(tmp_path):     store = FileEvidenceStore(base_dir=str(tmp_path))    t = StateTransition.create(        before_state_id=None,        after_state_id="state:frame:123",        transition_type="create",        timestamp_ns=1781654400000000000,        content={"object_type": "frame", "axiom_id": "axiom:test", "namespace": "research"},        provenance_transition_ids=[],    )    store.append_transition(t)    digest = store.replay_digest()    assert len(digest) == 64`

## `tests/unit/test_graph_validator.py`

python

`from __future__ import annotations from k501.graph.models import EdgeType, TransitionEdge, TransitionNode, TransitionType from k501.graph.validator import TransitionGraphValidator def test_cycle_detection():     n1 = TransitionNode.create("transition:1", TransitionType.CREATE, None, "state:1", 1)    n2 = TransitionNode.create("transition:2", TransitionType.CREATE, None, "state:2", 2)    e1 = TransitionEdge.create("edge:1", "transition:1", EdgeType.DERIVED_FROM, "transition:2")    e2 = TransitionEdge.create("edge:2", "transition:2", EdgeType.DERIVED_FROM, "transition:1")    v = TransitionGraphValidator({n1.node_id: n1, n2.node_id: n2}, [e1, e2])    errors = v.validate()    assert any(e.error_type == "CYCLE_DETECTED" for e in errors)`

If you want, I can now generate the **exact repository file tree** for these modules, or extend this with the **API layer and CLI** next.

Here is the formal directory structure for the final transition-centric implementation. It follows the recommended `src/` layout for Python packages, which helps avoid import confusion and keeps tests separate from distributable code.[[packaging.python](https://packaging.python.org/en/latest/discussions/src-layout-vs-flat-layout/)]

## Repository layout

text

`k501-aionarc/ ├── pyproject.toml ├── README.md ├── LICENSE ├── Makefile ├── .gitignore ├── src/ │   └── k501/ │       ├── __init__.py │       ├── core/ │       │   ├── __init__.py │       │   ├── identity_axiom.py │       │   ├── transition.py │       │   ├── replay.py │       │   └── exceptions.py │       ├── utils/ │       │   ├── __init__.py │       │   └── canonical_serialization.py │       ├── evidence/ │       │   ├── __init__.py │       │   ├── exceptions.py │       │   ├── store.py │       │   └── ingest.py │       └── graph/ │           ├── __init__.py │           ├── models.py │           ├── store.py │           ├── traverse.py │           ├── query.py │           ├── validator.py │           └── replay_validator.py ├── tests/ │   ├── unit/ │   │   ├── test_identity_axiom.py │   │   ├── test_replay_axiom.py │   │   ├── test_evidence_store.py │   │   └── test_graph_validator.py │   ├── integration/ │   │   └── test_transition_pipeline.py │   └── e2e/ │       └── test_full_replay.py ├── data/ │   ├── evidence/ │   │   ├── transitions.jsonl │   │   ├── state_objects.jsonl │   │   ├── index.json │   │   └── replay_digest.txt │   └── graph/ │       ├── nodes.jsonl │       ├── edges.jsonl │       └── graph_digest.txt └── docs/     ├── architecture/    │   └── transition_centric_design.md    └── adr/        ├── 0001-identity-axiom.md        ├── 0002-rfc8785-canonicalization.md        ├── 0003-append-only-evidence-store.md        └── 0004-replay-axiom.md`

## Structural notes

- `core/` contains the canonical transition model, identity axiom, replay digest logic, and exceptions.
    
- `utils/` contains only deterministic helper code, with canonical serialization as the only required utility in this phase.
    
- `evidence/` is the append-only persistence layer for transitions and projections.
    
- `graph/` is the transition DAG and provenance traversal layer.
    
- `tests/` is split into unit, integration, and end-to-end checks to match the system’s determinism requirements.[[docs.pytest](https://docs.pytest.org/en/7.1.x/explanation/goodpractices.html)]
    
- `data/` holds local-first runtime artifacts, logs, and replay digests.
    
- `docs/adr/` records the ontology and persistence decisions so the identity contract does not drift over time.
    

## Minimal Phase 1–3 file set

If you want the smallest operational subset, the must-have files are:

text

`src/k501/core/__init__.py src/k501/core/identity_axiom.py src/k501/core/transition.py src/k501/core/replay.py src/k501/core/exceptions.py src/k501/utils/__init__.py src/k501/utils/canonical_serialization.py src/k501/evidence/__init__.py src/k501/evidence/exceptions.py src/k501/evidence/store.py src/k501/evidence/ingest.py src/k501/graph/__init__.py src/k501/graph/models.py src/k501/graph/store.py src/k501/graph/traverse.py src/k501/graph/query.py src/k501/graph/validator.py src/k501/graph/replay_validator.py tests/unit/test_identity_axiom.py tests/unit/test_replay_axiom.py tests/unit/test_evidence_store.py tests/unit/test_graph_validator.py`

This is close to a coherent production candidate, but I would not yet call it "final". There are still several architectural issues hidden in the implementation.

The overall direction is much stronger than the earlier SQLite/event hybrid.

The system has now essentially become:

```
AIONARC =

Transition Stream
        ↓

Projection Layer
        ↓

StateObjects

        ↓

Provenance Graph

        ↓

Replay Validator
```

and that is internally consistent.

### 1. RFC8785 usage

Good.

Using

```python
rfc8785.dumps(obj)
```

is preferable.

I would however suggest avoiding repeated encode/decode cycles.

Instead of

```python
def canonical_serialize(obj):
    data = rfc8785.dumps(obj)

    if isinstance(data,bytes):
        return data.decode()
```

I'd expose both interfaces.

```python
def canonical_bytes(obj)->bytes:

    x=rfc8785.dumps(obj)

    if isinstance(x,bytes):
        return x

    return x.encode("utf8")


def canonical_string(obj)->str:

    return canonical_bytes(obj).decode("utf8")


def canonical_hash(obj)->str:

    return hashlib.sha256(
            canonical_bytes(obj)
    ).hexdigest()
```

Less conversions.

---

### 2. REPLAY_AXIOM_0

I think this part is underspecified.

Current

```python
digest =
SHA256(

[
t1,
t2,
t3

]

)

```

detects order changes.

But not deletion.

Example

Original

```
t1
t2
t3
t4
```

Replay

```
t1
t2
t4
```

Digest changes.

Good.

But

```
t1
t2
t3
t4
t5
```

and

```
t1
t2
t3
t4
t5
t6
```

also change.

Question:

Do you intend

REPLAY_AXIOM_0

to mean

> identical prefix

or

> identical archive

I suspect what you really want is

```text
STREAM_DIGEST



HEAD_TRANSITION_ID


STREAM_LENGTH



```

or

```text
STREAM_ROOT


MERKLE_ROOT


TRANSITION_COUNT
```

Otherwise partial replication becomes difficult.

---

### 3. Provenance IDs

This is a very good decision.

Old

```python
provenance={

writer:"gemini"

toolchain:"ollama"

}


```

is mutable semantic metadata.

New

```python
provenance_transition_ids=[

transition:abc

transition:def

]

```

is compositional.

Much better.

It effectively means

Proofs are transitions.

Audits are transitions.

Imports are transitions.

Freeze is transition.

Validation is transition.

I like that.

---

### 4. Duplicate detection

This worries me.

Current

```python
index.json
```

contains every transition id.

At 100 million transitions

this becomes huge.

I'd probably prefer

```text
transitions.jsonl


transitions.idx



```

where

```
offset


transition_id



```

or perhaps

```python
sqlite


WITHOUT ROWID


```

only as an index

not as storage

---

### 5. State projections

Current

```python
state_objects.jsonl
```

contains every projection.

I'm not convinced.

Projection is reproducible.

Projection can always be rebuilt.

I'd probably remove

```text
state_objects.jsonl
```

entirely.

and keep only

```text
transitions.jsonl


replay_digest.txt


```

Then

```python
project_state(id)
```

materializes on demand.

Unless projection speed matters.

---

### 6. Atomicity

Current

```python
append_transition()


append transition


update index


append projection


update digest


```

is unsafe.

Crash between steps

can leave

```
transition exists


digest stale


projection missing


```

state.

I would suggest

append-only journal semantics

```text
write tmp



fsync


rename


fsync directory



```

or

```
transitions.segment


transitions.segment.sha256


```

---

### 7. Transition ID truncation

Current

```python
transition_id =

sha256(... )[:24]
```

96 bits.

Probably sufficient.

But if AIONARC is supposed to become a long-lived archive,

I'd simply use

```python
transition:

<full_sha256>



```

64 hex chars.

Storage overhead is negligible.

---

### 8. Graph digest

Current

```python
ordered_ids=list(self.nodes.keys())
```

depends on insertion order.

I would not trust that.

Better

```python
ordered_ids=sorted(self.nodes)
```

or

```python
ordered_ids = replay_order()


```

using causal ordering.

---

### 9. Something even simpler

After reading the whole design, I suspect AIONARC can be reduced further.

Canonical persistence:

```text
objects/


transitions/


states/



transitions/

0000000001.json


0000000002.json


0000000003.json




heads/


main


validation



freeze



```

Replay axiom

```text
REPLAY_AXIOM_0


digest =


SHA256(

transition_1 ||

transition_2 ||

...

transition_n

)



```

Identity axiom

```text
IDENTITY_AXIOM_0


transition_id =


SHA256(

before_state

after_state

type

content

provenance_transition_ids

)

```

Projection axiom

```text
PROJECTION_AXIOM_0


state =

fold(

transitions

)



```

Provenance axiom

```text
PROVENANCE_AXIOM_0


provenance(entity)


=

ancestor transitions



```

At that point, the entire core of AIONARC becomes surprisingly small:

- `transition.py`
    
- `canonical.py`
    
- `stream.py`
    
- `replay.py`
    
- `projection.py`
    
- `graph.py`
    
- `validator.py`
    

Probably less than 2000 lines of Python.

Conceptually, I think this is the first version you've shown that has a reasonably clear mathematical interpretation:

- `IDENTITY_AXIOM_0` — identity of a transition
    
- `REPLAY_AXIOM_0` — identity of a stream
    
- `PROJECTION_AXIOM_0` — deterministic state reconstruction
    
- `PROVENANCE_AXIOM_0` — ancestry relation over transitions
    

That feels substantially closer to a stable AIONARC kernel than earlier K501 iterations built around semantic frames, manifests, and auxiliary runtime layers.