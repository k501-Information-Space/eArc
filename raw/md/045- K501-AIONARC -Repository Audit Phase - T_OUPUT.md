┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ tree -L 3 src
src
├── k501
│   ├── agent
│   │   └── __init__.py
│   ├── api
│   │   ├── __init__.py
│   │   ├── middleware
│   │   └── routes
│   ├── core
│   │   ├── archive.py
│   │   ├── axiom.py
│   │   ├── canonical.py
│   │   ├── frame.py
│   │   ├── freeze.py
│   │   ├── __init__.py
│   │   ├── kernel.py
│   │   ├── lifecycle.py
│   │   ├── projection.py
│   │   ├── __pycache__
│   │   ├── replay.py
│   │   ├── snapshot.py
│   │   ├── state_object.py
│   │   ├── tests
│   │   ├── transition.py
│   │   └── validator.py
│   ├── embeddings
│   │   └── __init__.py
│   ├── evidence
│   │   ├── audit.py
│   │   ├── index.py
│   │   ├── __init__.py
│   │   ├── pointer.py
│   │   ├── proof.py
│   │   ├── __pycache__
│   │   └── receipt.py
│   ├── governance
│   │   └── __init__.py
│   ├── graph
│   │   └── __init__.py
│   ├── __init__.py
│   ├── observability
│   │   └── __init__.py
│   ├── __pycache__
│   │   └── __init__.cpython-313.pyc
│   ├── retrieval
│   │   └── __init__.py
│   ├── runtime
│   │   ├── __init__.py
│   │   ├── journal.py
│   │   └── __pycache__
│   ├── storage
│   │   ├── archive_store.py
│   │   ├── evidence_store.py
│   │   ├── index_store.py
│   │   ├── __init__.py
│   │   └── __pycache__
│   ├── utils
│   │   └── __init__.py
│   └── workers
│       └── __init__.py
└── k501_aionarc.egg-info
    ├── dependency_links.txt
    ├── PKG-INFO
    ├── requires.txt
    ├── SOURCES.txt
    └── top_level.txt

