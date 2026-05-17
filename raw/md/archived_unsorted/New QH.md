QAL/QH32_BIT_REGISTRY
version: QAL-EXPERIMENTAL
mode: REFERENCE_ONLY
policy: APPEND_ONLY

spec_id: qal://k501/qh32/bit-registry/v0.1/1772298789
emit_id: qf09_emit
batch_id: qal://iinkognit0/batch/1772298789

ts:
  utc: 2026-02-28T17:13:09Z
  unix: 1772298789

source:
  action: stage3_formal_closure
  scope: "QH32 minimal bit-registry + TX/RX FSM (structural only)"
  basis:
    - stage2_frozen: qal://k501/axiomatics/stage2/1772296918
    - ids_patch_frozen: qal://k501/protocol/ids/v1
  constraints:
    - interpretation: forbidden
    - philosophy: forbidden
    - content_loss: forbidden
  id_policy: compliant_with_ids_v1

---

QH32_SPEC:

  total_bits: 32
  indexing:
    bit_order: msb0
    bit_positions: [0..31]
    encoding: unsigned

  invariants:
    - inv_id: QH32-INV-01
      statement: "QH32 is boundary-only; MUST NOT mutate QH56 core cells."
    - inv_id: QH32-INV-02
      statement: "Any state transition requiring receipt MUST emit receipt (append-only)."
    - inv_id: QH32-INV-03
      statement: "Rollback transitions are forbidden (no state undo; only forward by new frames)."
    - inv_id: QH32-INV-04
      statement: "If REJECT_WRITE=1 then any attempted core-write MUST be rejected and logged."

  fields:

    # -----------------------------------------
    # F0: VERSION (4 bits)
    # -----------------------------------------
    - field_id: QH32-F0
      name: qh32_version
      offset: 0
      width: 4
      type: u4
      allowed:
        - 0x0: reserved
        - 0x1: v0.1_current
      default: 0x1

    # -----------------------------------------
    # F1: DOMAIN (2 bits) 00=reserved,01=TX,10=RX,11=CTRL
    # -----------------------------------------
    - field_id: QH32-F1
      name: domain
      offset: 4
      width: 2
      type: enum2
      allowed:
        - 0b00: reserved
        - 0b01: TX
        - 0b10: RX
        - 0b11: CTRL
      default: 0b11

    # -----------------------------------------
    # F2: GATE_MODE (2 bits)
    # 00=CLOSED, 01=OPEN, 10=GUARDED, 11=LOCKED
    # -----------------------------------------
    - field_id: QH32-F2
      name: gate_mode
      offset: 6
      width: 2
      type: enum2
      allowed:
        - 0b00: CLOSED
        - 0b01: OPEN
        - 0b10: GUARDED
        - 0b11: LOCKED
      default: 0b10

    # -----------------------------------------
    # F3: DIR (1 bit) 0=INBOUND,1=OUTBOUND (relative to core)
    # -----------------------------------------
    - field_id: QH32-F3
      name: direction
      offset: 8
      width: 1
      type: enum1
      allowed:
        - 0: INBOUND
        - 1: OUTBOUND
      default: 0

    # -----------------------------------------
    # F4: RECEIPT_POLICY (3 bits)
    # bit0=RECEIPT_REQUIRED
    # bit1=RECEIPT_ON_REJECT
    # bit2=RECEIPT_ON_ACCEPT
    # -----------------------------------------
    - field_id: QH32-F4
      name: receipt_policy
      offset: 9
      width: 3
      type: bitset3
      flags:
        - bit: 0
          name: RECEIPT_REQUIRED
        - bit: 1
          name: RECEIPT_ON_REJECT
        - bit: 2
          name: RECEIPT_ON_ACCEPT
      default: 0b111

    # -----------------------------------------
    # F5: CORE_WRITE (2 bits)
    # 00=NONE,01=REQUESTED,10=FORBIDDEN,11=RESERVED
    # -----------------------------------------
    - field_id: QH32-F5
      name: core_write_intent
      offset: 12
      width: 2
      type: enum2
      allowed:
        - 0b00: NONE
        - 0b01: REQUESTED
        - 0b10: FORBIDDEN
        - 0b11: reserved
      default: 0b10

    # -----------------------------------------
    # F6: REJECT_WRITE (1 bit) hard stop
    # -----------------------------------------
    - field_id: QH32-F6
      name: reject_write
      offset: 14
      width: 1
      type: bool
      allowed: [0,1]
      default: 1

    # -----------------------------------------
    # F7: PAYLOAD_PRESENCE (2 bits)
    # 00=NONE,01=ATTACHED,10=EXTERNAL_REF,11=RESERVED
    # -----------------------------------------
    - field_id: QH32-F7
      name: payload_presence
      offset: 15
      width: 2
      type: enum2
      allowed:
        - 0b00: NONE
        - 0b01: ATTACHED
        - 0b10: EXTERNAL_REF
        - 0b11: reserved
      default: 0b01

    # -----------------------------------------
    # F8: TRANSFORM (3 bits) representation change only
    # 000=NONE,001=MD,010=YAML,011=SQL,100=TOKEN,101=BITSTRING,110=JCS,111=RESERVED
    # -----------------------------------------
    - field_id: QH32-F8
      name: transform
      offset: 17
      width: 3
      type: enum3
      allowed:
        - 0b000: NONE
        - 0b001: MD
        - 0b010: YAML
        - 0b011: SQL
        - 0b100: TOKEN
        - 0b101: BITSTRING
        - 0b110: JCS
        - 0b111: reserved
      default: 0b000

    # -----------------------------------------
    # F9: BOUNDARY_FLAGS (5 bits)
    # bit0=INTERPRETATION_FORBIDDEN (must be 1 in this mode)
    # bit1=NO_PHANTOM_ENFORCED
    # bit2=APPEND_ONLY_ENFORCED
    # bit3=CANON_CORE_PROTECTED
    # bit4=RESERVED
    # -----------------------------------------
    - field_id: QH32-F9
      name: boundary_flags
      offset: 20
      width: 5
      type: bitset5
      flags:
        - bit: 0
          name: INTERPRETATION_FORBIDDEN
        - bit: 1
          name: NO_PHANTOM_ENFORCED
        - bit: 2
          name: APPEND_ONLY_ENFORCED
        - bit: 3
          name: CANON_CORE_PROTECTED
        - bit: 4
          name: reserved
      default: 0b01111

    # -----------------------------------------
    # F10: STATE (4 bits) FSM state id
    # -----------------------------------------
    - field_id: QH32-F10
      name: fsm_state
      offset: 25
      width: 4
      type: u4
      allowed:
        - 0x0: S0_IDLE
        - 0x1: S1_TX_REQUEST
        - 0x2: S2_TX_ACCEPT
        - 0x3: S3_TX_REJECT
        - 0x4: S4_RX_REQUEST
        - 0x5: S5_RX_ACCEPT
        - 0x6: S6_RX_REJECT
        - 0x7: S7_CTRL_SEAL
        - 0x8: S8_CTRL_LOCK
        - 0x9: S9_CTRL_AUDIT
        - 0xA: reserved
        - 0xB: reserved
        - 0xC: reserved
        - 0xD: reserved
        - 0xE: reserved
        - 0xF: reserved
      default: 0x0

    # -----------------------------------------
    # F11: STATE_FLAGS (3 bits)
    # bit0=RECEIPT_EMITTED
    # bit1=VIOLATION_DETECTED
    # bit2=RESERVED
    # -----------------------------------------
    - field_id: QH32-F11
      name: state_flags
      offset: 29
      width: 3
      type: bitset3
      flags:
        - bit: 0
          name: RECEIPT_EMITTED
        - bit: 1
          name: VIOLATION_DETECTED
        - bit: 2
          name: reserved
      default: 0b000

