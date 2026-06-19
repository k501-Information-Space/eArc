# K501-Aionarc: Complete Implementation Index

## Phase 0: Project Foundation (Completed)

1. ✅ Architecture Overview (`docs/architecture/00_overview.md`)
    
2. ✅ Engineering Plan (Version 6.0, Transition-Centric)
    
3. ✅ JSON Schemas (10 schemas for all primitives)
    
4. ✅ Repository Structure (full folder manifest)
    
5. ✅ `pyproject.toml` (modern tooling: uv, ruff, pytest)
    
6. ✅ `Makefile` (all dev commands)
    
7. ✅ Structured Logging (`src/k501/observability/logs.py`, middleware)
    

---

## Phase 1: Core Ontology Runtime (Transition-Centric)

## Step 1.1: Core Primitives

8. ⬜  `src/k501/core/__init__.py`
    
9. ✅ `src/k501/core/axiom.py`
    
10.  ⬜ `src/k501/core/kernel.py`
    
11. ✅ `src/k501/core/frame.py`
    
12. ✅ `src/k501/core/snapshot.py`
    
13. ✅ `src/k501/core/freeze.py`
    
14. ✅ `src/k501/core/state_object.py` (materialized view)
    

## Step 1.2: Transition Core (NEW — Primary Object)

15. ⬜ `src/k501/core/identity_axiom.py` (Identity Axiom: content + provenance)
    
16. ⬜ `src/k501/core/transition.py` (StateTransition — primary object)
    
17. ⬜ `src/k501/core/transition_type.py` (TransitionType enum)
    
18. ⬜ `src/k501/core/transition_registry.py` (per-object-type rules)
    
19. ✅ `src/k501/core/lifecycle.py` (transition validation)
    

## Step 1.3: Utilities

20. ✅ `src/k501/utils/__init__.py`
    
21. ✅ `src/k501/utils/ids.py` (deterministic ID generation)
    
22. ✅ `src/k501/utils/hashing.py` (SHA-256 content hashing)
    
23. ⬜ `src/k501/utils/canonical_serialization.py` (RFC 8785 JCS)
    
24. ⬜ `src/k501/utils/identity.py` (transition-centric ID generation)
    
25. ⬜ `src/k501/utils/time.py` (time anchor utilities)
    

## Step 1.4: Unit Tests

26. ✅ `tests/unit/test_state_object.py`
    
27. ✅ `tests/unit/test_lineage.py`
    
28. ✅ `tests/unit/test_integrity.py`
    
29. ⬜ `tests/unit/test_transition.py` (transition creation, identity axiom)
    
30. ⬜ `tests/unit/test_transition_registry.py` (per-object-type rules)
    
31. ⬜ `tests/unit/test_canonical_serialization.py` (RFC 8785 compliance)
    

---

## Phase 2: Evidence Store (Transition-Centric)

## Step 2.1: Storage Layer

32. ⬜ `src/k501/storage/__init__.py`
    
33. ⬜ `src/k501/storage/jsonl.py` (JSONL file storage)
    
34. ⬜ `src/k501/storage/sqlite.py` (SQLite persistence)
    
35. ⬜ `src/k501/storage/blobs.py` (binary blob storage)
    

## Step 2.2: Transition Store

36. ⬜ `src/k501/evidence/__init__.py`
    
37. ⬜ `src/k501/evidence/transition_store.py` (append-only transition storage)
    
38. ⬜ `src/k501/evidence/state_store.py` (materialized view storage)
    
39. ⬜ `src/k501/evidence/ingest.py` (ingestion pipeline with CREATE transition)
    
40. ⬜ `src/k501/evidence/snapshot.py` (CREATE transition)
    
41. ⬜ `src/k501/evidence/freeze.py` (FREEZE transition)
    
42. ⬜ `src/k501/evidence/archive.py` (ARCHIVE transition)
    
43. ⬜ `src/k501/evidence/manifest.py` (ingestion manifests)
    

## Step 2.3: Governance Evidence

44. ⬜ `src/k501/evidence/proof.py` (VALIDATE/REJECT transitions)
    
45. ⬜ `src/k501/evidence/audit.py` (AUDIT transitions)
    

## Step 2.4: Integrity

