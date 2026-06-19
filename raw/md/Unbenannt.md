Below is a repository layout that fits K501-Aionarc as a provenance-first memory system, with clear boundaries for evidence, graph, retrieval, governance, and agents. I’ve structured it so the codebase can grow without collapsing the architecture back into generic RAG.[[github](https://github.com/axiomhq/agent-memory)]

## Repository Structure

text

`k501-aionarc/ ├── README.md ├── LICENSE ├── pyproject.toml ├── uv.lock ├── .gitignore ├── .env.example ├── docker-compose.yml ├── Makefile ├── ruff.toml ├── mypy.ini ├── pytest.ini ├── docs/ │   ├── architecture/ │   │   ├── 00_overview.md │   │   ├── 01_ontology.md │   │   ├── 02_state_model.md │   │   ├── 03_reference_graph.md │   │   ├── 04_governance.md │   │   ├── 05_retrieval.md │   │   ├── 06_agent_interface.md │   │   └── 07_roadmap.md │   ├── api/ │   │   ├── openapi.yaml │   │   ├── mcp_tools.md │   │   └── examples.md │   ├── schemas/ │   │   ├── state_object.schema.json │   │   ├── evidence.schema.json │   │   ├── frame.schema.json │   │   ├── snapshot.schema.json │   │   ├── freeze.schema.json │   │   ├── archive.schema.json │   │   ├── proof.schema.json │   │   ├── audit.schema.json │   │   ├── claim.schema.json │   │   ├── belief.schema.json │   │   └── graph.schema.json │   ├── runbooks/ │   │   ├── ingestion.md │   │   ├── validation.md │   │   ├── recovery.md │   │   ├── migration.md │   │   └── observability.md │   └── adr/ │       ├── 0001-axiom-and-state-object.md │       ├── 0002-append-only-evidence.md │       ├── 0003-reference-graph.md │       ├── 0004-hybrid-retrieval.md │       └── 0005-governance-layer.md ├── configs/ │   ├── app.yaml │   ├── logging.yaml │   ├── retrieval.yaml │   ├── governance.yaml │   ├── graph.yaml │   └── embeddings.yaml ├── data/ │   ├── archive/ │   ├── manifests/ │   ├── proofs/ │   ├── audits/ │   ├── claims/ │   ├── beliefs/ │   ├── snapshots/ │   ├── freezes/ │   └── indexes/ ├── scripts/ │   ├── bootstrap.sh │   ├── ingest.py │   ├── freeze.py │   ├── validate.py │   ├── build_index.py │   ├── migrate_graph.py │   ├── replay_audit.py │   └── benchmark_retrieval.py ├── tests/ │   ├── unit/ │   │   ├── test_state_object.py │   │   ├── test_lineage.py │   │   ├── test_integrity.py │   │   ├── test_claims.py │   │   └── test_beliefs.py │   ├── integration/ │   │   ├── test_ingestion_pipeline.py │   │   ├── test_graph_traversal.py │   │   ├── test_hybrid_retrieval.py │   │   ├── test_governance_flow.py │   │   └── test_agent_api.py │   ├── e2e/ │   │   ├── test_archive_replay.py │   │   ├── test_provenance_query.py │   │   └── test_multi_agent_namespace.py │   └── fixtures/ │       ├── documents/ │       ├── graphs/ │       ├── proofs/ │       └── audits/ ├── benchmarks/ │   ├── datasets/ │   ├── queries/ │   ├── expected/ │   ├── retrieval_benchmark.py │   ├── provenance_benchmark.py │   ├── governance_benchmark.py │   └── report_template.md └── src/     └── k501/        ├── __init__.py        ├── app.py        ├── api/        │   ├── __init__.py        │   ├── http.py        │   ├── mcp.py        │   ├── routes/        │   │   ├── evidence.py        │   │   ├── graph.py        │   │   ├── retrieval.py        │   │   ├── governance.py        │   │   └── agent.py        │   └── middleware/        │       ├── auth.py        │       ├── audit_log.py        │       └── provenance.py        ├── core/        │   ├── __init__.py        │   ├── axiom.py        │   ├── kernel.py        │   ├── frame.py        │   ├── snapshot.py        │   ├── freeze.py        │   ├── state_object.py        │   └── lifecycle.py        ├── evidence/        │   ├── __init__.py        │   ├── store.py        │   ├── ingest.py        │   ├── archive.py        │   ├── manifest.py        │   └── integrity.py        ├── graph/        │   ├── __init__.py        │   ├── models.py        │   ├── store.py        │   ├── traverse.py        │   ├── lineage.py        │   └── query.py        ├── retrieval/        │   ├── __init__.py        │   ├── chunker.py        │   ├── embedder.py        │   ├── index.py        │   ├── ranker.py        │   ├── hybrid.py        │   └── explain.py        ├── governance/        │   ├── __init__.py        │   ├── claims.py        │   ├── validation.py        │   ├── beliefs.py        │   ├── conflict.py        │   └── policy.py        ├── agent/        │   ├── __init__.py        │   ├── context.py        │   ├── tools.py        │   ├── memory_api.py        │   └── namespaces.py        ├── embeddings/        │   ├── __init__.py        │   ├── ollama.py        │   ├── nomic.py        │   └── models.py        ├── storage/        │   ├── __init__.py        │   ├── jsonl.py        │   ├── sqlite.py        │   ├── vector.py        │   └── blobs.py        ├── observability/        │   ├── __init__.py        │   ├── logs.py        │   ├── metrics.py        │   ├── traces.py        │   └── audit.py        ├── utils/        │   ├── __init__.py        │   ├── ids.py        │   ├── hashing.py        │   ├── time.py        │   ├── serialization.py        │   └── errors.py        └── workers/            ├── __init__.py            ├── ingestion_worker.py            ├── indexing_worker.py            ├── validation_worker.py            └── audit_worker.py`

## File Manifest

## Root files

- `README.md` — project overview and developer onboarding.
    
- `LICENSE` — license text.
    
- `pyproject.toml` — Python dependency and build config.
    
- `uv.lock` — locked dependency graph.
    
- `.gitignore` — repo exclusions.
    
- `.env.example` — sample environment variables.
    
- `docker-compose.yml` — local dev stack.
    
- `Makefile` — common build, test, and run commands.
    
- `ruff.toml` — lint formatting configuration.
    
- `mypy.ini` — type checking configuration.
    
- `pytest.ini` — test configuration.
    

## Docs

- `docs/architecture/00_overview.md` — system intent and plane separation.
    
- `docs/architecture/01_ontology.md` — Axiom, Kernel, Frame, Snapshot, Freeze, Archive.
    
- `docs/architecture/02_state_model.md` — State Object and lifecycle rules.
    
- `docs/architecture/03_reference_graph.md` — graph design and traversal.
    
- `docs/architecture/04_governance.md` — claim/belief/validation model.
    
- `docs/architecture/05_retrieval.md` — hybrid retrieval design.
    
- `docs/architecture/06_agent_interface.md` — agent memory contract.
    
- `docs/architecture/07_roadmap.md` — milestones and release phases.
    
- `docs/api/openapi.yaml` — HTTP API definition.
    
- `docs/api/mcp_tools.md` — MCP tool definitions.
    
- `docs/api/examples.md` — request/response examples.
    
- `docs/schemas/*.json` — canonical JSON Schemas.
    
- `docs/runbooks/*.md` — operational procedures.
    
- `docs/adr/*.md` — architecture decision records.
    

## Source packages

- `src/k501/app.py` — application entrypoint.
    
- `src/k501/api/http.py` — HTTP server setup.
    
- `src/k501/api/mcp.py` — MCP server setup.
    
- `src/k501/api/routes/*` — route handlers.
    
- `src/k501/core/*` — ontology primitives and lifecycle.
    
- `src/k501/evidence/*` — archive and integrity management.
    
- `src/k501/graph/*` — provenance graph models and queries.
    
- `src/k501/retrieval/*` — chunking, embedding, ranking, retrieval.
    
- `src/k501/governance/*` — claims, beliefs, conflicts, policies.
    
- `src/k501/agent/*` — memory-facing agent API.
    
- `src/k501/embeddings/*` — local embedding backends.
    
- `src/k501/storage/*` — persistence adapters.
    
- `src/k501/observability/*` — logs, metrics, traces, audits.
    
- `src/k501/utils/*` — IDs, hashing, serialization, time, errors.
    
- `src/k501/workers/*` — async background jobs.
    

## Data directories

- `data/archive/` — frozen archive payloads.
    
- `data/manifests/` — ingestion manifests.
    
- `data/proofs/` — proof artifacts.
    
- `data/audits/` — audit records.
    
- `data/claims/` — claim records.
    
- `data/beliefs/` — belief records.
    
- `data/snapshots/` — snapshot artifacts.
    
- `data/freezes/` — freeze artifacts.
    
- `data/indexes/` — vector and lexical indexes.
    

## Tests and benchmarks

- `tests/unit/*` — primitive-level tests.
    
- `tests/integration/*` — subsystem boundary tests.
    
- `tests/e2e/*` — full pipeline and replay tests.
    
- `tests/fixtures/*` — sample data.
    
- `benchmarks/*` — retrieval, provenance, and governance benchmarks.
    

## Notes on structure

This structure keeps the **evidence plane**, **reference graph**, **retrieval plane**, and **governance plane** separate so each can evolve independently. It also makes it easy to add MCP tooling later without mixing agent interfaces into core archive code.[[deepagentsdk](https://deepagentsdk.dev/docs/guides/agent-memory)]

If you want, I can next generate:

1. a complete `docs/architecture/00_overview.md`,
    
2. the JSON Schemas for all core objects, or
    
3. a ready-to-use `pyproject.toml` and `Makefile`.