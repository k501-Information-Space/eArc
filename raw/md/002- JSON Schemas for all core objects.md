I'll generate the full JSON Schemas for all core objects directly as text.

## JSON Schema: State Object (universal memory primitive)

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/state_object.schema.json",  "title": "StateObject",  "description": "Universal memory primitive for K501-Aionarc. Contains evidence, lineage, trust, retrieval links, and provenance.",  "type": "object",  "required": ["state_id", "namespace", "object_type", "version"],  "properties": {    "state_id": {      "type": "string",      "description": "Deterministic stable identifier for the state object."    },    "axiom_id": {      "type": "string",      "description": "Root axiom anchoring deterministic origin."    },    "namespace": {      "type": "string",      "description": "Logical namespace for access control and grouping."    },    "version": {      "type": "string",      "pattern": "^[0-9]+\\.[0-9]+\\.[0-9]+$",      "description": "Schema version of this object."    },    "object_type": {      "type": "string",      "enum": [        "axiom", "kernel", "frame", "snapshot", "freeze", "archive",        "chunk", "embedding", "proof", "audit", "receipt",        "claim", "belief", "namespace", "pointer", "time_anchor"      ],      "description": "Type of memory primitive."    },    "origin": {      "type": "object",      "properties": {        "frame_id": {"type": "string"},        "snapshot_id": {"type": "string"},        "freeze_id": {"type": "string"},        "archive_id": {"type": "string"}      }    },    "lineage": {      "type": "object",      "properties": {        "derived_from": {          "type": "array",          "items": {"type": "string"}        },        "ancestor_chain": {          "type": "array",          "items": {"type": "string"}        },        "transitive_root": {"type": "string"}      }    },    "validation": {      "type": "object",      "properties": {        "proof_id": {"type": "string"},        "audit_id": {"type": "string"},        "receipt_id": {"type": "string"},        "status": {          "type": "string",          "enum": ["pending", "validated", "rejected", "superseded"]        }      }    },    "trust": {      "type": "object",      "properties": {        "belief_status": {          "type": "string",          "enum": ["unknown", "candidate", "accepted", "contested", "rejected"]        },        "confidence": {"type": "number", "minimum": 0.0, "maximum": 1.0},        "support_score": {"type": "number", "minimum": 0.0}      }    },    "time": {      "type": "object",      "properties": {        "created_at": {"type": "string", "format": "date-time"},        "updated_at": {"type": "string", "format": "date-time"},        "time_anchor": {"type": "string"},        "valid_from": {"type": "string", "format": "date-time"},        "valid_to": {"type": "string", "format": "date-time"}      }    },    "retrieval": {      "type": "object",      "properties": {        "chunk_ids": {"type": "array", "items": {"type": "string"}},        "embedding_ids": {"type": "array", "items": {"type": "string"}},        "graph_refs": {"type": "array", "items": {"type": "string"}}      }    },    "provenance": {      "type": "object",      "properties": {        "source": {"type": "string"},        "writer": {"type": "string"},        "tool_chain": {"type": "array", "items": {"type": "string"}},        "signature": {"type": "string"}      }    },    "payload": {      "type": "object",      "properties": {        "content_hash": {"type": "string"},        "summary": {"type": "string"},        "metadata": {"type": "object"}      }    }  } }`

## JSON Schema: Frame

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/frame.schema.json",  "title": "Frame",  "description": "Executable or observable state slice. Bridge between runtime and archive.",  "type": "object",  "required": ["frame_id", "namespace", "kernel_id", "status", "created_at"],  "properties": {    "frame_id": {"type": "string"},    "namespace": {"type": "string"},    "kernel_id": {"type": "string"},    "status": {      "type": "string",      "enum": ["active", "frozen", "archived"]    },    "created_at": {"type": "string", "format": "date-time"},    "snapshot_id": {"type": "string"},    "metadata": {"type": "object"}  } }`

## JSON Schema: Snapshot

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/snapshot.schema.json",  "title": "Snapshot",  "description": "Consistent view of state for freeze and archive.",  "type": "object",  "required": ["snapshot_id", "frame_id", "created_at", "state_hash"],  "properties": {    "snapshot_id": {"type": "string"},    "frame_id": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "state_hash": {"type": "string"},    "freeze_id": {"type": "string"},    "metadata": {"type": "object"}  } }`

## JSON Schema: Freeze

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/freeze.schema.json",  "title": "Freeze",  "description": "Sealed immutable record of Snapshot. First governance boundary.",  "type": "object",  "required": ["freeze_id", "snapshot_id", "created_at", "content_hash"],  "properties": {    "freeze_id": {"type": "string"},    "snapshot_id": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "content_hash": {"type": "string"},    "archive_id": {"type": "string"},    "reason": {"type": "string"},    "metadata": {"type": "object"}  } }`