24 directories, 42 files
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ find src -type f | sort
src/k501/agent/__init__.py
src/k501_aionarc.egg-info/dependency_links.txt
src/k501_aionarc.egg-info/PKG-INFO
src/k501_aionarc.egg-info/requires.txt
src/k501_aionarc.egg-info/SOURCES.txt
src/k501_aionarc.egg-info/top_level.txt
src/k501/api/__init__.py
src/k501/api/middleware/__init__.py
src/k501/api/routes/__init__.py
src/k501/core/archive.py
src/k501/core/axiom.py
src/k501/core/canonical.py
src/k501/core/frame.py
src/k501/core/freeze.py
src/k501/core/__init__.py
src/k501/core/kernel.py
src/k501/core/lifecycle.py
src/k501/core/.mypy_cache/3.12/cache.0.db
src/k501/core/.mypy_cache/3.12/cache.10.db
src/k501/core/.mypy_cache/3.12/cache.11.db
src/k501/core/.mypy_cache/3.12/cache.12.db
src/k501/core/.mypy_cache/3.12/cache.13.db
src/k501/core/.mypy_cache/3.12/cache.14.db
src/k501/core/.mypy_cache/3.12/cache.15.db
src/k501/core/.mypy_cache/3.12/cache.1.db
src/k501/core/.mypy_cache/3.12/cache.2.db
src/k501/core/.mypy_cache/3.12/cache.3.db
src/k501/core/.mypy_cache/3.12/cache.4.db
src/k501/core/.mypy_cache/3.12/cache.5.db
src/k501/core/.mypy_cache/3.12/cache.6.db
src/k501/core/.mypy_cache/3.12/cache.7.db
src/k501/core/.mypy_cache/3.12/cache.8.db
src/k501/core/.mypy_cache/3.12/cache.9.db
src/k501/core/.mypy_cache/CACHEDIR.TAG
src/k501/core/.mypy_cache/.gitignore
src/k501/core/projection.py
src/k501/core/__pycache__/archive.cpython-313.pyc
src/k501/core/__pycache__/axiom.cpython-313.pyc
src/k501/core/__pycache__/canonical.cpython-313.pyc
src/k501/core/__pycache__/frame.cpython-313.pyc
src/k501/core/__pycache__/freeze.cpython-313.pyc
src/k501/core/__pycache__/__init__.cpython-313.pyc
src/k501/core/__pycache__/kernel.cpython-313.pyc
src/k501/core/__pycache__/lifecycle.cpython-313.pyc
src/k501/core/__pycache__/snapshot.cpython-313.pyc
src/k501/core/__pycache__/state_object.cpython-313.pyc
src/k501/core/__pycache__/transition.cpython-313.pyc
src/k501/core/__pycache__/validator.cpython-313.pyc
src/k501/core/replay.py
src/k501/core/snapshot.py
src/k501/core/state_object.py
src/k501/core/transition.py
src/k501/core/validator.py
src/k501/embeddings/__init__.py
src/k501/evidence/audit.py
src/k501/evidence/index.py
src/k501/evidence/__init__.py
src/k501/evidence/pointer.py
src/k501/evidence/proof.py
src/k501/evidence/__pycache__/audit.cpython-313.pyc
src/k501/evidence/__pycache__/index.cpython-313.pyc
src/k501/evidence/__pycache__/__init__.cpython-313.pyc
src/k501/evidence/__pycache__/pointer.cpython-313.pyc
src/k501/evidence/__pycache__/proof.cpython-313.pyc
src/k501/evidence/__pycache__/receipt.cpython-313.pyc
src/k501/evidence/receipt.py
src/k501/governance/__init__.py
src/k501/graph/__init__.py
src/k501/__init__.py
src/k501/observability/__init__.py
src/k501/__pycache__/__init__.cpython-313.pyc
src/k501/retrieval/__init__.py
src/k501/runtime/__init__.py
src/k501/runtime/journal.py
src/k501/runtime/__pycache__/__init__.cpython-313.pyc
src/k501/runtime/__pycache__/journal.cpython-313.pyc
src/k501/storage/archive_store.py
src/k501/storage/evidence_store.py
src/k501/storage/index_store.py
src/k501/storage/__init__.py
src/k501/storage/__pycache__/archive_store.cpython-313.pyc
src/k501/storage/__pycache__/evidence_store.cpython-313.pyc
src/k501/storage/__pycache__/index_store.cpython-313.pyc
src/k501/storage/__pycache__/__init__.cpython-313.pyc
src/k501/utils/__init__.py
src/k501/workers/__init__.py
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ find tests -type f | sort
tests/unit/__pycache__/test_archive.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_archive_store.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_audit.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_axiom.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_canonical.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_evidence_store.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_frame.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_freeze.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_identity_validator.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_imports.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_index.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_index_store.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_journal.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_kernel.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_lifecycle.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_pointer.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_proof.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_receipt.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_repository_structure.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_snapshot.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_state_object.cpython-313-pytest-9.1.0.pyc
tests/unit/__pycache__/test_transition.cpython-313-pytest-9.1.0.pyc
tests/unit/test_archive.py
tests/unit/test_archive_store.py
tests/unit/test_audit.py
tests/unit/test_axiom.py
tests/unit/test_canonical.py
tests/unit/test_evidence_store.py
tests/unit/test_frame.py
tests/unit/test_freeze.py
tests/unit/test_identity_validator.py
tests/unit/test_imports.py
tests/unit/test_index.py
tests/unit/test_index_store.py
tests/unit/test_journal.py
tests/unit/test_kernel.py
tests/unit/test_lifecycle.py
tests/unit/test_pointer.py
tests/unit/test_proof.py
tests/unit/test_receipt.py
tests/unit/test_repository_structure.py
tests/unit/test_snapshot.py
tests/unit/test_state_object.py
tests/unit/test_transition.py
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ find src -name "*.py" -exec wc -l {} \; | sort -n
0 src/k501/agent/__init__.py
0 src/k501/api/__init__.py
0 src/k501/api/middleware/__init__.py
0 src/k501/api/routes/__init__.py
0 src/k501/core/__init__.py
0 src/k501/embeddings/__init__.py
0 src/k501/evidence/__init__.py
0 src/k501/governance/__init__.py
0 src/k501/graph/__init__.py
0 src/k501/__init__.py
0 src/k501/observability/__init__.py
0 src/k501/retrieval/__init__.py
0 src/k501/storage/__init__.py
0 src/k501/utils/__init__.py
0 src/k501/workers/__init__.py
3 src/k501/runtime/__init__.py
9 src/k501/core/replay.py
10 src/k501/core/axiom.py
14 src/k501/core/frame.py
14 src/k501/core/freeze.py
14 src/k501/core/kernel.py
14 src/k501/evidence/pointer.py
15 src/k501/core/archive.py
15 src/k501/core/lifecycle.py
15 src/k501/core/projection.py
15 src/k501/core/snapshot.py
15 src/k501/evidence/proof.py
15 src/k501/evidence/receipt.py
15 src/k501/runtime/journal.py
15 src/k501/storage/archive_store.py
15 src/k501/storage/evidence_store.py
15 src/k501/storage/index_store.py
16 src/k501/core/state_object.py
17 src/k501/evidence/audit.py
17 src/k501/evidence/index.py
18 src/k501/core/validator.py
36 src/k501/core/canonical.py
63 src/k501/core/transition.py
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ sed -n '1,200p' src/k501/core/axiom.py

