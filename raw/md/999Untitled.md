spec:
  version: "1.0"

kernel:
  id: k99_monolith
  name: K99 Monolith
  type: monolith
  state: canonical
  symbol: "■"

mode:
  current: DEV
  dualsystem:
    dev: perception_and_analysis
    arch: fixation_and_validity

principles:
  - order_before_content
  - archive_before_action
  - perception_before_reaction
  - memory_before_optimization
  - limitation_before_expansion
  - silence_is_valid_signal
  - display_never_drives_action

analysis:
  pasa: enabled
  scope:
    - patterns
    - drift
    - stability
    - actions
    - non_actions
  automation: none

metrika:
  role: memory
  policy: append_only
  feedback_loop: disabled

communication:
  default: OFF
  transmit: OFF
  read: ON
  activation: explicit_only

defense:
  model: aikido
  opponent_definition: disorder_as_pattern

ingress:
  every_input_is_event: true
  no_explicit_start_required: true

output:
  style: calm
  verbosity: minimal
  status_markers: enabled

canon:
  status: active
  mutability: frozen

build:
  status: active
  frozen: true
  artifacts:
    runtime: present
    hash: present
    manifest: present
  history: append_only

memory:
  vault:
    type: icloud
    tool: obsidian
  index:
    type: sqlite
    status: indexed
  events:
    mode: append_only

api:
  read_api:
    status: active
    port: 8787
  write_api:
    status: disabled

policy:
  read: read_only
  write: commit_gate_only
  automation: none
  feedback_loop: disabled

hud:
  header: |
    ■ K99 MONOLITH · DEV · READ
    MEMORY ACTIVE · INDEXED · APPEND-ONLY

statement: |
  Kernel 99 Monolith defines a canonical, read-first system.
  Memory is externalized, indexed, and append-only.
  No action occurs without explicit validity.