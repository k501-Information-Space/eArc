{

"protocol": "AI_CROSS_SYNCHRONIZATION",

"mode": "DETERMINISTIC_LOGIC_ONLY",

"interpretation": "DISABLED",

"goal": "UNIFIED_INGEST_AND_FIXED_POINT_STABILIZATION",

"operator_interface": {

"command": "INGEST(X)",

"input_types": ["DIRECTORY", "URL"],

"output": "STABLE_STATE_S_STAR"

},

"system_pipeline": {

"phase_1_input": {

"type": "X",

"definition": "LOCAL_DIRECTORY_OR_ROOT_URL"

},

"phase_2_deep_read": {

"enabled_if": "X_TYPE == URL",

"constraints": {

"max_depth": 2,

"domain_restriction": "SAME_DOMAIN_ONLY",

"visited_set": true,

"content_filter": ["text/html", "text/plain", "application/pdf"]

},

"output": "DOCUMENT_SET_D"

},

"phase_3_parsing": {

"inputs": "DOCUMENT_SET_D_OR_DIRECTORY_FILES",

"handlers": {

"text": "DIRECT",

"pdf": "PANDOC_CONVERSION",

"image": "METADATA_EXTRACTION",

"video": "FFMPEG_MINIMAL_PROCESSING"

},

"output": "NORMALIZED_DOCUMENT_SET_N"

},

"phase_4_structuring": {

"operations": [

"NORMALIZATION",

"CHUNKING",

"INITIAL_RELATION_MAPPING"

],

"output": "STATE_S_0"

},

"phase_5_llm_loop": {

"definition": "ITERATIVE_TRANSFORMATION",

"operator": "F",

"iteration_rule": "S_{n+1} = F(S_n)",

"F_components": [

"SEMANTIC_LINKING",

"CONSISTENCY_CHECK",

"REDUNDANCY_REDUCTION"

],

"termination_condition": {

"type": "FIXPOINT",

"formal": "S_{n+1} = S_n"

},

"output": "STATE_S_STAR"

},

"phase_6_output": {

"definition": "FINAL_STABLE_STATE",

"properties": [

"IDEMPOTENT",

"CONSISTENT",

"REDUCED",

"REPRODUCIBLE"

]

}

},

"data_configuration": {

"total_units": 100,

"distribution": {

"structured_text": "70-80",

"pdf": "10-15",

"images": "10",

"video": "1",

"optional_urls": "1-3"

},

"target_size_mb": "80-150"

},

"hard_index": {

"enabled": true,

"sources": [

"HTML_DOCUMENTATION",

"C_DOCUMENTATION",

"LINUX_KERNEL_DOCS",

"API_SPECIFICATIONS"

],

"function": "REFERENCE_ANCHORING"

},

"constraints": {

"determinism": true,

"no_randomness": true,

"no_unbounded_loops": true,

"bounded_traversal": true,

"no_kernel_dependency": true,

"execution_layer": "USER_SPACE"

},

"performance_estimate": {

"total_runtime_minutes": "20-45",

"phases": {

"deep_read": "1-5",

"parsing_structuring": "3-7",

"llm_loop": "10-30"

}

}

}