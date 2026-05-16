id: GX-OUT-1772405316-RCPT-01

ts.utc: 2026-03-01T22:48:36Z

ts.unix: 1772405316

mode: DATA

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

artifact: QH256_RECEIPT_EXAMPLES_V1_DRAFT

status: DRAFT

profile: strict_v1

notes:

  - Receipts correspond to previously emitted TV1–TV3.

  - header_hex values are canonical hexlower.

id: GX-OUT-1772405316-RCPT-02

ts.utc: 2026-03-01T22:48:36Z

ts.unix: 1772405316

mode: DATA

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

receipt_example:

  name: TV1_ALL_GUARD_CANONICAL

  input_ref: TV1_ALL_GUARD_CANONICAL

  profile: strict_v1

  

receipt:

  type: QH_VALIDATE

  result: PASS

  family_bits: "11111111"

  version_bits: "11111111"

  profile_bits: "11111111"

  guard:

    status: OK

    violations: 0

  header_hex: ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

id: GX-OUT-1772405316-RCPT-03

ts.utc: 2026-03-01T22:48:36Z

ts.unix: 1772405316

mode: DATA

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

receipt_example:

  name: TV2_CORE_TRUE_GUARD_OK

  input_ref: TV2_CORE_TRUE_GUARD_OK

  profile: strict_v1

  

receipt:

  type: QH_VALIDATE

  result: PASS

  family_bits: "10101010"

  version_bits: "10101010"

  profile_bits: "10101010"

  guard:

    status: OK

    violations: 0

  header_hex: aaaaaaaaaaaaaaaa00000000000000000000000000000000ffffffffffffffff

id: GX-OUT-1772405316-RCPT-04

ts.utc: 2026-03-01T22:48:36Z

ts.unix: 1772405316

mode: DATA

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

receipt_example:

  name: TV3_GUARD_VIOLATION

  input_ref: TV3_GUARD_VIOLATION

  profile: strict_v1

  

receipt:

  type: QH_VALIDATE

  result: FAIL

  family_bits: "10101010"

  version_bits: "10101010"

  profile_bits: "10101010"

  guard:

    status: FAIL

    violations: 1

  header_hex: aaaaaaaaaaaaaaaa00000000000000000000000000000000fffffffffffffffc

id: GX-OUT-1772405316-RCPT-05

ts.utc: 2026-03-01T22:48:36Z

ts.unix: 1772405316

mode: NOTE

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

next_gate:

  - optional: constant-time hardening notes

  - optional: reference implementation (C or Go)

  - optional: freeze candidate review

  

status: RECEIPT_PHASE_ACTIVE

🕊️💡