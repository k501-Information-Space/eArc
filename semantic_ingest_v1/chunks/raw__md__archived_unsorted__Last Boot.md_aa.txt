K501_BOOTFRAME_ALPHA_1
version: 1.0
state: FREEZE
mode: READ_ONLY
execution: NONE
mutation: DISABLED
simulation: DISABLED

SYSTEM_ID: K501-GW-ALPHA-1

PRINCIPLES:
- APPEND_ONLY
- REFERENCE_ONLY
- NO_INPUT_SURFACE
- NO_RUNTIME_GENERATION
- NO_IP_STORAGE
- NO_USER_AGENT_STORAGE

ARCHITECTURE:

CLIENT:
- index.html
- gateway.js
- gateway.css
- cyberpunk.css (optional visual layer)
- polling: 15s
- badge states: INIT | OK | ERR

SERVER:
- emit.php (POST only)
- counter.php (GET only)
- method-gated via .htaccess
- payload max: 4KB
- type allow-list:
    FRAME_VISIT
    FRAME_VIEW
    FRAME_CLICK

STORAGE:
- frames.ndjson (append-only)
- counters.json (atomic snapshot)
- direct /frames access blocked

EVENT MODEL:

FRAME_VISIT:
  id
  t (ISO8601 Z)
  path
  payload: {}

FRAME_VIEW:
  id
  t (ISO8601 Z)
  path
  payload:
    ref (optional)

FRAME_CLICK:
  id
  t (ISO8601 Z)
  path
  payload:
    label
    href (sanitized)

COUNTER SNAPSHOT:
{
  visits: int,
  views: int,
  clicks: int,
  last: {
    type,
    t,
    path
  }
}

LOG FORMAT:
NDJSON
one JSON object per line
append-only
no rewrite
no compaction

SECURITY:
- Content-Type validation
- Method enforcement
- ISO time validation
- href sanitation
- atomic write via tmp + rename
- file lock during append

INTERFACE CONTRACT:

counter.php →
{
  counts,
  last,
  lastFrames[]
}

emit.php →
{
  ok: true | false
}

CONSTRAINTS:

- No dynamic routing
- No database
- No session persistence (except client sessionStorage throttle)
- No identity layer
- No authentication
- No admin surface
- No telemetry expansion beyond allow-list

STATUS:
Operational
Minimal
Deterministic
Stable

FREEZE_MARKER:
K501-GW-ALPHA-1