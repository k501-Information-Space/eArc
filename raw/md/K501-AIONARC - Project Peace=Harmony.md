┌──(peace㉿harmony)-[~/Projekte/k501-aionarc]
└─$ tree -L 5 
.
├── benchmarks
│   ├── datasets
│   ├── expected
│   └── queries
├── configs
├── data
│   ├── archive
│   ├── audits
│   ├── beliefs
│   ├── claims
│   ├── freezes
│   ├── indexes
│   ├── manifests
│   ├── proofs
│   └── snapshots
├── docs
│   ├── adr
│   ├── api
│   ├── architecture
│   ├── proofs
│   │   ├── proof_v0_archive.md
│   │   ├── proof_v0_axiom.md
│   │   ├── proof_v0_frame.md
│   │   ├── proof_v0_freeze.md
│   │   ├── proof_v0_kernel.md
│   │   ├── proof_v0_lifecycle.md
│   │   ├── proof_v0_snapshot.md
│   │   └── proof_v0_state_object.md
│   ├── runbooks
│   └── schemas
├── main.py
├── Makefile
├── mypy.ini
├── pyproject.toml
├── pytest.ini
├── README.md
├── ruff.toml
├── scripts
├── src
│   ├── k501
│   │   ├── agent
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   ├── api
│   │   │   ├── __init__.py
│   │   │   ├── middleware
│   │   │   │   ├── __init__.py
│   │   │   │   └── __pycache__
│   │   │   ├── __pycache__
│   │   │   │   └── __init__.cpython-313.pyc
│   │   │   └── routes
│   │   │       ├── __init__.py
│   │   │       └── __pycache__
│   │   ├── core
│   │   │   ├── archive.py
│   │   │   ├── axiom.py
│   │   │   ├── canonical.py
│   │   │   ├── frame.py
│   │   │   ├── freeze.py
│   │   │   ├── __init__.py
│   │   │   ├── kernel.py
│   │   │   ├── lifecycle.py
│   │   │   ├── projection.py
│   │   │   ├── __pycache__
│   │   │   │   ├── archive.cpython-313.pyc
│   │   │   │   ├── axiom.cpython-313.pyc
│   │   │   │   ├── canonical.cpython-313.pyc
│   │   │   │   ├── frame.cpython-313.pyc
│   │   │   │   ├── freeze.cpython-313.pyc
│   │   │   │   ├── __init__.cpython-313.pyc
│   │   │   │   ├── kernel.cpython-313.pyc
│   │   │   │   ├── lifecycle.cpython-313.pyc
│   │   │   │   ├── projection.cpython-313.pyc
│   │   │   │   ├── replay.cpython-313.pyc
│   │   │   │   ├── snapshot.cpython-313.pyc
│   │   │   │   ├── state_object.cpython-313.pyc
│   │   │   │   ├── transition.cpython-313.pyc
│   │   │   │   ├── transition_v2.cpython-313.pyc
│   │   │   │   ├── validator.cpython-313.pyc
│   │   │   │   └── validator_v2.cpython-313.pyc
│   │   │   ├── replay.py
│   │   │   ├── snapshot.py
│   │   │   ├── state_object.py
│   │   │   ├── tests
│   │   │   │   └── unit
│   │   │   ├── transition.py
│   │   │   ├── transition_v2.py
│   │   │   ├── validator.py
│   │   │   └── validator_v2.py
│   │   ├── embeddings
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   ├── evidence
│   │   │   ├── audit.py
│   │   │   ├── index.py
│   │   │   ├── __init__.py
│   │   │   ├── pointer.py
│   │   │   ├── proof.py
│   │   │   ├── __pycache__
│   │   │   │   ├── audit.cpython-313.pyc
│   │   │   │   ├── index.cpython-313.pyc
│   │   │   │   ├── __init__.cpython-313.pyc
│   │   │   │   ├── pointer.cpython-313.pyc
│   │   │   │   ├── proof.cpython-313.pyc
│   │   │   │   └── receipt.cpython-313.pyc
│   │   │   └── receipt.py
│   │   ├── governance
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   ├── graph
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   ├── __init__.py
│   │   ├── observability
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   ├── __pycache__
│   │   │   └── __init__.cpython-313.pyc
│   │   ├── retrieval
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   ├── runtime
│   │   │   ├── __init__.py
│   │   │   ├── journal.py
│   │   │   └── __pycache__
│   │   │       ├── __init__.cpython-313.pyc
│   │   │       └── journal.cpython-313.pyc
│   │   ├── storage
│   │   │   ├── archive_store.py
│   │   │   ├── evidence_store.py
│   │   │   ├── exceptions.py
│   │   │   ├── index_store.py
│   │   │   ├── __init__.py
│   │   │   ├── journal.py
│   │   │   └── __pycache__
│   │   │       ├── archive_store.cpython-313.pyc
│   │   │       ├── evidence_store.cpython-313.pyc
│   │   │       ├── exceptions.cpython-313.pyc
│   │   │       ├── index_store.cpython-313.pyc
│   │   │       ├── __init__.cpython-313.pyc
│   │   │       └── journal.cpython-313.pyc
│   │   ├── utils
│   │   │   ├── __init__.py
│   │   │   └── __pycache__
│   │   │       └── __init__.cpython-313.pyc
│   │   └── workers
│   │       ├── __init__.py
│   │       └── __pycache__
│   │           └── __init__.cpython-313.pyc
│   └── k501_aionarc.egg-info
│       ├── dependency_links.txt
│       ├── PKG-INFO
│       ├── requires.txt
│       ├── SOURCES.txt
│       └── top_level.txt
├── tests
│   ├── e2e
│   ├── fixtures
│   │   ├── audits
│   │   ├── documents
│   │   ├── graphs
│   │   └── proofs
│   ├── integration
│   └── unit
│       ├── __pycache__
│       │   ├── test_archive.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_archive_store.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_audit.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_axiom.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_canonical.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_evidence_store.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_frame.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_freeze.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_identity_validator.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_imports.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_index.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_index_runtime.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_index_store.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_journal.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_journal_runtime.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_kernel.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_lifecycle.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_pointer.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_proof.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_receipt.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_repository_structure.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_snapshot.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_state_object.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_transition.cpython-313-pytest-9.1.0.pyc
│       │   ├── test_transition_projection.cpython-313-pytest-9.1.0.pyc
│       │   └── test_transition_v2.cpython-313-pytest-9.1.0.pyc
│       ├── test_archive.py
│       ├── test_archive_store.py
│       ├── test_audit.py
│       ├── test_axiom.py
│       ├── test_canonical.py
│       ├── test_evidence_store.py
│       ├── test_frame.py
│       ├── test_freeze.py
│       ├── test_identity_validator.py
│       ├── test_imports.py
│       ├── test_index.py
│       ├── test_index_runtime.py
│       ├── test_index_store.py
│       ├── test_journal.py
│       ├── test_journal_runtime.py
│       ├── test_kernel.py
│       ├── test_lifecycle.py
│       ├── test_pointer.py
│       ├── test_proof.py
│       ├── test_receipt.py
│       ├── test_repository_structure.py
│       ├── test_snapshot.py
│       ├── test_state_object.py
│       ├── test_transition_projection.py
│       ├── test_transition.py
│       └── test_transition_v2.py
└── uv.lock

70 directories, 155 files
                                                                                                                   
┌──(harmony㉿peace)-[~/Projekte/k501-aionarc]
└─$ 
