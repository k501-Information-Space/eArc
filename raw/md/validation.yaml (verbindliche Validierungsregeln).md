validation:
  schema:
    require_kernel_yaml_fields:
      - id
      - type
      - scope
      - name
      - version
      - state
      - kanon
      - date
    require_builder_meta:
      - builder.id
      - builder.version

  states:
    frames:
      allowed_transitions:
        - from: ingested
          to: held
        - from: held
          to: released
        - from: released
          to: archived
      forbid_reverse_transitions: true

  archive:
    truth_layer: true
    immutable_state: archived
    mutation_policy: revision_only   # niemals überschreiben

  release_surfaces:
    required_keys:
      - feeds
      - endpoints
      - export
      - artifacts
    allowed_values:
      - enabled
      - disabled
    dev_alpha_defaults:
      feeds: enabled
      endpoints: enabled
      export: enabled
      artifacts: enabled

  exclusions:
    forbidden_features:
      - social_mechanics
      - ranking
      - push
      - realtime_chat
      - app_store_strategy