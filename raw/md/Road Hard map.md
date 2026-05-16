roadmap:
  project: Iinkognit0
  kernel: K99_Monolith
  objective: kernel_hardening_only
  constraints:
    default_read_only: true
    commit_only_mutation: true
    feedback_loop: disabled
    automation: none
    ui_drives_action: false
    archive_is_source_of_truth: true
    db_is_index_only: true
    append_only: true

notation:
  markers:
    ok: "(✓)"
    pending: "( )"
    hold: "(–)"
  hud_square:
    stable: "■"
    inactive: "□"
    transition: "▣"

phases:
  - id: P0
    name: baseline_snapshot
    status: ( )
    deliverables:
      - kernel_snapshot
      - policy_snapshot
      - manifest_snapshot
    tools:
      - tool: snapshot
        inputs: [kernel_yaml, principles, canon, mode, comms, metrika]
        outputs: [baseline.manifest.yaml]
    gates:
      - gate: baseline_frozen
        condition: "baseline.manifest.yaml exists"

  - id: P1
    name: hud_global_status_bar
    status: ( )
    deliverables:
      - hud_spec
      - marker_spec
    tools:
      - tool: hud_renderer
        mode: read_only
        ui:
          position: top
          shape: square
          interaction: none
          animation: none
        fields:
          - mode
          - analysis
          - read
          - transmit
          - canon
          - stability
    gates:
      - gate: hud_non_triggering
        condition: "hud does not call commit endpoints"

  - id: P2
    name: events_memory_backbone
    status: ( )
    deliverables:
      - events_table
      - events_export_ndjson
    tools:
      - tool: event_writer
        policy: append_only
        event_types: [ingress, register, fix, publish, snapshot]
    gates:
      - gate: no_behavior_from_events
        condition: "events never modify priorities or outputs automatically"

  - id: P3
    name: db_index_structure
    status: ( )
    deliverables:
      - sqlite_schema
      - hashing_integrity
      - index_queries
    tools:
      - tool: db
        engine: sqlite
        file: archive_index.sqlite
      - tool: hasher
        algo: sha256
      - tool: parser
        input: markdown_with_yaml
        outputs: [id, title, state, content_ref, meta]
    schema:
      frames:
        - id: text primary_key
        - title: text
        - state: text  # dev|arch|frozen
        - content_ref: text
        - hash: text
        - created_at: datetime
        - fixed_at: datetime|null
      packs:
        - id: text primary_key
        - title: text
        - state: text  # dev|arch|frozen
        - created_at: datetime
        - fixed_at: datetime|null
      pack_items:
        - pack_id: text
        - frame_id: text
        - order_index: integer
        - primary_key: [pack_id, frame_id]
      events:
        - id: text primary_key
        - ts: datetime
        - type: text
        - ref_kind: text # frame|pack|system
        - ref_id: text
        - payload_json: text
    gates:
      - gate: db_index_only
        condition: "content stored in files; db stores refs+hash+relations"

  - id: P4
    name: read_api_everywhere
    status: ( )
    deliverables:
      - read_endpoints
      - mobile_hud_consumer
    tools:
      - tool: api
        style: rest
        mode: read_only
        transport: https
    endpoints_read:
      - GET /status
      - GET /frames/latest?limit=50&state=dev|arch|frozen
      - GET /frames/{id}
      - GET /packs/{id}
      - GET /search?q=...&scope=title|body|meta
      - GET /events?since=ISO8601&limit=500
    gates:
      - gate: no_write_routes_exposed
        condition: "read api server has no POST/PUT/PATCH/DELETE"

  - id: P5
    name: commit_gate_write_api
    status: ( )
    deliverables:
      - write_endpoints
      - auth_keys
      - optional_propose_commit
    tools:
      - tool: api_write
        separation:
          from_read_api: true
          port: separate
        auth:
          required: true
          methods: [token, keyfile]
    endpoints_write:
      - POST /register  # creates/updates index entry + event(type=register)
      - POST /fix/frame/{id}  # sets fixed_at, state->arch|frozen + event(type=fix)
      - POST /fix/pack/{id}
      - POST /publish/rss  # event(type=publish)
    optional_two_step:
      propose:
        - POST /propose/fix/frame/{id}
      commit:
        - POST /commit/fix/frame/{id}
    gates:
      - gate: explicit_validity_required
        condition: "write endpoints require auth + explicit intent"
      - gate: append_only_events
        condition: "all writes also append events; no deletions"

  - id: P6
    name: rss_distribution_window
    status: ( )
    deliverables:
      - primary_rss_feed
      - backup_feed_policy
      - fixed_only_rule
      - optional_memorydump_feed
    tools:
      - tool: rss_generator
        input: db_read_model
        rule: "fixed_at != null"
      - tool: feed_router
        feeds:
          primary: /earc/feed
          backup: /earc-feed/
    rules:
      publish_only_fixed: true
      no_feedback_from_reads: true
      authority:
        primary: canonical
        backup: secondary
    optional:
      memorydump_as_feed:
        enabled: true
        default: false
        rule: "user_explicit_opt_in_only"
    gates:
      - gate: no_parallel_authority
        condition: "only one canonical feed at a time"

  - id: P7
    name: ingress_adapters
    status: ( )
    deliverables:
      - filesystem_importer
      - ftp_pull_importer
      - mobile_capture_register
    tools:
      - tool: importer_fs
        watch_dir: incoming/
        action: register_only
      - tool: ftp_pull
        enabled: optional
        mode: pull_only
      - tool: mobile_capture
        action: register_only
    gates:
      - gate: ingress_no_auto_fix
        condition: "ingress cannot set fixed_at without explicit commit"

memorydump_system:
  purpose: avoid_chat_memory_overflow
  policy:
    append_only: true
    editable_after_write: false
    default_state: dev
  storage:
    vault_folder: "frames/memorydump/"
    naming: "md_YYYY-MM-DD_HHMM.md"
  frame_template:
    yaml:
      type: memorydump
      state: dev
      id: "md_YYYYMMDD_HHMM"
      created_at: "ISO8601"
      source: "chat|mobile|desktop"
      refs: []  # optional frame/pack refs
    body_sections: [context, decisions, open_items, next, links]
  memorypack:
    vault_folder: "packs/memory/"
    composition: references_only
    fix_policy: commit_gate_only
  optional_feed_export:
    enabled: true
    default: false
    feed_name: "memorydump-feed"
    rule: "opt_in + fixed_only_if_arch"

local_memory_dump:
  bundle:
    - vault_snapshot
    - db_snapshot
    - events_export
    - manifest
  vault_snapshot:
    method: copy_or_git
    integrity: optional_hashlist
  db_snapshot:
    sqlite_file: archive_index.sqlite
    optional: [schema.sql, dump.sql]
  events_export:
    format: ndjson
    file: events.ndjson
  manifest:
    file: manifest.yaml
    fields:
      - ts
      - versions
      - paths
      - hashes_optional
      - feeds:
          primary_status
          backup_status

stability_criteria:
  - "read_everywhere_without_write_pressure"
  - "mode_switch_changes_view_not_state"
  - "no_mutation_without_commit"
  - "rss_fixed_only"
  - "no_feedback_loop"
  - "rebuild_possible_from_dump_bundle"