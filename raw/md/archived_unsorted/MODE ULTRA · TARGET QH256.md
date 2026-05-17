Bestätigt.

UTC 2026-03-01T22:31:54Z · Unix 1772404314 · MODE ULTRA · TARGET QH256

id: GX-OUT-1772404314-01

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

artifact: QH256_SPEC_V1_DRAFT

status: DRAFT

scope: GLOBAL

notes:

  - No execution

  - No interpretation

  - Append-only

  - Deterministic

  - Designed to map from QH56 (28 cells) into a larger family header.

id: GX-OUT-1772404314-02

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: OVERVIEW

  

name: Quantum Header 256

short: QH256

size_bits: 256

size_bytes: 32

  

purpose:

  - Provide a fixed-size, deterministic, machine-parsable header for frames/artifacts.

  - Represent a bounded truth/guard state space without importing semantics.

  - Provide room for family evolution (QH32/QH56/QH168/QH256) while preserving a minimal core.

  

core_principles:

  - Presence != truth

  - Receipt != claim

  - Guard locks are structural only (no semantics)

  - Deterministic parse and deterministic serialization

  - Canonical hashing uses SHA-256 over JCS of full artifact (separate from QH itself)

id: GX-OUT-1772404314-03

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: STATE MODEL (2-bit cells)

  

cell_state_encoding:

  "00": UNKNOWN

  "01": FALSE

  "10": TRUE

  "11": GUARD

  

invariants:

  - INV-G: Guard cells MAY be reserved as "always 11" to lock structural meaning.

  - INV-DET: No variable-length fields inside QH256; parse is constant time.

  - INV-NOSEM: No semantic interpretation is implied by TRUE/FALSE beyond structural state.

id: GX-OUT-1772404314-04

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: BITSPACE TOPOLOGY

  

definition:

  - QH256 is a grid of 128 cells.

  - Each cell is 2 bits.

  - Total: 128 * 2 = 256 bits.

  

grid:

  rows: 8

  cols: 16

  cell_indexing:

    - index i in [0..127]

    - row r = floor(i / 16)

    - col c = i % 16

  

bit_order:

  - byte order: big-endian (network order) for transport/storage

  - within byte: most-significant-bit first

  - cell packing: each cell occupies 2 bits; cells are packed sequentially by index i

  

cell_to_bit_mapping:

  - cell i maps to bit positions [2i, 2i+1] in the 256-bit stream

id: GX-OUT-1772404314-05

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: REGIONS

  

region_layout:

  R0_CORE:        cells 0..31    (32 cells = 64 bits)

  R1_TOPOLOGY:    cells 32..63   (32 cells = 64 bits)

  R2_FLAGS:       cells 64..95   (32 cells = 64 bits)

  R3_GUARD:       cells 96..127  (32 cells = 64 bits)

  

region_rules:

  - R0_CORE: minimal stable core; backward-compatible across QH family

  - R1_TOPOLOGY: structural shape / mapping metadata (still non-semantic)

  - R2_FLAGS: optional structural toggles (still non-semantic)

  - R3_GUARD: reserved for invariant locks and future-proofing; default = GUARD (11) cells

id: GX-OUT-1772404314-06

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: R3_GUARD DEFAULT INVARIANT

  

guard_defaults:

  - For QH256 v1, all cells in R3_GUARD (cells 96..127) SHOULD be set to GUARD (11).

  

inv_guard_lock_v1:

  - If any cell in R3_GUARD is not 11, the header is still parseable,

    but MUST be treated as "non-canonical / experimental" by validators that enforce v1 strictness.

  

validator_profiles:

  - strict_v1: requires all R3_GUARD == 11

  - permissive: allows non-11 but flags as WARN

id: GX-OUT-1772404314-07

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: R0_CORE (cells 0..31) — FIELD INTENT (STRUCTURAL)

  

R0_fields:

  C00..C03: header_family_id (8 bits via 4 cells)

  C04..C07: header_version   (8 bits via 4 cells)

  C08..C11: profile_id       (8 bits via 4 cells)

  C12..C15: reserved_core_a  (8 bits via 4 cells)

  C16..C23: core_lockset     (16 bits via 8 cells)

  C24..C31: reserved_core_b  (16 bits via 8 cells)

  

