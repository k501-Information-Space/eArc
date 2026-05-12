kernel_builder_contract:
  cli: k
  version: "1.0"
  ethos:
    deterministic: true
    explicit: true
    no_automation: true
    no_feedback_loop: true
    append_only_history: true

paths:
  spec: kernel/spec/kernel.yaml
  schema: kernel/spec/schemas/kernel_spec_v1.json
  build_dir: kernel/build/
  normalized: kernel/build/kernel.normalized.yaml
  runtime: kernel/build/kernel.runtime.json
  hash: kernel/build/kernel.hash.sha256
  manifest: kernel/build/kernel.manifest.yaml
  tests_vectors: kernel/tests/vectors/
  tests_expected: kernel/tests/expected/
  tests_reports: kernel/tests/reports/last_run.json
  history_dir: kernel/build_history/

commands:
  validate:
    cmd: "k validate kernel/spec/kernel.yaml"
    does:
      - json_schema_validation
      - invariant_checks_R1_R6
      - principles_whitelist
    exit_codes:
      0: OK
      1: SCHEMA_ERROR
      2: INVARIANT_ERROR

  normalize:
    cmd: "k normalize kernel/spec/kernel.yaml --out kernel/build/kernel.normalized.yaml"
    does:
      - fieldname_harmonization
      - defaults_injection
      - deterministic_ordering
      - whitespace_normalization
    guarantees:
      - idempotent

  build:
    cmd: "k build kernel/spec/kernel.yaml --out kernel/build/"
    does:
      - validate
      - normalize
      - emit_runtime_json
      - emit_manifest
    outputs:
      - kernel/build/kernel.runtime.json
      - kernel/build/kernel.manifest.yaml
    abort_on:
      - validate_fail
      - normalize_fail

  hash:
    cmd: "k hash kernel/build/kernel.runtime.json --out kernel/build/kernel.hash.sha256"
    does:
      - sha256_over_exact_bytes
    outputs:
      - kernel/build/kernel.hash.sha256

  manifest:
    cmd: "k manifest kernel/spec/kernel.yaml kernel/build/kernel.runtime.json kernel/build/kernel.hash.sha256 --out kernel/build/kernel.manifest.yaml"
    does:
      - emit_build_metadata
    outputs:
      - kernel/build/kernel.manifest.yaml

  test:
    cmd: "k test"
    does:
      - run_all_vectors
      - build_each_vector
      - compare_to_golden_expected
      - write_last_run_report
    outputs:
      - kernel/tests/reports/last_run.json
    exit_codes:
      0: OK
      10: GOLDEN_DRIFT
      11: REGRESSION_INVARIANT

  diff:
    cmd: "k diff <expected_runtime.json> <actual_runtime.json>"
    does:
      - byte_or_structured_json_diff

  freeze:
    cmd: "k freeze kernel/build/ --history kernel/build_history/"
    does:
      - append_only_copy_runtime_hash_manifest
      - create_build_id_directory
      - optional_update_LATEST_pointer
    guarantees:
      - no_overwrite
      - no_delete

  status:
    cmd: "k status"
    does:
      - output_machine_readable_status
    output_example:
      spec_version: "1.0"
      kernel_id: "k99_monolith"
      last_build: "YYYYMMDD_HHMMSSZ-<short_hash>"
      hash_sha256: "<hex>"
      canon: "frozen"
      mode: "DEV"
      valid: true

  build_strict:
    cmd: "k build --strict"
    does:
      - require_tests_green
      - no_warnings
      - optional_git_clean_check
    abort_on:
      - tests_not_green
      - warnings_present
      - git_dirty_optional

non_goals:
  - auto_mode
  - optimize_mode
  - publish_side_effects
  - learning_from_usage

definition_of_done:
  required_artifacts:
    - kernel/build/kernel.runtime.json
    - kernel/build/kernel.hash.sha256
    - kernel/build/kernel.manifest.yaml
  required_checks:
    - validate_ok
    - test_ok
  required_properties:
    - deterministic_build
    - reproducible_hash
    - append_only_history