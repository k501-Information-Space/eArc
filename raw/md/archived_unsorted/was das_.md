iinkognit0@K501:/K501GeminiNet$ sudo apt update

[sudo] Passwort für iinkognit0:

OK:1 http://deb.debian.org/debian trixie InRelease

OK:2 http://security.debian.org/debian-security trixie-security InRelease

OK:3 http://deb.debian.org/debian trixie-updates InRelease

OK:4 http://deb.debian.org/debian trixie-backports InRelease

OK:5 https://download.vscodium.com/debs vscodium InRelease

OK:6 https://packages.microsoft.com/repos/code stable InRelease

OK:7 https://paulcarroty.gitlab.io/vscodium-deb-rpm-repo/debs vscodium InRelease

Alle Pakete sind aktuell.

iinkognit0@K501:/K501GeminiNet$ ollama serve

time=2026-03-14T13:42:59.403+01:00 level=INFO source=routes.go:1658 msg="server config" env="map[CUDA_VISIBLE_DEVICES: GGML_VK_VISIBLE_DEVICES: GPU_DEVICE_ORDINAL: HIP_VISIBLE_DEVICES: HSA_OVERRIDE_GFX_VERSION: HTTPS_PROXY: HTTP_PROXY: NO_PROXY: OLLAMA_CONTEXT_LENGTH:0 OLLAMA_DEBUG:INFO OLLAMA_EDITOR: OLLAMA_FLASH_ATTENTION:false OLLAMA_GPU_OVERHEAD:0 OLLAMA_HOST:http://127.0.0.1:11434 OLLAMA_KEEP_ALIVE:5m0s OLLAMA_KV_CACHE_TYPE: OLLAMA_LLM_LIBRARY: OLLAMA_LOAD_TIMEOUT:5m0s OLLAMA_MAX_LOADED_MODELS:0 OLLAMA_MAX_QUEUE:512 OLLAMA_MODELS:/home/iinkognit0/.ollama/models OLLAMA_MULTIUSER_CACHE:false OLLAMA_NEW_ENGINE:false OLLAMA_NOHISTORY:false OLLAMA_NOPRUNE:false OLLAMA_NO_CLOUD:false OLLAMA_NUM_PARALLEL:1 OLLAMA_ORIGINS:[http://localhost https://localhost http://localhost:* https://localhost:* http://127.0.0.1 https://127.0.0.1 http://127.0.0.1:* https://127.0.0.1:* http://0.0.0.0 https://0.0.0.0 http://0.0.0.0:* https://0.0.0.0:* app://* file://* tauri://* vscode-webview://* vscode-file://*] OLLAMA_REMOTES:[ollama.com] OLLAMA_SCHED_SPREAD:false OLLAMA_VULKAN:false ROCR_VISIBLE_DEVICES: http_proxy: https_proxy: no_proxy:]"

time=2026-03-14T13:42:59.404+01:00 level=INFO source=routes.go:1660 msg="Ollama cloud disabled: false"

time=2026-03-14T13:42:59.405+01:00 level=INFO source=images.go:477 msg="total blobs: 0"

time=2026-03-14T13:42:59.405+01:00 level=INFO source=images.go:484 msg="total unused blobs removed: 0"

time=2026-03-14T13:42:59.405+01:00 level=INFO source=routes.go:1713 msg="Listening on 127.0.0.1:11434 (version 0.17.7)"

time=2026-03-14T13:42:59.409+01:00 level=INFO source=runner.go:67 msg="discovering available GPUs..."

time=2026-03-14T13:42:59.413+01:00 level=INFO source=server.go:430 msg="starting runner" cmd="/usr/local/bin/ollama runner --ollama-engine --port 43719"

time=2026-03-14T13:42:59.487+01:00 level=INFO source=runner.go:106 msg="experimental Vulkan support disabled. To enable, set OLLAMA_VULKAN=1"

time=2026-03-14T13:42:59.487+01:00 level=INFO source=server.go:430 msg="starting runner" cmd="/usr/local/bin/ollama runner --ollama-engine --port 45543"

time=2026-03-14T13:42:59.534+01:00 level=INFO source=types.go:60 msg="inference compute" id=cpu library=cpu compute="" name=cpu description=cpu libdirs=ollama driver="" pci_id="" type="" total="11.6 GiB" available="9.6 GiB"

time=2026-03-14T13:42:59.534+01:00 level=INFO source=routes.go:1763 msg="vram-based default context" total_vram="0 B" default_num_ctx=4096

^Ciinkognit0@K501:/K501GeminiNet$