46. ⬜ `src/k501/evidence/integrity.py` (hash verification, replay test)
    

## Step 2.5: Integration Tests

47. ⬜ `tests/integration/test_ingestion_pipeline.py`
    
48. ⬜ `tests/e2e/test_archive_replay.py` (identical transition_id on replay)
    
49. ⬜ `tests/e2e/test_identity_axiom.py` (same transition + different timestamp = same ID)
    

---

## Phase 3: Transition Graph (Not State Object Graph)

## Step 3.1: Graph Models (Transition-Centric)

50. ✅ `src/k501/graph/__init__.py`
    
51. ⬜ `src/k501/graph/transition_node.py` (Transition as node, not StateObject)
    
52. ⬜ `src/k501/graph/transition_edge.py` (Edge between transitions)
    
53. ✅ `src/k501/graph/models.py` (Node, Edge — needs update to transition-centric)
    

## Step 3.2: Graph Store

54. ✅ `src/k501/graph/store.py` (needs update to transition-centric)
    
55. ⬜ `src/k501/graph/index.py` (SQLite indexes for transitions)
    

## Step 3.3: Traversal API

56. ✅ `src/k501/graph/traverse.py` (needs update to transition-centric)
    
57. ⬜ `src/k501/graph/lineage.py` (transition chain reconstruction)
    
58. ⬜ `src/k501/graph/provenance.py` (proof/audit transition chain)
    

## Step 3.4: Query Layer

59. ✅ `src/k501/graph/query.py` (needs update to transition-centric)
    
60. ⬜ `src/k501/graph/filters.py` (temporal and namespace filters)
    

## Step 3.5: Validation

61. ✅ `src/k501/graph/validator.py` (needs update to transition-centric)
    
62. ⬜ `src/k501/graph/replay_validator.py` (identical transition_id on replay)
    

## Step 3.6: Integration Tests

63. ⬜ `tests/integration/test_graph_traversal.py`
    
64. ⬜ `tests/integration/test_transition_graph.py` (transition nodes, not state objects)
    
65. ⬜ `tests/e2e/test_provenance_query.py`
    

---

## Phase 4: Retrieval Engine (Hybrid + Provenance)

## Step 4.1: Chunking & Embedding

66. ⬜ `src/k501/retrieval/__init__.py`
    
67. ⬜ `src/k501/retrieval/chunker.py` (document chunking)
    
68. ⬜ `src/k501/retrieval/embedder.py` (Ollama + Nomic embeddings)
    

## Step 4.2: Indexes

69. ⬜ `src/k501/retrieval/vector_index.py` (SQLite + numpy)
    
70. ⬜ `src/k501/retrieval/lexical_index.py` (keyword search)
    

## Step 4.3: Ranking

71. ⬜ `src/k501/retrieval/ranker.py` (multi-signal ranker)
    
72. ⬜ `src/k501/retrieval/hybrid.py` (hybrid search combiner)
    
73. ⬜ `src/k501/retrieval/explain.py` (score decomposition)
    

## Step 4.4: Search API

74. ⬜ `src/k501/retrieval/search.py` (return StateObjects, not chunks)
    

## Step 4.5: Integration Tests

75. ⬜ `tests/integration/test_hybrid_retrieval.py`
    
76. ⬜ `tests/e2e/test_provenance_query.py`
    

---

## Phase 5: Governance Engine (Transition-Based)

## Step 5.1: Claims (Transition-Based)

77. ⬜ `src/k501/governance/__init__.py`
    
78. ⬜ `src/k501/governance/claims.py` (CREATE transition for claim)
    

## Step 5.2: Validation (Transition-Based)

79. ⬜ `src/k501/governance/validation.py` (VALIDATE/REJECT transitions)
    

## Step 5.3: Beliefs (Transition-Based)

80. ⬜ `src/k501/governance/beliefs.py` (ACCEPT/REJECT/CONTEST transitions)
    

## Step 5.4: Conflict Resolution (Transition-Based)

81. ⬜ `src/k501/governance/conflict.py` (detect conflicting belief transitions)
    

## Step 5.5: Policy Engine

82. ⬜ `src/k501/governance/policy.py` (pluggable policies per object type)
    

