DUCKBOOTFRAME · K501 HMRI · iOS Local-First v0.2
UTC 2026-02-24T15:30:38Z · Unix 1771947038

Identity
A minimal, privacy-first integration concept using a DuckDuckGo-class browser surface
with a local K501/HMRI layer. Non-executive reference artifact. Deterministic intent.

Mode
- REFERENCE_ONLY
- APPEND_ONLY
- LOCAL_FIRST

Core Principle
State → Gate → Bundled Output

Authoritative Time Rule
The canonical time of every frame is defined exclusively by {ts.utc, ts.unix}.
ULID MAY provide identity and coarse ordering but MUST NOT define canonical time.

Hard Requirements
- All frames MUST include {ts.utc, ts.unix}.
- Serialization MUST be canonical and deterministic (JCS/RFC8785 or equivalent).
- Storage is local-only by default.
- Export is user-initiated only.
- No hidden telemetry.

Architecture (v0.2)

L1 · Surface Layer
- DuckDuckGo-class browser or Safari environment
- Share-first capture (current)
- Safari Web Extension (future)

L2 · Integration Facade
- Emits structured events
- Queries Gate policy before user-facing interruptions
- Triggers export pipeline

L3 · K501 Core
- Frame schema + append-only writer
- HMRI state estimator (CALM / FOCUSED / OVERLOADED)
- Deterministic Gate engine
- Lightweight index snapshots

L4 · Local Storage
- NDJSON append-only segments (daily rotation)
- manifest.json (counts, ranges, anomalies)
- No remote sync in v0.2

Required Frame Types (v0.2)
- SESSION_START
- SESSION_END
- FRAME_MARK
- HMRI_STATE
- GATE_DECISION
- EXPORT_ACTION

Optional Frame Types
- FRAME_NOTE
- BATCH_OPEN
- FOCUS_TOGGLE
- CLOCK_ANOMALY

Gate Policy (deterministic)

CALM:
  HP → PASS
  NP → PASS (banner downgradable)
  LP → BUFFER

FOCUSED:
  HP → PASS (quiet channel)
  NP → BUFFER
  LP → SUPPRESS

OVERLOADED:
  HP → PASS (emergency only)
  NP → BUFFER
  LP → SUPPRESS

Override Rules
- OPEN → PASS (except explicit user blocks)
- CLOSED → BUFFER except HP emergency

Reason Codes (stable)
- R01_FOCUS_ACTIVE
- R02_OVERLOAD_HIGH
- R03_LOW_PRIORITY_BATCH
- R04_CHANNEL_DOWNGRADE
- R05_USER_OVERRIDE_OPEN
- R06_USER_OVERRIDE_CLOSED

HMRI Estimator (v0.2)
Inputs:
- session minutes
- interaction rate
- batch-open frequency
- time-of-day
- optional manual focus toggle

Properties:
- saturating load score
- stability score
- hysteresis enforced
- snapshot every 5 minutes and on transitions

Ordering & Proof Strategy

Primary Order:
1. Append sequence
2. ts.unix (non-decreasing check)
3. ULID as tie-breaker only

Manifest Minimum
- frame_count
- time_range {start, end}
- type_counts
- anomaly_counts
- order_policy descriptor

Anomaly Handling
If local clock moves backward:
- emit CLOCK_ANOMALY frame
- writer SHOULD clamp to monotonic unix when feasible

iOS Execution Path

Phase 0 (current)
- PWA “K501 Pocket”
- Share-first capture
- Local NDJSON export
- Optional iSH validation tooling

Phase 1
- Safari Web Extension (automatic VISIT/VIEW)
- same K501 core

Phase 2
- Optional DuckDuckGo fork integration
- unchanged frame contract

Success Criteria (3-day field test)
- measurable reduction in user interruptions
- longer uninterrupted focus blocks
- subjective: “information feels navigable”
- deterministic exports validate cleanly

Non-Goals (v0.2)
- no cloud sync
- no AI dependency
- no system-wide notification interception
- no biometric inference

Stability Assessment
Structure coherent.
Time discipline preserved.
Append-only integrity intact.
Ready for controlled v0.2 field testing.

END OF DUCKBOOTFRAME