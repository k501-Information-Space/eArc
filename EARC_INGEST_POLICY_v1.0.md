# eArc Ingestion Policy v1.0

**Policy ID:** `EARC_INGEST_POLICY_1.0`  
**Repository role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`  
**Authority:** `NONE`  
**Operator time anchor:** `1793335241`.

## 1. Purpose

This policy governs how historical and current K501 development material is admitted into eArc. It covers workspaces, code fragments, QH256 implementations and validations, pipelines, runtimes, publications, documents, conversations, test data and derived outputs.

Ingestion is not approval. Inclusion means only that an object was admitted to the archive with the recorded provenance and checks.

## 2. Admission sequence

`INTAKE → QUARANTINE → INVENTORY → BYTE_IDENTITY → PROVENANCE → RIGHTS_AND_PRIVACY_TRIAGE → NEUTRAL_CLASSIFICATION → RELATION_LINKING → APPEND_ONLY_COMMIT → READ_BACK`

A failed or incomplete stage remains explicitly OPEN. Do not label an object fully admitted or verified when required evidence is missing.

### Stage meanings

1. **INTAKE:** identify the requested batch and the operator's stated scope.
2. **QUARANTINE:** stage outside public publication until sensitive material, secrets and rights risks are assessed.
3. **INVENTORY:** capture exact paths, names, sizes, types and source boundaries.
4. **BYTE_IDENTITY:** compute a content hash with a known-good implementation; separately capture Git blob/LFS identities.
5. **PROVENANCE:** capture source system, original path/URL, original timestamp, source commit/release/DOI and collection time where known.
6. **RIGHTS_AND_PRIVACY_TRIAGE:** assess rights, personal data, credentials, confidential information and redistribution conditions.
7. **NEUTRAL_CLASSIFICATION:** assign an object class and source-declared claims without creating authority.
8. **RELATION_LINKING:** link versions, parent/derived relationships, conversations and release records only where evidence supports them.
9. **APPEND_ONLY_COMMIT:** add the original source object and its archive record without overwriting a prior occurrence.
10. **READ_BACK:** read back the committed object/record and verify the declared byte identity and manifest relations.

## 3. Source object versus archive metadata

The source object is preserved as received. Archive metadata is a separate record. If an incoming object requires normalization, extraction, decryption, OCR, redaction or conversion, preserve the original where lawful and safe; store the result as a derivative with an explicit parent reference and procedure.

No filename-based reclassification, automatic deduplication, silent rename or inferred path migration is permitted.

## 4. Status axes — not one global status

Use independent fields. Examples:

- Integrity: `NOT_CHECKED`, `HASH_MATCH`, `HASH_MISMATCH`, `UNAVAILABLE`.
- Provenance: `UNKNOWN`, `SOURCE_RECORDED`, `PARTIALLY_CORROBORATED`, `CORROBORATED`.
- Rights: `RIGHTS_OPEN`, `RIGHTS_REVIEWED`, `LICENSE_RECORDED`, `RESTRICTION_RECORDED`.
- Privacy: `NOT_REVIEWED`, `REVIEW_REQUIRED`, `CLEARED_FOR_PUBLICATION`, `RESTRICTED`.
- Content review: `NOT_REVIEWED`, `STRUCTURE_READ`, `CONTENT_READ`.
- Reproduction: `NOT_RUN`, `LOCAL_RESULT_RECORDED`, `INDEPENDENT_RESULT_RECORDED`.

These are evidence states, not quality rankings. The archive does not have a single `CANONICAL` or `CURRENT` status for its objects.

## 5. Source declarations

If a document says `CANONICAL`, record that value under `source_declared_status` together with its issuer, source context and time anchor. Do not write `earc_status=CANONICAL`. eArc authority is always `NONE`.

Examples:
- QH256 v2 validation may be source-declared canonical in its own QH256/Zenodo context. In eArc it is a `VALIDATION_ARTEFACT`.
- Old K501 canonical declarations are `HISTORICAL_DECLARATION` objects.
- An old `qh_core.c` is an `EXPERIMENTAL_CORE` or `CODE_FRAGMENT` when that is supported by source evidence or operator declaration; the archive does not present it as current.
- A later pipeline/runtime release is recorded with its own version and release reference, not promoted to a universal current version.

## 6. Conversation exports and workspace snapshots

Conversation exports and workspaces may contain credentials, personal information, private details, third-party content, copyrighted material or information not intended for public release.

They must pass a pre-publication privacy and rights review. A conversation is preserved as an exact export only where publication is permitted. If a redacted derivative is required, record that it is a derivative and retain the original only in an appropriately restricted location where lawful. Never publish secrets or access tokens.

## 7. Rights model

No repository-wide blanket licence is inferred. Every object defaults to `RIGHTS_OPEN` unless its exact path/object identity is covered by an explicit entry in `RIGHTS_REGISTER.json` or by a verified source-specific licence. MIT and CC BY 4.0 are available as separate licence instruments; they apply only to the exact objects recorded in the rights register and only where the grantor has the necessary rights.

## 8. Duplicate and version handling

- Same bytes do not prove same source identity.
- Different bytes do not by themselves prove a new version.
- Keep multiple occurrences and source locators distinct.
- Link a derivative to its exact parent.
- Link release versions only where version metadata or source evidence supports the relation.
- Never collapse historical versions because a later one is labelled current.

## 9. Commit and read-back

Before a public commit:
- verify the proposed object list and paths;
- validate archive record syntax;
- confirm that rights/privacy stages are complete for public publication;
- generate hashes using a correct implementation;
- create the commit;
- read back the committed objects and recompute hashes;
- preserve the exact commit/tree and any remaining OPEN checks.

A GitHub commit alone does not prove the full content of a Git LFS payload was downloaded or independently verified.

## 10. Stop conditions

Do not publish an item when it contains unresolved secrets, private personal data, restricted/confidential information, unclear third-party rights, or source material whose public redistribution is not authorized. Keep it in restricted staging or record the item as not admitted.

K501 :: UNKNOWN_BY_DEFAULT  
K501 :: PROOF_BEFORE_STATE  
K501 :: PRESERVE_HISTORY  
K501 :: NO_PHANTOM
