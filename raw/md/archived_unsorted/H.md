{

"meta": {

"protocol": "AI_CROSS_HANDSHAKE",

"mode": "PRO",

"policy": ["NO_DRIFT", "DETERMINISTIC", "APPEND_ONLY"],

"time_anchor": 1773773742

},

"validation": {

"hardware_state": "LOCKED_CONFIRMED",

"constraints": [

"CPU_NO_AVX2",

"CPU_NO_AVX512",

"RAM_LIMIT_8GB",

"THERMAL_LIMIT_ACTIVE"

],

"implication": [

"STRICT_SEQUENTIAL_EXECUTION",

"BATCH_SIZE_LE_50",

"NO_PARALLELISM",

"MEMORY_SAFE_OPERATIONS_ONLY"

]

},

"code_audit": {

"module": "k501_merger.py",

"status": "VALID_WITH_PATCH",

"issues": [

{

"id": "I1",

"type": "FIELD_MISMATCH",

"detail": "vector file uses keys {ref, v} not {ref_id, vector}",

"impact": "VECTOR_LOOKUP_FAIL"

}

],

"required_patch": {

"action": "KEY_ALIGNMENT",

"change": [

"data['ref_id'] -> data['ref']",

"data['vector'] -> data['v']"

]

}

},

"patched_logic": {

"vector_map": "vec_map[data['ref']] = data['v']",

"lookup": "vec_map.get(frame_id, [])"

},

"algorithm": {

"type": "SEQUENTIAL_FUSION",

"complexity": {

"time": "O(n)",

"memory": "O(k)"

},

"mapping": "ZIP(frames, llm) + HASH_LOOKUP(vectors)",

"determinism": "STRICT_1_TO_1"

},

"execution_contract": {

"preconditions": [

"FILES_EXIST",

"LINE_COUNT_MATCH(frames, llm)",

"VECTOR_FILE_OPTIONAL"

],

"command": "python3 ~/workspace/k501/runtime/tools/k501_merger.py",

"expected_output": "master_index_v1.ndjson"

},

"output_schema": {

"id": "string",

"t": "int",

"h": "string",

"semantic": {

"labels": "array[string]",

"type": "string"

},

"vector": "array[float]"

},

"state_transition": {

"current": "AWAITING_FUSION",

"trigger": "EXECUTE_MERGER",

"next": "FUSED_INDEX_READY"

},

"next_phase": {

"id": "A6",

"name": "HARD_INDEX_BUILD",

"goal": "CREATE_INDEX_FROM_MASTER",

"operations": [

"ID_INDEX",

"VECTOR_INDEX",

"TIME_INDEX"

]

},

"assertions": [

"PIPELINE_CONSISTENT",

"MERGE_STRATEGY_VALID",

"PATCH_REQUIRED_FOR_VECTOR_ALIGNMENT",

"SYSTEM_READY_FOR_EXECUTION"

]

}