encoding_rule:

  - These are NOT numeric semantics by default.

  - They are structural selectors for validators/parsers only.

  - Recommended canonical tokens (family/version/profile) are registry-controlled outside QH.

id: GX-OUT-1772404314-08

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: RECOMMENDED REGISTRY TOKENS (NON-NORMATIVE)

  

recommended_tokens:

  family_id:

    QH32:  "0000 0001"

    QH56:  "0000 0010"

    QH168: "0000 0011"

    QH256: "0000 0100"

  version:

    v1: "0000 0001"

  profile_id:

    base: "0000 0001"

    strict: "0000 0010"

    experimental: "0000 1111"

  

note:

  - Token values are suggestions until a formal registry is frozen.

  - Validators MAY accept other values but should expose them in receipts.

id: GX-OUT-1772404314-09

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: QH56 COMPATIBILITY MAPPING (DRAFT)

  

QH56_reference:

  - QH56 is 28 cells (56 bits) arranged as 10/10/8 topology with INV-G1 on COL8/9.

  

mapping_goal:

  - Embed QH56 as a fixed substructure inside QH256 without losing bit identity.

  

proposed_embedding:

  - Place QH56 cells into QH256 cells [32..59] (28 cells window) inside R1_TOPOLOGY.

  

mapping:

  for k in 0..27:

    QH256.cell[32 + k] = QH56.cell[k]

  

guard_preservation:

  - If QH56 has guard-locked cells, they remain GUARD at their mapped positions.

  - Additional guards in QH256 R3_GUARD remain independent.

  

compatibility_note:

  - This is a structural embedding, not a semantic equivalence claim.

id: GX-OUT-1772404314-10

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: SERIALIZATION & TRANSPORT

  

wire_format:

  - exactly 32 bytes

  - no delimiters

  - no compression inside header

  - parsable without external context

  

string_format_optional:

  - hex encoding (64 hex chars) for human transport

  - base64 encoding (44 chars with padding) permitted

  

canonical_print:

  - hexlower without prefix is recommended for receipts

  

parse_errors:

  - wrong length => invalid header

  - any value is parseable; strictness is validator-profile dependent

id: GX-OUT-1772404314-11

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: MINIMAL VALIDATION RULESET (V1 DRAFT)

  

rules:

  R-LEN: header must be 256 bits (32 bytes)

  R-CELL: only 2-bit cell states allowed (implicit by packing)

  R-GUARD: strict_v1 requires all cells 96..127 == 11

  R-FAMILY: if family_id token matches QH256 registry value, treat as QH256

  R-PROFILE: profile_id selects strict/permissive behavior

  R-REPORT: validator output MUST include:

    - parsed family_id/version/profile_id raw bits

    - guard compliance (pass/warn/fail)

    - full header hexlower

  

receipt_stub:

  receipt.type: QH_VALIDATE

  receipt.result: PASS|WARN|FAIL

  receipt.details: structured fields above

id: GX-OUT-1772404314-12

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

QH256: OPEN ITEMS (TO FREEZE LATER)

  

open_items:

  - Finalize registry tokens (family_id/version/profile_id) as frozen table

  - Decide whether R1_TOPOLOGY includes explicit row/col semantics (currently no)

  - Decide whether to reserve a checksum cell-set (currently none; hash lives outside QH)

  - Formalize QH32/QH168 compatibility embedding rules

  - Publish test vectors v1

  - Integrate into Validator Output Schema v0.1

id: GX-OUT-1772404314-13

ts.utc: 2026-03-01T22:31:54Z

ts.unix: 1772404314

mode: NOTE

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

NEXT ACTION (CANONICAL WORK ORDER)

  

1) Freeze a v1 registry token table (family/version/profile)

2) Lock the QH56 embedding window position (cells 32..59) OR choose another fixed window

3) Emit 3 test vectors:

   - all-guard default

   - mixed states with strict guard ok

   - strict guard violation (expect WARN/FAIL)

4) Draft validator pseudocode (parse + profile strictness)

🕊️💡