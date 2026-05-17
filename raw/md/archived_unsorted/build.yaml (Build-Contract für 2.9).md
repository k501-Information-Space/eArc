build:
  builder:
    id: kernel_builder_2_9
    version: "2.9"

  determinism:
    source_date_epoch: fixed          # builder setzt/erzwingt SOURCE_DATE_EPOCH
    normalize_line_endings: true      # LF only
    normalize_whitespace: true        # trailing spaces trim (außer in code fences)
    forbid_absolute_paths_in_reports: true
    stable_sorting:
      lists: true
      keys: true

  outputs:
    dist_dir: kernel/dist
    reports_dir: kernel/reports

    artifact_naming:
      kernel_md: "kernel_{id}_{version}.md"
      kernel_html: "kernel_{id}_{version}.html"
      kernel_pdf: "kernel_{id}_{version}.pdf"
      kernel_epub: "kernel_{id}_{version}.epub"
      report_json: "build_report_{id}_{version}.json"
      sha256sums: "SHA256SUMS_{id}_{version}"

  formats:
    md: true
    html: true
    pdf: optional
    epub: optional

  fail_fast: true