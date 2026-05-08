#!/usr/bin/env bash
# K501 Phase: A2 & A3 Execution

# 1. Enforce LLM Contract Schema via Prompt Update
echo "Analyze data. Output STRICT JSON ONLY. Schema: {\"labels\": [\"tag1\", \"...max 5\"], \"type\": \"doc_type\"}. All values MUST be LOWERCASE. NO EXPLANATION." > ~/k501_llm_test/prompt.txt

# 2. Define Paths
IN=~/k501_llm_test/in/batch_002.ndjson
OUT=~/k501_llm_test/out/semantic_llm_50.ndjson
PR=$(cat ~/k501_llm_test/prompt.txt)

# 3. Extract Controlled Batch
head -n 50 ~/workspace/archive/little_alpha_storage/frames.ndjson > "$IN"
: > "$OUT"

echo "[SYS] Executing A2/A3: RERUN_BATCH (Size: 50)"

# 4. Sequential Execution (FD 3 Isolation)
while IFS= read -u 3 -r line; do
    [ -z "$line" ] && continue
    
    # Extract ID for logging
    ID=$(echo "$line" | jq -r .id | rev | cut -d/ -f1 | rev)
    echo "[INFER] Processing: $ID"
    
    # API Call with Strict JSON Extraction
    curl -s http://localhost:11434/api/generate -d "{
        \"model\": \"qwen2:0.5b-instruct\",
        \"prompt\": \"$PR Data: $line\",
        \"stream\": false
    }" | jq -rc '.response' | jq -rc . >> "$OUT" 2>/dev/null

    # Validation Catch
    if [ $? -ne 0 ]; then
        echo "[WARN] Schema Violation / Invalid JSON: $ID" >&2
    fi

done 3< "$IN"

echo "[SYS] Batch Complete. Output collected at $OUT"