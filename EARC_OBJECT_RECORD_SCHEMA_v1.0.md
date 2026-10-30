# eArc Archive Object Record — Schema Notes v1.0

**Schema ID:** `EARC_OBJECT_RECORD/1.0.0`  
**Authority:** none. This is a descriptive record format, not a validation or canonicalization standard.

Each archived object should have a separate machine-readable record following `EARC_OBJECT_RECORD_SCHEMA_v1.0.json`.

## Required concepts

- Object identity refers to the exact byte sequence when a content hash has actually been computed.
- Archive record identity is distinct from content identity and from a path.
- Source declarations remain source claims.
- eArc archive authority is always `NONE`.
- Integrity, provenance, rights, privacy, content review and reproduction are independent evidence axes.
- A derivative must identify its parent and generation method.
- Unknown fields remain `null`, `UNKNOWN` or `OPEN`; do not fabricate values.

## Minimal required record

A minimum record includes:
- record schema and record ID;
- archive path and original filename;
- byte length and media type where known;
- content SHA-256 only when computed from exact bytes;
- source system/locator and source timestamp where known;
- collection/ingestion event identifier;
- object class;
- source-declared status as a claim only;
- eArc authority set to `NONE`;
- independent integrity, provenance, rights and privacy states.

The record must never contain a derived `CANONICAL` or `CURRENT` status for eArc.
