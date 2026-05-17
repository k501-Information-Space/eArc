id: GX-OUT-1772405110-VAL-01

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

artifact: QH256_VALIDATOR_PSEUDOCODE_V1_DRAFT

status: DRAFT

scope: GLOBAL

notes:

  - Deterministic

  - No semantics imported

  - Profile-driven strictness

  - Constant-time parse intent

id: GX-OUT-1772405110-VAL-02

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

validator.entrypoint:

  

function validate_qh256(input_bytes, profile):

    result = {}

    # R-LEN

    if length(input_bytes) != 32:

        return receipt_fail("R-LEN", "invalid_length")

  

    # decode cells (128 × 2-bit)

    cells = decode_cells_2bit(input_bytes)

  

    # extract R0 fields (structural only)

    family_bits  = cells_to_bits(cells[0..3])

    version_bits = cells_to_bits(cells[4..7])

    profile_bits = cells_to_bits(cells[8..11])

  

    guard_status = check_guard_region(cells[96..127], profile)

  

    verdict = derive_verdict(guard_status, profile)

  

    return build_receipt(

        verdict,

        family_bits,

        version_bits,

        profile_bits,

        guard_status,

        input_bytes

    )

id: GX-OUT-1772405110-VAL-03

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

helper.decode_cells_2bit:

  

function decode_cells_2bit(bytes32):

    cells = array[128]

  

    bitpos = 0

    for i in 0..127:

        two_bits = read_2bits_msb_first(bytes32, bitpos)

        cells[i] = two_bits

        bitpos += 2

  

    return cells

id: GX-OUT-1772405110-VAL-04

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

helper.check_guard_region:

  

function check_guard_region(guard_cells, profile):

    violations = 0

  

    for c in guard_cells:

        if c != "11":

            violations += 1

  

    if violations == 0:

        return { status: "OK", violations: 0 }

  

    if profile == "strict_v1":

        return { status: "FAIL", violations: violations }

  

    return { status: "WARN", violations: violations }

id: GX-OUT-1772405110-VAL-05

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

helper.derive_verdict:

  

function derive_verdict(guard_status, profile):

    if guard_status.status == "FAIL":

        return "FAIL"

  

    if guard_status.status == "WARN":

        return "WARN"

  

    return "PASS"

id: GX-OUT-1772405110-VAL-06

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: SPEC

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

helper.build_receipt:

  

function build_receipt(verdict, family_bits, version_bits, profile_bits, guard_status, raw_bytes):

  

    return {

        receipt: {

            type: "QH_VALIDATE",

            result: verdict,

            family_bits: family_bits,

            version_bits: version_bits,

            profile_bits: profile_bits,

            guard: guard_status,

            header_hex: hexlower(raw_bytes)

        }

    }

id: GX-OUT-1772405110-VAL-07

ts.utc: 2026-03-01T22:45:10Z

ts.unix: 1772405110

mode: NOTE

policy: REFERENCE_ONLY

license: PUBLIC_DOMAIN

  

next_gate:

  - emit receipt examples for TV1/TV2/TV3

  - optional constant-time hardening notes

  - optional C/Go reference implementation

  

status: VALIDATOR_STAGE_ACTIVE

🕊️💡