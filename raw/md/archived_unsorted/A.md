{

"artifact": "K501_Little_Alpha_QRL",

"version": "0.1",

"timestamp_unix": 1773529667,

"mode": "QRL_compact",

"goal": "minimal_compilable_single_node",

"system_model": {

"definition": "K501 = (F,R,T,H,I,AI)",

"graph": "GI = (F,E,I)",

"properties": [

"append_only",

"hash_chained",

"origin_rooted",

"deterministic_serialization",

"indexed"

]

},

"frame_chain": [

"f0_genesis",

"f1_topology_insight",

"f2...fn_signal_frames"

],

"quantum_header": {

"type": "QH56",

"cells": 56,

"states": {

"00": "UNKNOWN",

"01": "FALSE",

"10": "TRUE",

"11": "GUARD"

}

},

"little_alpha_modules": [

{

"name": "qh_algebra",

"file": "qh_algebra.c",

"purpose": "quantum_header_logic"

},

{

"name": "qh_core",

"file": "qh_core.c",

"purpose": "frame_construction"

},

{

"name": "frame_engine",

"file": "frame_engine.c",

"purpose": "hash_and_serialization"

},

{

"name": "hard_index",

"file": "hard_index.c",

"purpose": "deterministic_lookup"

},

{

"name": "dynamic_cage",

"file": "dynamic_cage.c",

"purpose": "frame_validation_guard"

},

{

"name": "ingestion",

"file": "ingestion.c",

"purpose": "document_to_signal_frames"

}

],

"workspace_structure": {

"root": "k501_alpha",

"dirs": [

"src",

"storage",

"docs/input"

],

"files": [

"frames.ndjson",

"Makefile"

]

},

"serialization": {

"format": "JCS_RFC8785",

"encoding": "UTF8_NFC",

"hash": "SHA256(JCS(frame_without_h))"

},

"frame_template": {

"fields_order": [

"id",

"type",

"t",

"h",

"d",

"qh",

"relations"

]

},

"ingestion_pipeline": [

"document_input",

"utf8_normalize",

"chunk_4096_bytes",

"sha256_chunk_hash",

"signal_frame_generation",

"append_to_frames_ndjson"

],

"storage": {

"format": "NDJSON",

"primary_file": "frames.ndjson"

},

"compile": {

"binary": "k501_alpha",

"command": "gcc -O2 src/*.c -o k501_alpha"

},

"cli": [

"k501_alpha genesis",

"k501_alpha append",

"k501_alpha ingest <document>",

"k501_alpha verify"

],

"little_alpha_capabilities": [

"create_frames",

"validate_frames",

"append_only_storage",

"deterministic_hashing",

"document_ingestion",

"basic_query"

],

"project_progress": {

"architecture": 1.0,

"core_runtime": 0.9,

"ingestion": 0.8,

"query_engine": 0.4,

"network": 0.0,

"overall": 0.85

},

"next_stage": {

"name": "K501_Beta",

"features": [

"node_replication",

"network_protocol",

"hash_consensus",

"distributed_query",

"ai_cluster_engine"

]

}

}