sed -n '1,200p' src/k501/core/frame.py

sed -n '1,200p' src/k501/core/state_object.py

sed -n '1,200p' src/k501/core/snapshot.py

sed -n '1,200p' src/k501/core/freeze.py

sed -n '1,200p' src/k501/core/archive.py

sed -n '1,200p' src/k501/core/lifecycle.py

sed -n '1,200p' src/k501/core/kernel.py
from pydantic import BaseModel


class Axiom(BaseModel):
    """
    Root ontology primitive of K501-AIONARC.
    """

    name: str
    description: str
from pydantic import BaseModel


class Frame(BaseModel):
    """
    Frame ontology object.

    A Frame represents a bounded unit of information
    within the K501-AIONARC ontology.
    """

    frame_id: str
    title: str
    description: str
from pydantic import BaseModel


class StateObject(BaseModel):
    """
    StateObject ontology object.

    A StateObject represents the current
    state of a Frame within the
    K501-AIONARC ontology.
    """

    state_id: str
    frame_id: str
    version: str
    status: str
from pydantic import BaseModel


class Snapshot(BaseModel):
    """
    Snapshot ontology object.

    A Snapshot represents a captured
    StateObject at a specific moment.
    """

    snapshot_id: str
    state_id: str
    version: str
    description: str
from pydantic import BaseModel


class Freeze(BaseModel):
    """
    Freeze ontology object.

    A Freeze represents an immutable
    Snapshot within the K501-AIONARC ontology.
    """

    freeze_id: str
    snapshot_id: str
    reason: str
from pydantic import BaseModel


class Archive(BaseModel):
    """
    Archive ontology object.

    An Archive represents a frozen object
    accepted for long-term preservation
    within the K501-AIONARC ontology.
    """

    archive_id: str
    title: str
    description: str
from pydantic import BaseModel


class Lifecycle(BaseModel):
    """
    Lifecycle ontology object.

    A Lifecycle defines the valid progression
    of ontology objects within the
    K501-AIONARC ontology.
    """

    lifecycle_id: str
    title: str
    description: str
from pydantic import BaseModel


class Kernel(BaseModel):
    """
    Kernel ontology object.

    The Kernel is the root orchestration
    object of the K501-AIONARC ontology.
    """

    kernel_id: str
    title: str
    description: str
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ sed -n '1,200p' src/k501/core/canonical.py

sed -n '1,200p' src/k501/core/transition.py

sed -n '1,200p' src/k501/core/projection.py

sed -n '1,200p' src/k501/core/validator.py

sed -n '1,200p' src/k501/core/replay.py
from __future__ import annotations

import hashlib
import json
from typing import Any


def canonical_string(obj: Any) -> str:
    """
    Deterministic JSON serialization.
    """

    return json.dumps(
        obj,
        sort_keys=True,
        separators=(",", ":"),
        ensure_ascii=False,
    )


def canonical_bytes(obj: Any) -> bytes:
    """
    Canonical UTF-8 bytes.
    """

    return canonical_string(obj).encode("utf-8")


def canonical_hash(obj: Any) -> str:
    """
    SHA256 hash of canonical representation.
    """

    return hashlib.sha256(
        canonical_bytes(obj)
    ).hexdigest()
from __future__ import annotations

from typing import Any

from pydantic import BaseModel

from k501.core.canonical import canonical_hash


class Transition(BaseModel):
    transition_id: str
    object_id: str
    timestamp_ns: int
    content: dict[str, Any]
    metadata: dict[str, Any]
    provenance: list[str]

    @classmethod
    def create(
        cls,
        *,
        object_id: str,
        timestamp_ns: int,
        content: dict[str, Any],
        metadata: dict[str, Any],
        provenance: list[str],
    ) -> "Transition":
        payload = transition_identity_payload(
            object_id=object_id,
            content=content,
            provenance=provenance,
        )

        transition_id = compute_transition_id(payload)

        return cls(
            transition_id=transition_id,
            object_id=object_id,
            timestamp_ns=timestamp_ns,
            content=content,
            metadata=metadata,
            provenance=provenance,
        )

    def to_record(self) -> dict[str, Any]:
        return self.model_dump()


