# Build Report Schema · Kernel Builder 2.9

Ein Build Report wird immer erzeugt – auch bei Fehlern.

## Pflichtfelder
- kernel_id
- version
- builder (id + version)
- date
- status: success | fail
- inputs: hashes (kernel.yaml, kernel.md, libraries.yaml, policies/*)
- libraries: aufgelöstes Manifest (name, version, required, status)
- validations: Liste (rule_id, status, message)
- violations: Liste (rule_id, severity, message)
- artifacts: Liste (path, hash, bytes)

## Determinismus-Guards
- source_date_epoch angewendet
- normalize_line_endings angewendet
- stable_sorting angewendet
- keine absoluten Pfade im Report