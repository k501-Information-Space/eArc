Phase 3 · Data & Archive Layer (Extended)
- Transport: SFTP + rsync (SSH)
- FS: iOS Files / iCloud Drive (append-only)
- DB: SQLite + FTS5 (WAL)
- Vault: Header-first scan (YAML)
- Integrity: SHA-256 + detached manifests (optional Merkle)
- Diff: Metadata-first, Patience Diff
- Security: SSH Ed25519, read-only keys
- Mobile: batch jobs, energy-aware