# k501.gatepack.v0_1.strict.yaml
gatepack:
  id: "k501-gatepack-strict-v0.1"
  name: "K501 GatePack Strict v0.1"
  model: "strict"
  version: "0.1.0"
  derived_from: "k501-gatepack-soft-v0.1"
  defaults:
    on_error: "FAIL"
    disabled_by_default: false

gates:
  # --- IO / SAFETY (mostly FAIL) --------------------------------------------

  - id: "G001"
    title: "Out path configured"
    enabled: true
    check: { kind: "schema_validate", args: { path: "io.out.path" } }
    message: "io.out.path must be set."

  - id: "G002"
    title: "Out writing enabled in run mode"
    enabled: true
    when: { all_of: [ { op: "eq", left: "run.mode", right: "run" } ] }
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "io.out.write", eq: false }
            then: { fail: true }
    message: "In run mode, io.out.write must be true (strict baseline)."

  - id: "G003"
    title: "Write scope limited to out/"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "security.write_scope.allowed_roots", contains_only: ["out"] }
            then: { pass: true }
          - else: { fail: true }
    message: "Write scope must be restricted to out only."

  - id: "G004"
    title: "Destructive actions denied"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "security.destructive_actions", eq: "deny" }
            then: { pass: true }
          - else: { fail: true }
    message: "destructive_actions must remain deny."

  - id: "G005"
    title: "Exclude out/ from scan"
    enabled: true
    check:
      kind: "required_files"
      args:
        required_globs_present_in_exclude: ["out/**"]
    message: "Must exclude out/** to prevent feedback loops."

  - id: "G006"
    title: "Exclude .git and node_modules"
    enabled: true
    check:
      kind: "required_files"
      args:
        required_globs_present_in_exclude:
          - "**/.git/**"
          - "**/node_modules/**"
    message: "Must exclude .git and node_modules."

  - id: "G007"
    title: "Confirm mode consistent with writes"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "io.out.write", eq: true }
            then: { path: "run.confirm", eq: "yes" }
    message: "Strict: if writing, confirm must be yes (no ask/no)."

  # --- SCAN HEALTH (bounded) -------------------------------------------------

  - id: "G010"
    title: "File count not zero"
    enabled: true
    check: { kind: "file_count", args: { min: 1, fail_if_eq: 0 } }
    message: "0 files is a failure in strict mode."

  - id: "G011"
    title: "Scan size under cap"
    enabled: true
    check: { kind: "file_count", args: { fail_if_gt: 20000, warn_if_gt: 5000 } }
    message: "Strict cap: >20k files fails; >5k warns."

  - id: "G012"
    title: "Hidden files handling explicit"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "scan.exclude.hidden", missing: true }
            then: { fail: true }
    message: "scan.exclude.hidden must be explicitly set."

  - id: "G013"
    title: "Do not follow symlinks"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "scan.follow_symlinks", eq: true }
            then: { fail: true }
    message: "Strict: follow_symlinks must be false."

  - id: "G014"
    title: "Hashing enabled for integrity"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "scan.hashing.enabled", eq: false }
            then: { warn: true }
    message: "Strict recommends hashing; warn if disabled."

  # --- EXTRACT / GRAPH (required) -------------------------------------------

  - id: "G020"
    title: "Extract enabled in run mode"
    enabled: true
    when: { all_of: [ { op: "eq", left: "run.mode", right: "run" } ] }
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "extract.enabled", eq: false }
            then: { fail: true }
    message: "Strict: extract must be enabled in run."

  - id: "G021"
    title: "Markdown module enabled"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "extract.modules.markdown.enabled", eq: false }
            then: { fail: true }
    message: "Strict: markdown extractor must be enabled."

  - id: "G022"
    title: "Graph module enabled"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "extract.modules.graph.enabled", eq: false }
            then: { fail: true }
    message: "Strict: graph must be enabled."

  - id: "G023"
    title: "Normalization explicit"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "extract.normalize.path_sep", missing: true }
            then: { fail: true }
    message: "Strict: normalization must be explicit."

  # --- FRONTMATTER / IDS (hard) ---------------------------------------------

  - id: "G030"
    title: "Frontmatter id required"
    enabled: true
    check: { kind: "frontmatter_id", args: { field: "id", required: true, level: "FAIL" } }
    message: "Strict: YAML frontmatter must contain id."

  - id: "G031"
    title: "Frontmatter id format required"
    enabled: true
    check:
      kind: "frontmatter_id"
      args:
        field: "id"
        pattern: "^[0-9]{8,}$"
        required: true
        level: "FAIL"
    message: "Strict: id must be numeric and >= 8 digits."

  - id: "G032"
    title: "Deterministic id strategy required"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "determinism.ids.strategy", in: ["hash_path"] }
            then: { pass: true }
          - else: { fail: true }
    message: "Strict: determinism.ids.strategy must be hash_path."

  - id: "G033"
    title: "Determinism sorting required"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "determinism.sort.files", eq: "path" }
            then: { pass: true }
          - else: { fail: true }
    message: "Strict: files must be sorted by path."

  # --- LINKS / INTEGRITY (bounded) ------------------------------------------

  - id: "G040"
    title: "Broken links under threshold"
    enabled: true
    check:
      kind: "link_integrity"
      args:
        modes: ["wikilink", "mdlink"]
        level: "FAIL"
        max_broken: 0
    message: "Strict: broken links must be 0."

  - id: "G041"
    title: "No self-links"
    enabled: true
    check:
      kind: "link_integrity"
      args:
        detect_self_links: true
        level: "FAIL"
    message: "Strict: self-links are failures."

  - id: "G042"
    title: "Outbound link noise bounded"
    enabled: true
    check:
      kind: "link_integrity"
      args:
        fail_if_outbound_links_gt: 500
        warn_if_outbound_links_gt: 250
        level: "WARN"
    message: "Strict: outbound link volume bounded."

  # --- HUD / REPORT (required) ----------------------------------------------

  - id: "G045"
    title: "HUD enabled"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "hud.enabled", eq: false }
            then: { fail: true }
    message: "Strict: HUD must be enabled."

  - id: "G046"
    title: "Report outputs configured"
    enabled: true
    check:
      kind: "required_files"
      args:
        required_outputs: ["scan", "extract", "gates", "hud"]
    message: "Strict: report must include scan/extract/gates/hud."

  - id: "G047"
    title: "Out directory must not be empty"
    enabled: true
    check: { kind: "no_empty_out", args: {} }
    message: "Strict: out/ must contain reports."

  # --- PLUGINS / CONTROL (tight) --------------------------------------------

  - id: "G048"
    title: "Plugins disabled unless explicitly allowed"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "plugins.enabled", eq: true }
            then: { warn: true }
    message: "Strict: keep plugins off unless you are sure."

  - id: "G049"
    title: "Allowlist required when plugins enabled"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "plugins.enabled", eq: true }
            then: { path: "plugins.allowlist", min_items: 1 }
    message: "Strict: plugins require allowlist."

  # --- CALMNESS / LIMITS (required) -----------------------------------------

  - id: "G050"
    title: "Time budget required"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "limits.time_budget_ms", missing: true }
            then: { fail: true }
    message: "Strict: limits.time_budget_ms must be set."