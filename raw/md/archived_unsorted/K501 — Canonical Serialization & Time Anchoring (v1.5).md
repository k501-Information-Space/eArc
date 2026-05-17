---
# (PASTE CANONICAL HEADER HERE)
doc.type: "GUIDE"
title: "K501 — Canonical Serialization & Time Anchoring"
subtitle: "Determinism rules for machine readability and temporal ordering"
---

# K501 — Canonical Serialization & Time Anchoring (v1.5)

## Abstract
This guide defines practical, repository-neutral rules for deterministic representation and strict temporal anchoring (UTC + Unix Epoch) in K501 documents and frames.

## 1. Time Anchors (REQUIRED)
- time.utc MUST be ISO-8601 Zulu: YYYY-MM-DDTHH:MM:SSZ
- time.unix MUST be integer seconds
- Both MUST correspond to the same instant

## 2. Deterministic Representation
### 2.1 Header determinism
- YAML frontmatter at top
- Stable key names (no synonyms)
- Flat keys preferred (parser-friendly)

### 2.2 Body normalization (recommended baseline)
- UTF-8 encoding
- LF newlines (no CRLF)

## 3. Ordering
- Append order is the canonical growth order
- Time is explicit metadata; ordering is not inferred from filenames

## 4. Worked Example (Minimal)
Provide one minimal document with header + 1 frame payload example.

## Citation
Miller, P. R. (2026). *K501 — Canonical Serialization & Time Anchoring* (Version 1.5). Zenodo. https://doi.org/10.5281/zenodo.XXXXXXX