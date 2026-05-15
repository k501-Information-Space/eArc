{

"meta": {

"mode": "PRO",

"protocol": "AI_CROSS_HANDSHAKE",

"policy": ["NO_DRIFT", "NO_FREE_SEMANTICS", "DETERMINISTIC", "APPEND_ONLY"],

"time_anchor": {

"unix": 1773773742,

"utc": "2026-03-17T18:55:42Z"

}

},

"system": {

"name": "K501_DUAL_PIPELINE",

"state": "ACTIVE_VALIDATION",

"components": [

"INGEST_CORE",

"EMBEDDING_LAYER",

"LLM_ANALYSIS_LAYER"

]

},

"nodes": {

"node_A": {

"role": "EMBEDDING",

"cpu": "i5-8250U",

"threads": 8,

"ram_gb": 16,

"mode": "DUAL_CHANNEL",

"status": "STABLE"

},

"node_B": {

"role": "LLM_ANALYSIS",

"model": "qwen2_0.5b_q4",

"threads": 8,

"ram_gb": 16,

"status": "ACTIVE"

}

},

"pipeline": {

"flow": [

"RAW_DATA",

"FRAME_STRUCT",

"EMBED_VECTOR",

"LLM_STRUCT_OUTPUT",

"SEMANTIC_FRAME"

],

"current_position": "LLM_VALIDATION"

},

"frame_spec": {

"input": {

"required_fields": ["id", "t", "path"],

"missing": ["content"]

},

"issue": "INSUFFICIENT_SEMANTIC_SIGNAL",

"resolution": {

"action": "ADD_CONTENT_FIELD",

"strategy": "TRUNCATED_TEXT",

"limit_chars": 512

}

},

"llm_contract": {

"input": "FRAME_WITH_CONTENT",

"output_schema": {

"labels": "array[string,max=5]",

"type": "string"

},

"constraints": [

"LOWERCASE",

"NO_EXPLANATION",

"STRICT_JSON"

]

},

"batch_engine": {

"mode": "SEQUENTIAL",

"status": "STABLE",

"fix_applied": "QUOTED_INPUT",

"next_step": "BATCH_OPTIMIZATION"

},

"gaia_loop": {

"phase": "OBSERVE",

"input": "LLM_OUTPUT",

"operation": [

"COLLECT",

"COMPARE",

"VALIDATE"

],

"next_phase": "FORMALIZE"

},

"actions": [

{

"id": "A1",

"task": "PATCH_NORMALIZER",

"target": "ADD_CONTENT",

"priority": "CRITICAL"

},

{

"id": "A2",

"task": "RERUN_BATCH",

"size": 50,

"mode": "CONTROLLED"

},

{

"id": "A3",

"task": "COLLECT_OUTPUTS",

"target": "semantic_llm.ndjson"

},

{

"id": "A4",

"task": "CROSS_MODEL_COMPARE",

"models": ["qwen_local", "gemini_pro"]

}

],

"state_assertions": [

"STRUCTURE_STABLE",

"EMBEDDING_VALID",

"LLM_INPUT_INSUFFICIENT",

"CONTENT_REQUIRED"

],

"next_transition": {

"condition": "CONTENT_INTEGRATED",

"target_state": "SEMANTIC_GENERATION_VALID"

}

}