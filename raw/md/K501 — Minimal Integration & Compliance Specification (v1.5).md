---
# (PASTE CANONICAL HEADER HERE)
doc.type: "COMPLIANCE"
title: "K501 — Minimal Integration & Compliance Specification"
subtitle: "Normative requirements and a test checklist for K501-compatible systems"
---

# K501 — Minimal Integration & Compliance Specification (v1.5)

## Abstract
This document defines the minimal normative requirements for K501 compatibility and provides a verification checklist suitable for implementers and reviewers.

## 1. Normative Requirements (MUST)
A K501-compatible emitter MUST:
1. Produce a unique frame.id per frame
2. Provide time.utc in ISO-8601 Zulu format
3. Provide time.unix as integer seconds
4. Preserve append-only discipline (no mutation of historical frames)
5. Use deterministic serialization for the chosen payload representation (defined by the emitter)

## 2. Recommended (SHOULD)
A K501-compatible system SHOULD:
- Provide document.id for document-level frames
- Provide source.canonical and source.repository
- Provide stable versioning and previous_version references

## 3. Compliance Checklist (Copy/Paste)
- [ ] Frame IDs are unique
- [ ] UTC timestamp format valid: YYYY-MM-DDTHH:MM:SSZ
- [ ] Unix epoch integer present
- [ ] UTC and Unix correspond (no drift)
- [ ] Append-only rule respected (no in-place edits)
- [ ] Deterministic serialization rule stated
- [ ] Cross-references stable (previous_version / previous_doi if applicable)

## 4. Minimal Example (Structural Only)
Provide one example frame header + payload excerpt (non-semantic).

## Citation
Miller, P. R. (2026). *K501 — Minimal Integration & Compliance Specification* (Version 1.5). Zenodo. https://doi.org/10.5281/zenodo.XXXXXXX