## JSON Schema: Archive

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/archive.schema.json",  "title": "Archive",  "description": "Append-only historical evidence.",  "type": "object",  "required": ["archive_id", "freeze_id", "created_at", "content_hash"],  "properties": {    "archive_id": {"type": "string"},    "freeze_id": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "content_hash": {"type": "string"},    "source": {"type": "string"},    "proof_id": {"type": "string"},    "audit_id": {"type": "string"},    "metadata": {"type": "object"}  } }`

## JSON Schema: Proof

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/proof.schema.json",  "title": "Proof",  "description": "Validation of claims about archived content.",  "type": "object",  "required": ["proof_id", "archive_id", "created_at", "status"],  "properties": {    "proof_id": {"type": "string"},    "archive_id": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "status": {      "type": "string",      "enum": ["pending", "valid", "invalid"]    },    "validator": {"type": "string"},    "evidence_refs": {      "type": "array",      "items": {"type": "string"}    },    "signature": {"type": "string"},    "metadata": {"type": "object"}  } }`

## JSON Schema: Audit

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/audit.schema.json",  "title": "Audit",  "description": "Policy compliance and integrity check.",  "type": "object",  "required": ["audit_id", "archive_id", "created_at", "status"],  "properties": {    "audit_id": {"type": "string"},    "archive_id": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "status": {      "type": "string",      "enum": ["pending", "passed", "failed"]    },    "auditor": {"type": "string"},    "policy_id": {"type": "string"},    "findings": {      "type": "array",      "items": {"type": "string"}    },    "metadata": {"type": "object"}  } }`

## JSON Schema: Claim

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/claim.schema.json",  "title": "Claim",  "description": "Derived assertion from evidence that must be validated.",  "type": "object",  "required": ["claim_id", "namespace", "assertion", "created_at"],  "properties": {    "claim_id": {"type": "string"},    "namespace": {"type": "string"},    "assertion": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "evidence_refs": {      "type": "array",      "items": {"type": "string"}    },    "validation_id": {"type": "string"},    "status": {      "type": "string",      "enum": ["pending", "validated", "rejected", "contested"]    },    "metadata": {"type": "object"}  } }`

## JSON Schema: Belief

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/belief.schema.json",  "title": "Belief",  "description": "Operational confidence state used by reasoning.",  "type": "object",  "required": ["belief_id", "claim_id", "status", "confidence", "created_at"],  "properties": {    "belief_id": {"type": "string"},    "claim_id": {"type": "string"},    "created_at": {"type": "string", "format": "date-time"},    "updated_at": {"type": "string", "format": "date-time"},    "status": {      "type": "string",      "enum": ["unknown", "candidate", "accepted", "contested", "rejected"]    },    "confidence": {"type": "number", "minimum": 0.0, "maximum": 1.0},    "support_score": {"type": "number", "minimum": 0.0},    "superseded_by": {"type": "string"},    "metadata": {"type": "object"}  } }`

## JSON Schema: Reference Graph

json

`{   "$schema": "https://json-schema.org/draft/2020-12/schema",  "$id": "https://k501-aionarc.dev/schemas/graph.schema.json",  "title": "ReferenceGraph",  "description": "Deterministic reference graph for provenance and lineage traversal.",  "type": "object",  "required": ["root_node_id", "nodes", "edges"],  "properties": {    "root_node_id": {"type": "string"},    "nodes": {      "type": "array",      "items": {        "type": "object",        "required": ["node_id", "node_type"],        "properties": {          "node_id": {"type": "string"},          "node_type": {            "type": "string",            "enum": [              "axiom", "kernel", "frame", "snapshot", "freeze", "archive",              "proof", "audit", "claim", "belief", "namespace", "pointer", "time_anchor"            ]          },          "attributes": {"type": "object"}        }      }    },    "edges": {      "type": "array",      "items": {        "type": "object",        "required": ["source_id", "edge_type", "target_id"],        "properties": {          "source_id": {"type": "string"},          "edge_type": {            "type": "string",            "enum": [              "derived_from", "validated_by", "audited_by",              "belongs_to", "references", "supersedes",              "temporal_before", "temporal_after"            ]          },          "target_id": {"type": "string"},          "attributes": {"type": "object"}        }      }    }  } }`

## Usage Notes

- Save these schemas to `docs/schemas/*.json` in the repository structure.
    
- Use JSON Schema draft 2020-12 for modern validation.
    
- The `state_object.schema.json` is the universal primitive; all other objects should be embeddable or convertible to it.
    
- The `graph.schema.json` defines the deterministic reference graph core to provenance traversal.
    
- All time fields use RFC 3339 date-time format.
    
- All IDs are deterministic stable identifiers, not random UUIDs.