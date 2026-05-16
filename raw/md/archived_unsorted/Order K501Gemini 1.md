{

"K501Gemini_ImplementationPlan": {

"Mode": "StrictLogic",

"Timestamp": {

"Unix": 1773322301,

"UTC": "2026-03-12T13:31:41Z",

"CET": "2026-03-12T14:31:41+01:00"

},

"1_WorkingEnvironment": {

"TerminalTools": [

"tree",

"git",

"build-essential",

"python3",

"python3-pip",

"ffmpeg",

"curl",

"jq"

],

"InstallCommand": "sudo apt update && sudo apt install tree git build-essential python3 python3-pip ffmpeg curl jq",

"Repositories": {

"Ollama": "<ollama_repo_url> ollama",

"K501Core": "<k501_core_repo_url> K501Core",

"FFmpeg": "https://github.com/FFmpeg/FFmpeg ffmpeg",

"Mastodon": "https://github.com/mastodon/mastodon mastodon"

},

"DirectoryCheck": {

"Path": "/path/to/K501Core",

"TreeDepth": 2,

"ExpectedDirs": [

"IngestPy/",

"FrameGen/",

"qh256/",

"VectorKernel/",

"ANNResonance/",

"Ledger/",

"Bridge/"

]

}

},

"2_NodeFolderSelection": {

"BaseFolder": "~/K501Gemini/Node01",

"Commands": [

"mkdir -p ~/K501Gemini/Node01",

"cd ~/K501Gemini/Node01",

"tree -L 3 > K501NodeTree.txt",

"find . -type f \\( -name \"*.py\" -o -name \"*.c\" -o -name \"*.cpp\" -o -name \"*.js\" \\) > K501NodeCodeList.txt"

]

},

"3_CodePipelineStructure": {

"Purpose": "Gemini erkennt Node-Funktionalität vor Implementierung",

"Modules": {

"IngestPy": "liest Dateien/Streams ein, erstellt Rohframes",

"FrameGen": "erzeugt Frame-Struktur (id, ts, payload, hash, vector)",

"qh256Kernel": "deterministisches Hashing",

"VectorKernel": "AVX/SIMD Projektion",

"ANNResonanceEngine": "HNSW/LSH/IVF, spärlicher Frame-Graph",

"Ledger": "NDJSON Append-Only",

"BridgeNode": "Web Interface, Ollama Adapter, Peer-to-Peer (Mastodon)"

}

},

"4_GeminiStepByStepInstructions": {

"1_NodeScan": {

"Goal": "Alle Ordner und Dateien erkennen",

"Commands": ["tree", "find"],

"Outputs": ["K501NodeTree.txt", "K501NodeCodeList.txt"]

},

"2_CodeAnalysis": {

"DetectedPipeline": ["Ingest", "FrameGen", "Kernel", "ANN", "Ledger", "Bridge"],

"OptimizationsFlagged": ["SIMD", "AVX", "ANN Index", "Edge-LLM"]

},

"3_LLMCheck": {

"OllamaAdapter": true,

"Models": ["Qwen2.5 0.5B", "Llama 3.2 1B", "Phi-3 Mini"],

"LedgerAccess": "read-only"

},

"4_MediaPipelineInit": {

"FFmpegCheck": true,

"MastodonP2PCheck": true

},

"5_NodeOverviewGeneration": {

"OutputFile": "K501NodeOverview.md",

"Contents": ["Pipeline-Diagramm", "Optimierungsstatus", "LLM-Zuordnung", "Media & P2P Module"]

},

"6_ImplementationPlan": {

"Mapping": "Node-Ordnerstruktur → Pipeline",

"Resources": ["Speicherbedarf", "Thread-Zuweisung", "Buffers"],

"OutputFile": "NodePlan.json"

},

"7_ConfigurationCheck": {

"KernelParams": ["vm.dirty_ratio", "vm.dirty_background_ratio", "vm.swappiness", "fs.aio-max-nr"],

"IOBuffers": ["16MB Write", "8MB Read"],

"SIMD_AVX_Detection": true

},

"8_ExecutionReady": {

"OperatorCommand": "./K501Core/run_node.sh",

"GeminiMonitoring": ["Frames", "ANN", "Ledger"],

"LLMBehavior": "read-only, Vorschläge → operator_confirm()"

}

},

"5_SecurityStabilityRules": {

"Ledger": {

"AppendOnly": true,

"LLMWrite": false

},

"EdgeLLM": {

"Local": true,

"MaxRAM": "2.5GB"

},

"P2PCommunication": {

"Method": ["Mastodon", "Direct Node Messaging"],

"CentralDependency": false

},

"MediaPipeline": {

"FFmpeg": true,

"PreprocessingOptional": true

}

},

"6_Result": {

"NodeCataloged": true,

"CodeBlocksReferenced": true,

"LLMReferenced": true,

"MediaModulesReferenced": true,

"ReadyForImplementationMonitoring": true

}

}

}