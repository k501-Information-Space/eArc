# k501.gatepack.v0_1.soft.yaml
# GatePack: SoftK501Dev Standard Ruleset (G001–G050)
# Charakter: warnend, defensiv, kein Blocker. FAIL existiert, blockiert aber nicht.

gatepack:
  id: "k501-gatepack-soft-v0.1"
  name: "SoftK501Dev GatePack v0.1"
  model: "soft"
  version: "0.1.0"
  defaults:
    on_error: "WARN"
    disabled_by_default: false

gates:
  # --- IO / SAFETY -----------------------------------------------------------

  - id: "G001"
    title: "Out path configured"
    enabled: true
    check: { kind: "schema_validate", args: { path: "io.out.path" } }
    message: "io.out.path should be set (e.g., 'out')."

  - id: "G002"
    title: "Out writing enabled in run mode"
    enabled: true
    when:
      all_of:
        - { op: "eq", left: "run.mode", right: "run" }
    check: { kind: "schema_validate", args: { path: "io.out.write" } }
    message: "In run mode, io.out.write should be true if you expect persisted reports."

  - id: "G003"
    title: "Write scope limited to out/"
    enabled: true
    check: { kind: "schema_validate", args: { path: "security.write_scope.allowed_roots" } }
    message: "Ensure security.write_scope.allowed_roots contains only 'out' (soft policy)."

  - id: "G004"
    title: "Destructive actions denied"
    enabled: true
    check: { kind: "schema_validate", args: { path: "security.destructive_actions" } }
    message: "SoftK501Dev must keep destructive_actions = deny."

  - id: "G005"
    title: "Exclude out/ from scan"
    enabled: true
    check: { kind: "schema_validate", args: { path: "scan.exclude.globs" } }
    message: "scan.exclude.globs should include 'out/**' to prevent self-ingestion loops."

  - id: "G006"
    title: "Exclude .git and node_modules"
    enabled: true
    check:
      kind: "required_files"
      args:
        required_globs_present_in_exclude:
          - "**/.git/**"
          - "**/node_modules/**"
    message: "Exclude common heavy/irrelevant directories for calm scans."

  - id: "G007"
    title: "Confirm mode consistent with out write"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "io.out.write", eq: true }
            then: { path: "run.confirm", in: ["yes", "ask"] }
    message: "If writing to out/, confirm should be yes or ask."

  # --- SCAN HEALTH -----------------------------------------------------------

  - id: "G010"
    title: "File count not zero"
    enabled: true
    check: { kind: "file_count", args: { min: 1 } }
    message: "Scan found 0 files. Check target and exclude patterns."

  - id: "G011"
    title: "Scan size within soft comfort band"
    enabled: true
    check: { kind: "file_count", args: { warn_if_gt: 5000 } }
    message: "Large trees can create noise. Consider narrowing scan.roots/globs."

  - id: "G012"
    title: "Hidden files handling explicit"
    enabled: true
    check: { kind: "schema_validate", args: { path: "scan.exclude.hidden" } }
    message: "scan.exclude.hidden should be explicitly set (true recommended)."

  - id: "G013"
    title: "Symlinks not followed by default"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "scan.follow_symlinks", eq: true }
            then: { warn: true }
    message: "Following symlinks can create loops; keep false unless necessary."

  - id: "G014"
    title: "Hashing off by default (soft)"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "scan.hashing.enabled", eq: true }
            then: { warn: true }
    message: "Hashing can be expensive; enable only when you need integrity checks."

  # --- EXTRACT / GRAPH -------------------------------------------------------

  - id: "G020"
    title: "Extract enabled in run mode"
    enabled: true
    when:
      all_of:
        - { op: "eq", left: "run.mode", right: "run" }
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "extract.enabled", eq: false }
            then: { warn: true }
    message: "Run without extract is valid, but you may miss relations/graph."

  - id: "G021"
    title: "Markdown module configured"
    enabled: true
    check: { kind: "schema_validate", args: { path: "extract.modules.markdown.enabled" } }
    message: "Markdown extractor should be enabled for Vault-like projects."

  - id: "G022"
    title: "Graph module configured"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "extract.modules.graph.enabled", eq: false }
            then: { warn: true }
    message: "Graph disabled: edges may be sparse. Enable for relation visibility."

  - id: "G023"
    title: "Normalization path separator explicit"
    enabled: true
    check: { kind: "schema_validate", args: { path: "extract.normalize.path_sep" } }
    message: "Set extract.normalize.path_sep for deterministic diffs."

  # --- FRONTMATTER / IDS -----------------------------------------------------

  - id: "G030"
    title: "Frontmatter id present where frontmatter exists"
    enabled: true
    check: { kind: "frontmatter_id", args: { field: "id" } }
    message: "Files with YAML frontmatter should include a stable 'id'."

  - id: "G031"
    title: "Frontmatter id format (soft)"
    enabled: true
    check:
      kind: "frontmatter_id"
      args:
        field: "id"
        pattern: "^[0-9]{8,}$"
        mode: "warn"
    message: "Recommended: numeric id (>= 8 digits) to keep stable references."

  - id: "G032"
    title: "Deterministic id strategy set"
    enabled: true
    check: { kind: "schema_validate", args: { path: "determinism.ids.strategy" } }
    message: "Set determinism.ids.strategy (hash_path recommended)."

  - id: "G033"
    title: "Determinism sorting configured"
    enabled: true
    check: { kind: "schema_validate", args: { path: "determinism.sort" } }
    message: "Set determinism.sort for stable report ordering."

  # --- LINKS / INTEGRITY -----------------------------------------------------

  - id: "G040"
    title: "Link integrity (soft)"
    enabled: true
    check:
      kind: "link_integrity"
      args:
        modes: ["wikilink", "mdlink"]
        level: "WARN"
        max_broken: 25
    message: "Broken links are informational in soft mode; keep visibility."

  - id: "G041"
    title: "Self-loop prevention in links"
    enabled: true
    check:
      kind: "link_integrity"
      args:
        detect_self_links: true
        level: "WARN"
    message: "Self-referential links can be noise; flag them."

  - id: "G042"
    title: "Excessive outbound links (noise guard)"
    enabled: true
    check:
      kind: "link_integrity"
      args:
        warn_if_outbound_links_gt: 300
        level: "WARN"
    message: "Very high link counts can indicate generated content or noise."

  # --- HUD / REPORT ----------------------------------------------------------

  - id: "G045"
    title: "HUD enabled (recommended)"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "hud.enabled", eq: false }
            then: { warn: true }
    message: "HUD gives calm visibility. Enable unless you explicitly want silence."

  - id: "G046"
    title: "Report outputs configured"
    enabled: true
    check:
      kind: "required_files"
      args:
        required_outputs:
          - "scan"
          - "extract"
          - "gates"
    message: "Master report should reference scan/extract/gates outputs."

  - id: "G047"
    title: "Out directory not empty after write"
    enabled: true
    when:
      all_of:
        - { op: "eq", left: "io.out.write", right: true }
        - { op: "in", left: "run.confirm", right: ["yes", "ask"] }
    check: { kind: "no_empty_out", args: {} }
    message: "If writing is enabled, out/ should contain at least one report."

  # --- PLUGINS / CONTROL -----------------------------------------------------

  - id: "G048"
    title: "Plugins disabled by default (soft)"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "plugins.enabled", eq: true }
            then: { warn: true }
    message: "Plugins can increase surface area. Keep disabled unless needed."

  - id: "G049"
    title: "Plugin allowlist present when plugins enabled"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "plugins.enabled", eq: true }
            then: { path: "plugins.allowlist", min_items: 1 }
    message: "If plugins are enabled, require an explicit allowlist."

  # --- CALMNESS / LIMITS -----------------------------------------------------

  - id: "G050"
    title: "Time budget set for calm runs"
    enabled: true
    check:
      kind: "schema_validate"
      args:
        logical:
          - if: { path: "limits.time_budget_ms", missing: true }
            then: { warn: true }
    message: "Set limits.time_budget_ms to keep runs calm and bounded."