#!/usr/bin/env bash

set -euo pipefail

SOURCE_DIR="raw/md/archived_unsorted"

CHUNK_DIR="semantic_ingest_v1/chunks"
EMBED_DIR="semantic_ingest_v1/embeddings"
REPORT_DIR="semantic_ingest_v1/reports"

MODEL="nomic-embed-text"

mkdir -p "$CHUNK_DIR"
mkdir -p "$EMBED_DIR"
mkdir -p "$REPORT_DIR"

echo "[K501] BUILD_FILE_INDEX"

find "$SOURCE_DIR" \
-type f \
-name "*.md" \
| sort \
> "$REPORT_DIR/md_file_index.txt"

echo "[K501] SPLIT_PHASE"

while IFS= read -r file
do
    rel=$(echo "$file" | sed 's#/#__#g')

    split -b 12k \
    --additional-suffix=.txt \
    "$file" \
    "$CHUNK_DIR/${rel}_"

done < "$REPORT_DIR/md_file_index.txt"

echo "[K501] EMBED_PHASE"

find "$CHUNK_DIR" \
-type f \
| sort \
| while read -r chunk
do
    out=$(basename "$chunk")

    if [ ! -f "$EMBED_DIR/${out}.json" ]; then

	curl -s http://localhost:11434/api/embeddings \
	-d "{
	\"model\":\"$MODEL\",
	\"prompt\":$(jq -Rs . < "$chunk")
	}" \
	> "$EMBED_DIR/${out}.json"

        echo "[K501_EMBED_OK] $out"

    else

        echo "[K501_SKIP_EXISTS] $out"

    fi

done

echo "[K501] COMPLETE"