def transition_identity_payload(
    *,
    object_id: str,
    content: dict[str, Any],
    provenance: list[str],
) -> dict[str, Any]:
    return {
        "object_id": object_id,
        "content": content,
        "provenance": provenance,
    }


def compute_transition_id(payload: dict[str, Any]) -> str:
    return canonical_hash(payload)
from k501.core.state_object import StateObject
from k501.core.transition import Transition


def project_state(
    transitions: list[Transition],
) -> StateObject:
    latest = transitions[-1]

    return StateObject(
        state_id=latest.transition_id,
        frame_id=str(latest.content["frame_id"]),
        version=str(latest.content["version"]),
        status=str(latest.content["status"]),
    )
from pydantic import BaseModel

from k501.core.transition import Transition


class IdentityValidationResult(BaseModel):
    valid: bool


class IdentityValidator:
    @staticmethod
    def validate(
        transition: Transition,
    ) -> IdentityValidationResult:
        if not transition.transition_id:
            return IdentityValidationResult(valid=False)

        return IdentityValidationResult(valid=True)
from k501.core.projection import project_state
from k501.core.state_object import StateObject
from k501.core.transition import Transition


def replay(
    transitions: list[Transition],
) -> StateObject:
    return project_state(transitions)
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ sed -n '1,200p' src/k501/evidence/proof.py

sed -n '1,200p' src/k501/evidence/receipt.py

sed -n '1,200p' src/k501/evidence/audit.py

sed -n '1,200p' src/k501/evidence/index.py

sed -n '1,200p' src/k501/evidence/pointer.py
from pydantic import BaseModel


class Proof(BaseModel):
    """
    Proof evidence object.

    A Proof represents validated evidence
    that an ontology object was manifested
    and successfully verified.
    """

    proof_id: str
    ontology_object: str
    status: str
from pydantic import BaseModel


class Receipt(BaseModel):
    """
    Receipt evidence object.

    A Receipt records the successful
    manifestation or verification
    of an ontology or evidence object.
    """

    receipt_id: str
    proof_id: str
    status: str
from pydantic import BaseModel


class Audit(BaseModel):
    """
    Audit evidence object.

    An Audit records the verification
    of a Proof and Receipt lineage
    within the K501-AIONARC
    Information Space.
    """

    audit_id: str
    proof_id: str
    receipt_id: str
    status: str
from pydantic import BaseModel


class Index(BaseModel):
    """
    Index evidence object.

    An Index provides a searchable
    reference into proofs, receipts,
    audits, and future archival
    structures within the
    K501-AIONARC Information Space.
    """

    index_id: str
    target_object: str
    target_id: str
from pydantic import BaseModel


class Pointer(BaseModel):
    """
    Pointer evidence object.

    A Pointer represents a stable reference
    to an indexed ontology or evidence object.
    """

    pointer_id: str
    index_id: str
    target_id: str
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ sed -n '1,200p' src/k501/storage/archive_store.py

sed -n '1,200p' src/k501/storage/evidence_store.py

sed -n '1,200p' src/k501/storage/index_store.py
from pydantic import BaseModel


class ArchiveStore(BaseModel):
    """
    ArchiveStore storage object.

    ArchiveStore represents a persistent
    storage location for archived ontology
    and evidence objects.
    """

    store_id: str
    archive_id: str
    location: str
from pydantic import BaseModel


class EvidenceStore(BaseModel):
    """
    EvidenceStore storage object.

    EvidenceStore represents a persistent
    storage location for evidence artifacts
    within the K501-AIONARC Information Space.
    """

    store_id: str
    evidence_type: str
    location: str
from pydantic import BaseModel


class IndexStore(BaseModel):
    """
    IndexStore storage object.

    IndexStore represents a persistent
    storage location for index artifacts
    within the K501-AIONARC Information Space.
    """

    store_id: str
    index_id: str
    location: str
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ sed -n '1,200p' src/k501/runtime/journal.py
from pydantic import BaseModel


class Journal(BaseModel):
    """
    Journal runtime object.

    Journal represents an append-only
    chronological record within the
    K501-AIONARC Information Space.
    """

    journal_id: str
    stream_name: str
    event_count: int
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ find src -name "__pycache__"

find . -name "*.pyc"

find . -name "*.pyo"

