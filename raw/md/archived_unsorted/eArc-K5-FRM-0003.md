---
id: eArc-K5-FRM-0003
title: eArc Meta-Header
type: frame
version: 1.0
status: DRAFT
created: 2026-01-07
updated: 2026-01-07
scope: K5_CORE
consent_required: false
privacy_level: variable
---

# eArc Meta-Header v1.0

## Zweck
Ein einheitlicher Header für **jede Datei** (Text/MD/HTML/etc.),
damit Mensch + Maschine Inhalte eindeutig einordnen, verarbeiten, exportieren und versionieren können.

## Pflichtfelder (Minimal)
- id
- title
- type
- version
- status
- created
- updated
- scope

## Netzwerk-Felder (für „neuronales“ Lesen)
- relates_to: [IDs]
- depends_on: [IDs]
- supersedes: [IDs]
- tags: [strings]

## IO/Export-Felder (Input/Output/Export)
io:
  input:
    source: local|web|user
    format: md|txt|html|json|toml|yaml|pdf|epub|other
  output:
    format: md|txt|html|json|pdf|epub|other
    gate: blocked|open
  export:
    enabled: true|false
    pipeline: pandoc
    pandoc:
      pdf_engine: latex
      targets: [pdf, epub, html, docx]
      options: []

## PATH_FIRST Regel
Wenn diese Datei als „exportierbarer Dump“ gedacht ist:
Erste Zeile im Body ist der Zielpfad (virtuell), z.B.
`/eArc/K5/Dumps/`

## Hinweis
Der Header ist **Format-unabhängig**:
- In Markdown: YAML-Frontmatter
- In HTML: als Kommentarblock am Anfang (gleicher Inhalt)
- In TXT: als klarer Block am Anfang (YAML-ähnlich)

As I State Iinkognit0.