---

QH32_FSM:

  name: "TX/RX Boundary FSM (append-only transitions)"
  states:
    - S0_IDLE
    - S1_TX_REQUEST
    - S2_TX_ACCEPT
    - S3_TX_REJECT
    - S4_RX_REQUEST
    - S5_RX_ACCEPT
    - S6_RX_REJECT
    - S7_CTRL_SEAL
    - S8_CTRL_LOCK
    - S9_CTRL_AUDIT

  transitions:

    - t_id: T0
      from: S0_IDLE
      to: S1_TX_REQUEST
      when:
        domain: TX
        gate_mode_in: [OPEN, GUARDED]
      actions:
        - "set fsm_state=S1_TX_REQUEST"
        - "if receipt_policy.RECEIPT_REQUIRED=1 => emit_receipt"

    - t_id: T1
      from: S1_TX_REQUEST
      to: S2_TX_ACCEPT
      when:
        domain: TX
        gate_mode_in: [OPEN]
        reject_write: 1
        core_write_intent: [NONE, FORBIDDEN]
      actions:
        - "set fsm_state=S2_TX_ACCEPT"
        - "if receipt_policy.RECEIPT_ON_ACCEPT=1 => emit_receipt"

    - t_id: T2
      from: S1_TX_REQUEST
      to: S3_TX_REJECT
      when:
        domain: TX
        any_of:
          - gate_mode_in: [CLOSED, LOCKED]
          - core_write_intent: [REQUESTED]
      actions:
        - "set fsm_state=S3_TX_REJECT"
        - "set state_flags.VIOLATION_DETECTED=1 if core_write_intent=REQUESTED"
        - "if receipt_policy.RECEIPT_ON_REJECT=1 => emit_receipt"

    - t_id: T3
      from: S0_IDLE
      to: S4_RX_REQUEST
      when:
        domain: RX
        gate_mode_in: [OPEN, GUARDED]
      actions:
        - "set fsm_state=S4_RX_REQUEST"
        - "if receipt_policy.RECEIPT_REQUIRED=1 => emit_receipt"

    - t_id: T4
      from: S4_RX_REQUEST
      to: S5_RX_ACCEPT
      when:
        domain: RX
        gate_mode_in: [OPEN, GUARDED]
      actions:
        - "set fsm_state=S5_RX_ACCEPT"
        - "if receipt_policy.RECEIPT_ON_ACCEPT=1 => emit_receipt"

    - t_id: T5
      from: S4_RX_REQUEST
      to: S6_RX_REJECT
      when:
        domain: RX
        gate_mode_in: [CLOSED, LOCKED]
      actions:
        - "set fsm_state=S6_RX_REJECT"
        - "if receipt_policy.RECEIPT_ON_REJECT=1 => emit_receipt"

    - t_id: T6
      from: S0_IDLE
      to: S7_CTRL_SEAL
      when:
        domain: CTRL
        gate_mode_in: [GUARDED]
      actions:
        - "set fsm_state=S7_CTRL_SEAL"
        - "emit_receipt"

    - t_id: T7
      from: S7_CTRL_SEAL
      to: S8_CTRL_LOCK
      when:
        domain: CTRL
        gate_mode_in: [GUARDED, LOCKED]
      actions:
        - "set gate_mode=LOCKED"
        - "set fsm_state=S8_CTRL_LOCK"
        - "emit_receipt"

    - t_id: T8
      from: S0_IDLE
      to: S9_CTRL_AUDIT
      when:
        domain: CTRL
        gate_mode_in: [CLOSED, LOCKED, GUARDED, OPEN]
      actions:
        - "set fsm_state=S9_CTRL_AUDIT"
        - "emit_receipt"

  forbidden:
    - rule_id: FSM-FORBID-01
      statement: "No rollback transitions (any state -> earlier state) are forbidden; new frames only."
    - rule_id: FSM-FORBID-02
      statement: "Any transition attempting core_write_intent=REQUESTED MUST be rejected and logged."

---

OPEN_GAPS_QH32:

  - gap_id: QH32-GAP-01
    topic: "Receipt frame schema (minimal) exact fields and linkage to emit_id/batch_id/freeze_id"
    status: open

  - gap_id: QH32-GAP-02
    topic: "GateMode default policy matrix per environment (dev/stage/prod) expressed structurally"
    status: open

  - gap_id: QH32-GAP-03
    topic: "Transform enum finalization (representation registry mapping IDs)"
    status: open

---

STATUS:
  stage3_wp: S3-WP1_bind_precondition_met_for_QH32
  qh32_registry: drafted
  canon_ready: false
  requires_confirmation: true
  drift_detected: false