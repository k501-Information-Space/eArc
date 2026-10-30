# eArc Repository State Anchor — Neutral Archive

**Anchor ID:** `EARC_REPOSITORY_STATE_ANCHOR_1793335241`  
**Role:** `NEUTRAL_DEVELOPMENT_ARCHIVE`  
**Repository authority:** `NONE`  
**Canonical authority:** `NONE`

Operator anchor: Unix `1793335241`, 2026-10-30 04:40:41 UTC /
05:40:41 Europe/Berlin. This identifies the intended observation context and
does not assert that every operation occurred at that exact second.

Parent main commit/tree: `0429b08b710252e4e83799b8e8d19f0705433a53`.
Parent recursive tree: 4,516 blobs, 62 trees, not truncated.

Earlier navigation used `CANONICAL` for the root Gateway and described
`canonical/` as a canonical reference area. That terminology was
inappropriate for this neutral archive and is corrected by the current
transition. The path remains unchanged as a legacy name; neither its name
nor its contents confer eArc authority. Files containing source declarations
remain unmodified.

A source may declare `CANONICAL`, `VALIDATED`, `RELEASED` or `CURRENT`
in its originating context. eArc records that as `source_declared_status`
with provenance. Its own archive authority remains `NONE`. An externally
canonical QH256 validation is stored as a `VALIDATION_ARTEFACT`, not as an
eArc canonical object.

The operator identifies `src/qh_core.c` as an old historical experimental
core. Its neutral object record is
`EARC_OBJECT_RECORD_qh_core.c_1793335241.json`. The source file is
unchanged; Git blob identity is distinct from its content SHA-256, which is
`NOT_COMPUTED`.

Rights default to `RIGHTS_OPEN`. Exact grants are listed in
`RIGHTS_REGISTER.json`. Conversation exports and workspaces require
rights, privacy and secret review before public publication.

This anchor does not verify every source, download every LFS payload, clear
all rights, run builds, select a current runtime or move historical root
state folders. Paired Markdown/JSON records carry the same anchor identity.