## Step 5.6: Integration Tests

83. ⬜ `tests/integration/test_governance_flow.py`
    
84. ⬜ `tests/e2e/test_conflict_resolution.py`
    

---

## Phase 6: Agent Interface (Transition-API)

## Step 6.1: Memory API (Transition-Based)

85. ⬜ `src/k501/agent/__init__.py`
    
86. ⬜ `src/k501/agent/memory_api.py` (get transitions, state objects, provenance)
    
87. ⬜ `src/k501/agent/context.py` (context bundle construction)
    

## Step 6.2: Tools (MCP-Compatible)

88. ⬜ `src/k501/agent/tools.py` (MCP-compatible tools)
    
89. ⬜ `src/k501/agent/provenance_tools.py` (lookup_proof_transitions, inspect_audit_transitions)
    

## Step 6.3: API Routes

90. ⬜ `src/k501/api/routes/evidence.py`
    
91. ⬜ `src/k501/api/routes/graph.py`
    
92. ⬜ `src/k501/api/routes/retrieval.py`
    
93. ⬜ `src/k501/api/routes/governance.py`
    
94. ⬜ `src/k501/api/routes/agent.py`
    
95. ⬜ `src/k501/api/routes/audit.py` (replay transition chain)
    
96. ⬜ `src/k501/api/routes/lineage.py` (traverse transition graph)
    

## Step 6.4: Namespace Isolation

97. ⬜ `src/k501/agent/namespaces.py` (multi-agent namespace separation)
    

## Step 6.5: Integration Tests

98. ⬜ `tests/integration/test_agent_api.py`
    
99. ⬜ `tests/e2e/test_multi_agent_namespace.py`
    

---

## Phase 7: Documentation

## Step 7.1: Architecture Docs

100. ⬜ `docs/architecture/01_ontology.md` (transition-centric ontology)
    
101. ⬜ `docs/architecture/02_state_model.md` (StateObject = materialized view)
    
102. ⬜ `docs/architecture/03_reference_graph.md` (transition graph)
    
103. ⬜ `docs/architecture/04_governance.md` (transition-based governance)
    
104. ⬜ `docs/architecture/05_retrieval.md` (hybrid + provenance)
    
105. ⬜ `docs/architecture/06_agent_interface.md` (transition-API)
    
106. ⬜ `docs/architecture/07_roadmap.md`
    

## Step 7.2: API Docs

107. ⬜ `docs/api/evidence.md`
    
108. ⬜ `docs/api/graph.md`
    
109. ⬜ `docs/api/retrieval.md`
    
110. ⬜ `docs/api/governance.md`
    
111. ⬜ `docs/api/agent.md`
    

## Step 7.3: Developer Docs

112. ⬜ `docs/dev/getting_started.md`
    
113. ⬜ `docs/dev/testing.md`
    
114. ⬜ `docs/dev/deployment.md`
    

---

## Phase 8: Final Validation

## Step 8.1: End-to-End Tests

115. ⬜ `tests/e2e/test_full_lifecycle.py` (CREATE → FREEZE → ARCHIVE)
    
116. ⬜ `tests/e2e/test_identity_axiom_full.py` (replay with identical transition_id)
    
117. ⬜ `tests/e2e/test_transition_graph_replay.py` (identical graph on replay)
    

## Step 8.2: Performance Tests

118. ⬜ `tests/performance/test_retrieval_benchmark.py`
    
119. ⬜ `tests/performance/test_graph_traversal_benchmark.py`
    

## Step 8.3: Security Tests

120. ⬜ `tests/security/test_namespace_isolation.py`
    
121. ⬜ `tests/security/test_integrity_verification.py`
    

---

## Summary

**Total Steps:** 121

**Completed:** 31 (26%)

**Remaining:** 90 (74%)

**Critical Path:**

1. Transition Core (Steps 15–24)
    
2. Evidence Store (Steps 32–49)
    
3. Transition Graph (Steps 50–65)
    
4. Retrieval Engine (Steps 66–76)
    
5. Governance Engine (Steps 77–84)
    
6. Agent Interface (Steps 85–99)
    

**Next Immediate Step:** Step 15 — `src/k501/core/identity_axiom.py` (Identity Axiom: content + provenance)