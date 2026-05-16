K501 · GATEKEEPER FSM · SW-LIFECYCLE HARDENING · v0.3 (FREEZE)
UTC 2026-02-24T16:22:16Z · Unix 1771950136
mode=REFERENCE_ONLY
rule=APPEND_ONLY
semantics=NONE

Scope
Close the v0.3 hardening of Gatekeeper FSM around Service Worker updates:
- robust waiting detection
- symmetric activation message
- multi-tab controllerchange safety
- deduped update-ready pipeline
- defensive safe-mode behavior (timeout/error path)

Accepted Enhancements (A–E)
A) Waiting-on-load handling:
- After register(), check reg.waiting (+ controller) and process update-ready without relying on updatefound.

B) postMessage symmetry:
- Client sends {type:"SW_ACTIVATE_NOW"}.
- Service Worker listens and triggers self.skipWaiting().

C) controllerchange multi-tab guard:
- Optional reload protected by one-shot guard to prevent loops/jarring multi-tab reload storms.

D) processUpdateReady() dedup:
- Single function handles both reg.waiting and installed->waiting transitions, preventing logic drift.

E) Error/timeout -> SAFE_MODE:
- On install stall/error conditions, Gatekeeper enters SAFE_MODE (receipt-first, suppress nags).

Artifacts Included
- v0.3 delta patch snippet (client + service worker message listener)
- minimal framework-free mock test harness (gate() decisions + mapSW transitions)

Integrity
- Deterministic intent preserved
- Append-only discipline preserved
- No feature explosion introduced
- Ready for basic integration test + controlled field validation

END