🕊️ Verstanden.

Phase C gestartet — Snapshot-Batch minimal.

Ziel: deterministischer Kern, klein, auditierbar, HardIndex-konform.

  

  

  

  

🧭 K501 · SNAPSHOT PLAN · MINIMAL v0.1

  

  

Mode: REFERENCE_ONLY · Policy: APPEND_ONLY · Authority: NONE

Scope: Tier 0 Critical Sources

Strategy: small → canonical → hash-ready

  

  

  

  

🔥 SNAPSHOT SET — PRIORITY CORE

  

  

  

1️⃣ RFC 8259 — JSON

  

  

HI_SNAPSHOT (geplant)

  

- source_id: HI-SRC-RFC8259-0001
- snapshot_scope: FULL_TEXT
- volatility: STATIC
- estimated_size: SMALL
- chunk_strategy: SECTIONAL (by RFC sections)
- hash_plan: SHA256 over raw + SHA256 over normalized
- priority: P0

  

  

🎯 Zweck: JSON Ground Truth

  

  

  

  

2️⃣ RFC 3629 — UTF-8

  

  

HI_SNAPSHOT (geplant)

  

- source_id: HI-SRC-RFC3629-0001
- snapshot_scope: FULL_TEXT
- volatility: STATIC
- estimated_size: SMALL
- chunk_strategy: DOCUMENT_LEVEL
- hash_plan: SHA256 raw
- priority: P0

  

  

🎯 Zweck: Encoding Fundament

  

  

  

  

3️⃣ RFC 8785 — JCS

  

  

HI_SNAPSHOT (geplant)

  

- source_id: HI-SRC-RFC8785-0001
- snapshot_scope: FULL_TEXT
- volatility: STATIC
- estimated_size: SMALL
- chunk_strategy: SECTIONAL
- hash_plan: CRITICAL: SHA256 over canonical text
- priority: P0

  

  

🎯 Zweck: deterministische Serialisierung

  

⚠️ K501-kritisch

  

  

  

  

4️⃣ FIPS 180-4 — SHA-2

  

  

HI_SNAPSHOT (geplant)

  

- source_id: HI-SRC-FIPS1804-0001
- snapshot_scope: FULL_TEXT_PDF + TEXT_EXTRACT
- volatility: STATIC
- estimated_size: MEDIUM
- chunk_strategy:  
    

- primary: DOCUMENT_LEVEL
- optional: SECTIONAL (later)

-   
    
- hash_plan:  
    

- SHA256 over original PDF
- SHA256 over extracted text

-   
    
- priority: P0

  

  

🎯 Zweck: Hash Root

  

  

  

  

5️⃣ NDJSON Spec

  

  

HI_SNAPSHOT (geplant)

  

- source_id: HI-SRC-NDJSON-0001
- snapshot_scope: README + SPEC FILES
- volatility: SLOW
- estimated_size: VERY_SMALL
- chunk_strategy: FILE_LEVEL
- hash_plan: SHA256 per file
- priority: P1

  

  

🎯 Zweck: Streaming JSON Basis

  

  

  

  

🧩 CHUNKING STRATEGY (kanonisch)

  

  

  

Level 0 — Raw Preservation

  

  

Für jede Quelle:

  

- original_bytes → hash
- mime_type erfassen
- retrieval_ts setzen

  

  

✅ garantiert Reproduzierbarkeit

  

  

  

  

Level 1 — Logical Chunking

  

  

Nur wenn sinnvoll:

  

- RFCs → nach Sections
- Specs → nach Dateien
- PDFs → optional später

  

  

⚠️ keine aggressive Fragmentierung jetzt

  

  

  

  

Level 2 — Future Semantic Layer (NICHT JETZT)

  

  

Reserviert für später:

  

- concept extraction
- cross-linking
- semantic graph

  

  

👉 aktuell bewusst nicht aktiv

  

  

  

  

🔐 HASH PLAN (HardIndex-konform)

  

  

Für jeden Snapshot:

  

  

Pflicht-Hashes

  

  

1. hash_raw_sha256
2. hash_canonical_sha256 (wenn Textformat stabil)
3. optional: chunk_hashes[]

  

  

  

  

  

Canonicalization Rules

  

  

- RFC text → LF normalize
- trim trailing whitespace
- UTF-8 enforce
- NO semantic rewrite

  

  

  

  

  

📦 DOWNLOAD-REIHENFOLGE (empfohlen)

  

  

  

Batch A — klein & kritisch

  

  

1. RFC 8259
2. RFC 3629
3. RFC 8785

  

  

👉 danach bereits deterministischer Kern vorhanden

  

  

  

  

Batch B — Hash-Root

  

  

4. FIPS 180-4
5. NDJSON

  

  

  

  

  

🚫 EXPLIZIT NICHT IN DIESEM BATCH

  

  

- Kernel docs
- POSIX full
- Networking RFCs
- Language manuals

  

  

✅ Scope sauber gehalten

  

  

  

  

🧭 SYSTEMZUSTAND

  

  

Nach diesem Plan gilt:

  

- Bootframe: entwicklungsfähig
- Determinismus: geschlossen
- HardIndex: bereit für echte Inhalte
- Risiko Overfetch: unter Kontrolle

  

  

  

  

  

▶️ Nächster operativer Schritt

  

  

Wenn du bereit bist, sage:

  

„HI_SNAPSHOT Objekte erzeugen.“

  

Dann bekommst du:

  

- konkrete HI_SNAPSHOT Frames
- NDJSON-fertig
- direkt importierbar in dein Repo
- inkl. Retrieval-Felder

  

  

🕊️