find . -name "*.egg-info"
src/k501/storage/__pycache__
src/k501/runtime/__pycache__
src/k501/evidence/__pycache__
src/k501/__pycache__
src/k501/core/__pycache__
./.venv/lib/python3.13/site-packages/typing_inspection/__pycache__/typing_objects.cpython-313.pyc
./.venv/lib/python3.13/site-packages/typing_inspection/__pycache__/introspection.cpython-313.pyc
./.venv/lib/python3.13/site-packages/typing_inspection/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/server/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/plugins/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/__pycache__/version.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/__pycache__/__main__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/__pycache__/bogus_type.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/__pycache__/split_namespace.cpython-313.pyc
./.venv/lib/python3.13/site-packages/mypy/__pycache__/pyinfo.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pytest_cov/__pycache__/__init__.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/pytest_cov/__pycache__/plugin.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/orjson/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/plugin/__pycache__/_loader.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/plugin/__pycache__/_schema_validator.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/plugin/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_generate_schema.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_import_utils.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_discriminated_union.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_utils.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_fields.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_schema_generation_shared.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_signature.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_known_annotated_metadata.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_core_utils.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_model_construction.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_repr.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_core_metadata.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_generics.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_namespace_utils.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_config.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_docs_extraction.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_typing_extra.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_validators.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_schema_gather.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_decorators.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_internal_dataclass.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_mock_val_ser.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/_internal/__pycache__/_forward_ref.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/main.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/config.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/version.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/_migration.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/annotated_handlers.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/aliases.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/warnings.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/functional_validators.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/fields.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/errors.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/types.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic/__pycache__/json_schema.cpython-313.pyc
./.venv/lib/python3.13/site-packages/annotated_types/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/styles/__pycache__/_mapping.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/styles/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/formatters/__pycache__/terminal.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/formatters/__pycache__/_mapping.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/formatters/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/modeline.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/util.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/lexer.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/token.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/filter.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/regexopt.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/unistring.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/formatter.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/console.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/__pycache__/plugin.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/lexers/__pycache__/_mapping.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/lexers/__pycache__/diff.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/lexers/__pycache__/python.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/lexers/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pygments/filters/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/simple/__pycache__/pathspec.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/simple/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/simple/__pycache__/gitignore.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/__pycache__/_utils.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/__pycache__/agg.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/re2/__pycache__/pathspec.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/re2/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/re2/__pycache__/gitignore.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/re2/__pycache__/_base.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/re2/__pycache__/base.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/hyperscan/__pycache__/pathspec.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/hyperscan/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/hyperscan/__pycache__/gitignore.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/hyperscan/__pycache__/_base.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/_backends/hyperscan/__pycache__/base.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/patterns/__pycache__/gitwildmatch.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/patterns/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/patterns/gitignore/__pycache__/spec.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/patterns/gitignore/__pycache__/basic.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/patterns/gitignore/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/patterns/gitignore/__pycache__/base.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/util.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/pathspec.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/_version.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/backend.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/_typing.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/gitignore.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/pattern.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pathspec/__pycache__/_meta.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pytest/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/iniconfig/__pycache__/_parse.cpython-313.pyc
./.venv/lib/python3.13/site-packages/iniconfig/__pycache__/exceptions.cpython-313.pyc
./.venv/lib/python3.13/site-packages/iniconfig/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/anyio/_backends/__pycache__/_trio.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_backends/__pycache__/_asyncio.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_backends/__pycache__/__init__.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/streams/__pycache__/stapled.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/streams/__pycache__/tls.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/streams/__pycache__/__init__.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/streams/__pycache__/memory.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_testing.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_eventloop.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_tasks.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_resources.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_subprocesses.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/__init__.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_sockets.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/abc/__pycache__/_streams.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_synchronization.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_testing.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_fileio.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_eventloop.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_tempfile.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_tasks.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_resources.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_subprocesses.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_signals.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/__init__.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_exceptions.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_contextmanagers.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_typedattr.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_sockets.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/_core/__pycache__/_streams.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/__pycache__/from_thread.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/__pycache__/to_thread.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/__pycache__/pytest_plugin.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/__pycache__/__init__.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/anyio/__pycache__/lowlevel.cpython-313-pytest-9.1.0.pyc
./.venv/lib/python3.13/site-packages/pydantic_core/__pycache__/core_schema.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pydantic_core/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_code/__pycache__/source.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_code/__pycache__/code.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_code/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_io/__pycache__/terminalwriter.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_io/__pycache__/pprint.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_io/__pycache__/saferepr.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_io/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_io/__pycache__/wcwidth.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/config/__pycache__/findpaths.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/config/__pycache__/argparsing.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/config/__pycache__/exceptions.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/config/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/truncate.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/util.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/rewrite.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/_compare_any.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/highlight.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/_compare_set.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/_compare_sequence.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/_compare_mapping.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/_typing.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/_guards.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/assertion/__pycache__/compare_text.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/mark/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/mark/__pycache__/structures.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/mark/__pycache__/expression.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_py/__pycache__/error.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_py/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/_py/__pycache__/path.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/main.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/legacypath.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/freeze_support.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/stepwise.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/terminal.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/cacheprovider.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/deprecated.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/setupplan.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/recwarn.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/capture.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/doctest.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/nodes.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/compat.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/reports.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/outcomes.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/helpconfig.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/debugging.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/_version.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/unittest.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/hookspec.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/threadexception.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/timing.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/fixtures.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/raises.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/setuponly.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/pathlib.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/python.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/faulthandler.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/logging.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/warning_types.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/junitxml.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/warnings.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/pytester.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/_argcomplete.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/tmpdir.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/stash.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/subtests.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/scope.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/runner.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/skipping.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/monkeypatch.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/python_api.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/unraisableexception.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/tracemalloc.cpython-313.pyc
./.venv/lib/python3.13/site-packages/_pytest/__pycache__/pastebin.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_warnings.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_manager.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_tracing.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_version.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/__init__.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_result.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_hooks.cpython-313.pyc
./.venv/lib/python3.13/site-packages/pluggy/__pycache__/_callers.cpython-313.pyc
./.venv/lib/python3.13/site-packages/__pycache__/py.cpython-313.pyc
./.venv/lib/python3.13/site-packages/__pycache__/typing_extensions.cpython-313.pyc
./.venv/lib/python3.13/site-packages/__pycache__/mypy_extensions.cpython-313.pyc
./.venv/lib/python3.13/site-packages/__pycache__/_virtualenv.cpython-313.pyc
./src/k501/storage/__pycache__/index_store.cpython-313.pyc
./src/k501/storage/__pycache__/evidence_store.cpython-313.pyc
./src/k501/storage/__pycache__/__init__.cpython-313.pyc
./src/k501/storage/__pycache__/archive_store.cpython-313.pyc
./src/k501/runtime/__pycache__/journal.cpython-313.pyc
./src/k501/runtime/__pycache__/__init__.cpython-313.pyc
./src/k501/evidence/__pycache__/proof.cpython-313.pyc
./src/k501/evidence/__pycache__/index.cpython-313.pyc
./src/k501/evidence/__pycache__/pointer.cpython-313.pyc
./src/k501/evidence/__pycache__/__init__.cpython-313.pyc
./src/k501/evidence/__pycache__/receipt.cpython-313.pyc
./src/k501/evidence/__pycache__/audit.cpython-313.pyc
./src/k501/__pycache__/__init__.cpython-313.pyc
./src/k501/core/__pycache__/state_object.cpython-313.pyc
./src/k501/core/__pycache__/snapshot.cpython-313.pyc
./src/k501/core/__pycache__/freeze.cpython-313.pyc
./src/k501/core/__pycache__/transition.cpython-313.pyc
./src/k501/core/__pycache__/lifecycle.cpython-313.pyc
./src/k501/core/__pycache__/validator.cpython-313.pyc
./src/k501/core/__pycache__/axiom.cpython-313.pyc
./src/k501/core/__pycache__/__init__.cpython-313.pyc
./src/k501/core/__pycache__/canonical.cpython-313.pyc
./src/k501/core/__pycache__/archive.cpython-313.pyc
./src/k501/core/__pycache__/frame.cpython-313.pyc
./src/k501/core/__pycache__/kernel.cpython-313.pyc
./tests/unit/__pycache__/test_frame.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_proof.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_pointer.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_state_object.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_archive_store.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_lifecycle.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_evidence_store.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_axiom.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_freeze.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_imports.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_canonical.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_kernel.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_index_store.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_archive.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_identity_validator.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_journal.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_index.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_receipt.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_repository_structure.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_audit.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_transition.cpython-313-pytest-9.1.0.pyc
./tests/unit/__pycache__/test_snapshot.cpython-313-pytest-9.1.0.pyc
./src/k501_aionarc.egg-info
                                                                                                                    
┌──(matsch㉿hirn)-[~/Projekte/k501-aionarc]
└─$ 
