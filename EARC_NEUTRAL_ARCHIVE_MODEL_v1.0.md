# eArc Neutral Archive Model v1.0

**Repository:** `k501-Information-Space/eArc`  
**Model ID:** `EARC_NEUTRAL_ARCHIVE_MODEL_1.0`  
**Operator time anchor:** Unix `1793335241` — 2026-10-30 04:40:41 UTC / 05:40:41 Europe/Berlin.  
**Repository role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`  
**Repository authority:** `NONE`  
**Canonical authority:** `NONE`

## 1. Governing definition

eArc is a neutral, append-only development archive for the historical and evolving K501 work corpus.

It preserves source objects, development artefacts, code fragments, workspaces, QH256 cores and validations, pipeline/runtime versions, publications, exported conversations, tests, reports, derived data and the relationships between them.

**eArc stores artefacts and records their provenance. eArc does not canonize, ratify, approve, endorse, select, deprecate or establish the truth of an artefact.**

No object receives canonical authority merely because it is stored, indexed, hashed, placed in a directory, linked from a Gateway, or described as canonical by its original source.

## 2. Repository-level neutrality

The following are fixed repository-level properties:

- `REPOSITORY_ROLE = NEUTRAL_DEVELOPMENT_ARCHIVE`
- `REPOSITORY_AUTHORITY = NONE`
- `CANONICAL_AUTHORITY = NONE`
- `ENDORSEMENT = NONE`
- `VALIDATION_BY_STORAGE = NONE`
- `CURRENTNESS_BY_STORAGE = NONE`

A repository index is a map of observed objects and paths. A Gateway is a navigation interface. A manifest is an inventory statement. A checksum is an integrity datum for a precisely identified byte sequence. None of these grants normative authority.

## 3. Origin claims are preserved, not adopted

An archived object may contain or carry an origin-context declaration such as:

- `CANONICAL`
- `STABILIZED`
- `VALIDATED`
- `RELEASED`
- `CURRENT`
- `EXPERIMENTAL`
- `DRAFT`
- `OBSOLETE`

These values are retained only as **source-declared claims** with their source, issuer, timestamp, scope and evidence where known.

They do not become eArc states. The archive record must keep these fields separate:

| Field | Meaning |
|---|---|
| `source_declared_status` | Exact status stated by the source or issuing context. |
| `source_declared_by` | The person, project, repository, publisher or system that made that declaration, if known. |
| `source_declared_at` | Time anchor of the source declaration, if known. |
| `source_context` | The original repository, publication, release or workflow in which the declaration applied. |
| `earc_archive_role` | The object's neutral role in this archive. |
| `earc_assessment` | What eArc has actually observed or checked; default `NOT_ASSESSED`. |
| `earc_authority` | Always `NONE`. |

**Example — QH256 v2 validation:** A validation artefact may be canonical or formally released in its originating QH256/Zenodo context. In eArc it is an archived validation artefact with a preserved source claim and external reference. eArc does not declare it canonical, reproduce its tests, or transfer its source authority.

**Example — old canonical declarations:** Documents that once declared a canonical K501 state are retained as historical development declarations. Their text is not rewritten. Their declaration is not adopted by eArc.

## 4. Archive object classes

Classification describes the observed kind of stored object, not its authority or quality.

Permitted initial classes include:

- `WORKSPACE_SNAPSHOT`
- `CODE_FRAGMENT`
- `EXPERIMENTAL_CORE`
- `QH256_IMPLEMENTATION`
- `VALIDATION_ARTEFACT`
- `PIPELINE_RELEASE`
- `RUNTIME_RELEASE`
- `SPECIFICATION_DRAFT`
- `HISTORICAL_DECLARATION`
- `PUBLICATION_RECORD`
- `PUBLICATION_FILE`
- `CONVERSATION_EXPORT`
- `TEST_CORPUS`
- `TEST_OUTPUT`
- `BINARY_ARTEFACT`
- `DERIVED_DATA`
- `MANIFEST_OR_INDEX`
- `UNKNOWN`

A class is an archival descriptor. It does not establish that an object is complete, valid, safe, licensed, current or canonical.

## 5. Historical and current development material

eArc may contain multiple generations of the same subsystem: early workspaces, abandoned code fragments, experimental QH256 cores, validation packages, active pipeline candidates, later runtime releases and publications.

They are not to be collapsed into one "current" implementation.

For each object, record its own version, source, time, path, commit or release identity, and any source-declared lifecycle status. If no source proves currentness, use `UNKNOWN`. The archive must not select a winner based on a filename, directory location, later upload time or apparent version number.

An old experimental file remains a valid historical object even when newer implementations exist. A later release does not erase or rewrite earlier work.

## 6. Source, derivative, observation and interpretation

Keep these layers separate:

1. **Source object:** exact bytes received from the source context.
2. **Ingestion event:** when, how and from which source the object entered eArc.
3. **Archive record:** neutral metadata describing the object and its provenance.
4. **Derived object:** extraction, normalization, chunking, embedding, conversion or report generated from a source.
5. **Observation:** a result of a specified read or verification.
6. **Interpretation:** a separate human or model assessment, with author, timestamp, method and source references.

A derivative must reference its parent object and its generation procedure. It never replaces the source. A model summary is not a source object and must not be silently inserted as if it were an original conversation or document.

## 7. Identity and integrity

- Preserve original bytes whenever technically possible.
- Record exact byte length and a cryptographic content hash computed by a known-good, independently checked implementation.
- Keep Git blob identity, Git LFS pointer identity and downloaded LFS payload hash distinct.
- A Git tree listing is not a download or payload verification.
- A hash proves byte identity relative to the measured bytes; it does not prove authorship, truth, authority, completeness, licence or semantic equivalence.
- Equal hashes may indicate equal bytes, but do not silently merge object identities or erase distinct source occurrences.
- A path is a location, not an immutable object identity.
- A filename is not a source declaration or classification authority.

The historical directory name `canonical/` is retained as a legacy path in the current tree. Its name does not establish canonical status. The objects there are archived development artefacts and must be represented under the neutral model.

## 8. Ingestion safety and rights

Bulk imports are staged before public publication. Conversations, workspace snapshots, source archives and third-party materials require checks for secrets, access tokens, personal data, confidential content, third-party copyright and licence conditions.

No blanket permission is inferred from the fact that an object exists locally, was created during a conversation, or is already present in a public repository.

Rights are assessed per object or explicitly bounded group. Unknown rights remain `RIGHTS_OPEN`; absence of a licence file is not permission. See `LICENSE`, `LICENSE-MIT`, `LICENSE-CONTENT`, `LICENSE_MAP.md` and `RIGHTS_REGISTER.json`.

## 9. Append-only correction model

An erroneous archive classification is not corrected by rewriting the original source object. Add a new dated metadata observation that:

- references the exact object ID;
- records the earlier claim and its source;
- records the new observation;
- states who made it and when;
- describes the evidence and scope;
- leaves the original source bytes unchanged.

Conflicts are preserved. Unknown remains valid. An archive correction does not retroactively change what a source said at the time.

## 10. Relationship to K501 authority outside eArc

Canonical governance, release approval and global K501 state are determined outside eArc by the relevant project authority and its own approved records.

eArc may preserve a reference to such a decision, publication or canonical record. It does not become that authority, nor does it independently decide whether the external decision is still current.

An externally canonical QH256 validation can therefore be stored in eArc without making eArc a canonical repository and without making the archive copy a new canonical declaration.

## 11. Design invariant

**eArc is neutral about the authority of the objects it preserves. It is strict about the traceability of how those objects were obtained, represented and related.**

Preserve the artefact. Preserve its provenance. Preserve the original claim as a claim. Do not promote it into archive authority.

K501 :: PRESERVE_HISTORY  
K501 :: NO_INTERPRETATION  
K501 :: UNKNOWN_BY_DEFAULT  
K501 :: PROOF_BEFORE_STATE  
K501 :: RECONSTRUCT_BEFORE_EXTEND
