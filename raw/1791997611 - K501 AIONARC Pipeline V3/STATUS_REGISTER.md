# V3 Status Register

State anchor: Unix `1791997611` — 2026-10-14 17:06:51 UTC.

| Module | Status in this package | Evidence | Open boundary |
|---|---|---|---|
| QH256 v2 C core | Imported reference core, unchanged | Build and core test pass in package environment | Re-run on operator's Debian 13 host |
| SHA-256 | Imported support implementation | Used throughout scan and verification tests | No claim of external cryptographic certification |
| C CLI | Implemented alpha candidate | Compiles with warnings-as-errors under packaged flags | Host portability / runtime scale unknown |
| Filesystem scan | Implemented | Test fixture includes files, directory, symlink and binary | Concurrent/adversarial filesystem snapshot guarantees limited |
| Object/record identity | Implemented for V3 schema | Candidate reparse and rehash checks pass | Not compatible by claim with v2.1-C identity/record bytes |
| Append-only frames | Implemented | repeated frame refused; parent chain verified | Store copy/backup policy not automated |
| Proof-before-state | Implemented local contract | Proof persisted before state commit; tamper tests | No signature, and not a proof of external truth |
| Transition reconstruction | Implemented | expected events regenerated from parent/current state | Stress testing at large scale remains open |
| Per-object QH256 | Implemented V3 profile | QH hex is indexed and recomputed on verify | New mapping needs project owner review before canonization |
| Aggregate QH256 | Implemented with v2 `MERGE_K` | wire roundtrip and merge tests | Aggregate is lossy; interpret cell semantics carefully |
| Derived index | Implemented | each field/order/profile and per-object QH checked | Not a vector or semantic index |
| Gateway | Implemented | header + top-level entry sequence revalidated | Orientation only, not permissions |
| Text capture | Implemented basic formats | exact content hashes and UTF-8 checks; PDF through `pdftotext` if installed | DOCX extraction/OCR not implemented; 16 MiB/file, 256 MiB total caps |
| Lexical query | Implemented | query returns source identifiers/hashes/excerpts | ASCII-ish tokenization/substrings; not semantic or multilingual ranking |
| llama.cpp | Not integrated by design | Explicit non-goal for this version | Future adapter requires separate interface/proof gate |
| Python/C v2.1 parity | OPEN | Existing project R02 report shows field/order divergence | V3 does not claim parity or force v2.1 compatibility |
| Canonical release | NOT APPROVED | Package is labelled `3.0.0-alpha.0` | Owner review, licensing resolution, host run and gates needed |
