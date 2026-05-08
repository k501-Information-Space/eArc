{
  "kernel_id": "kernel_5000_dev_alpha",
  "version": "v4.1",
  "builder": { "id": "kernel_builder_2_9", "version": "2.9" },
  "date": "2026-01-08",
  "status": "success",
  "inputs": {
    "kernel/src/kernel.yaml": "<sha256>",
    "kernel/src/kernel.md": "<sha256>",
    "kernel/src/libraries.yaml": "<sha256>",
    "kernel/src/policies/validation.yaml": "<sha256>",
    "kernel/src/policies/strings.yaml": "<sha256>",
    "kernel/src/policies/build.yaml": "<sha256>"
  },
  "libraries": [
    { "name": "metrika", "version": "1.4.0", "required": true, "status": "resolved" },
    { "name": "export_pack", "version": "2.1.3", "required": true, "status": "resolved" },
    { "name": "builder_core", "version": "2.9.0", "required": true, "status": "resolved" }
  ],
  "validations": [
    { "rule_id": "schema.required_fields", "status": "pass", "message": "kernel.yaml Pflichtfelder vorhanden" },
    { "rule_id": "builder.meta", "status": "pass", "message": "builder.id/version korrekt" },
    { "rule_id": "strings.forbid_public_alpha", "status": "pass", "message": "public_alpha nicht enthalten" },
    { "rule_id": "release_surfaces.required", "status": "pass", "message": "feeds/endpoints/export/artifacts vorhanden" },
    { "rule_id": "release_surfaces.values", "status": "pass", "message": "enabled/disabled gültig" },
    { "rule_id": "exclusions.forbidden_features", "status": "pass", "message": "Ausschlüsse eingehalten" },
    { "rule_id": "states.frames.transitions", "status": "pass", "message": "Transitions gültig, keine Rücksprünge" },
    { "rule_id": "archive.truth_layer", "status": "pass", "message": "archived=immutable, revision_only" },
    { "rule_id": "determinism.normalization", "status": "pass", "message": "LF-only + whitespace normalize + stable sorting" }
  ],
  "violations": [],
  "artifacts": [
    { "path": "kernel/dist/kernel_kernel_5000_dev_alpha_v4.1.md", "hash": "<sha256>", "bytes": "<bytes>" },
    { "path": "kernel/dist/kernel_kernel_5000_dev_alpha_v4.1.html", "hash": "<sha256>", "bytes": "<bytes>" },
    { "path": "kernel/dist/SHA256SUMS_kernel_5000_dev_alpha_v4.1", "hash": "<sha256>", "bytes": "<bytes>" }
  ]
}