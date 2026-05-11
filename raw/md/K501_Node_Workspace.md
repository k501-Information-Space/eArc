{

"K501_Node_Workspace": {

"modules": {

"QH256_Core": {

"path": "modules/QH256_Core/",

"schema": "schemas/QH256_Core.json",

"launcher": "launch_core.py",

"test_data": "test_frames/"

},

"QH256_Algebra": {

"path": "modules/QH256_Algebra/",

"schema": "schemas/QH256_Algebra.json",

"launcher": "launch_algebra.py"

},

"QH256_Index": {

"path": "modules/QH256_Index/",

"schema": "schemas/QH256_Index.json",

"launcher": "launch_index.py"

},

"QH256_IO_Header": {

"path": "modules/QH256_IO_Header/",

"schema": "schemas/QH256_IO_Header.json",

"launcher": "launch_io.py"

},

"QH128_HardIndex": {

"path": "modules/QH128_HardIndex/",

"schema": "schemas/QH128_HardIndex.json",

"launcher": "launch_hardindex.py"

},

"QH256_AlgebraIndex": {

"path": "modules/QH256_AlgebraIndex/",

"schema": "schemas/QH256_AlgebraIndex.json",

"launcher": "launch_alg_index.py"

},

"QH256_MediaDecode": {

"path": "modules/QH256_MediaDecode/",

"schema": "schemas/QH256_MediaDecode.json",

"launcher": "launch_media.py",

"sample_media": "test_media/"

},

"QH256_LLM": {

"path": "modules/QH256_LLM/",

"schema": "schemas/QH256_LLM.json",

"launcher": "launch_llm.py"

},

"QH256_Communication": {

"path": "modules/QH256_Communication/",

"schema": "schemas/QH256_Communication.json",

"launcher": "launch_comm.py"

},

"Minimalpipeline": {

"path": "modules/Minimalpipeline/",

"schema": "schemas/Minimalpipeline.json",

"launcher": "launch_pipeline.py"

}

},

"workspace_settings": {

"AVX": "AVX1 fallback, AVX2 optional",

"iGPU": "OpenCL/Vulkan deterministic compute",

"LinuxKernel": {

"Scheduler": "SCHED_FIFO / SCHED_DEADLINE",

"HugePages": "2MB/1GB for embeddings & hard index",

"IOScheduler": "noop / deadline",

"MemoryOvercommit": "vm.overcommit_memory=2, vm.swappiness=0"

},

"RAM_Optimization": "Memory-mapped files, 32-byte alignment, prefetching",

"SSD_Optimization": "Append-only, async IO, lossless compression"

}

}

}