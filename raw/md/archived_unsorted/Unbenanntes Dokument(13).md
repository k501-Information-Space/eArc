iinkognit0@K501:/K501GeminiNet$ sudo systemctl stop ollama

iinkognit0@K501:/K501GeminiNet$ ^[[200~iinkognit0@K501:/K501GeminiNet$ #!/bin/bash

bash: iinkognit0@K501:/K501GeminiNet$: Datei oder Verzeichnis nicht gefunden

iinkognit0@K501:/K501GeminiNet$ # Ollama CPU-only Startscript für Intel HD iGPU

iinkognit0@K501:/K501GeminiNet$ # Author: iinkognit0

iinkognit0@K501:/K501GeminiNet$ # Date: 2026-03-14

iinkognit0@K501:/K501GeminiNet$

iinkognit0@K501:/K501GeminiNet$ # --- Environment Setup ---

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_VULKAN=0 # Vulkan deaktivieren, da iGPU nicht unterstützt

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_MULTIUSER_CACHE=false # Single-user, Cache lokal

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_NO_CLOUD=true # Cloud-Features deaktivieren

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_CONTEXT_LENGTH=2048 # RAM-schonender Token-Kontext

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_LOAD_TIMEOUT=5m0s # Timeout für Modell-Load

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_MAX_QUEUE=128 # CPU-only Queue verkleinern

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_MODELS="$HOME/.ollama/models"

iinkognit0@K501:/K501GeminiNet$ export OLLAMA_MAX_LOADED_MODELS=1 # Nur 1 Modell gleichzeitig laden

iinkognit0@K501:/K501GeminiNet$ # 3. Anpassungen: OLLAMA_CONTEXT_LENGTH & OLLAMA_MAX_QUEUE je nach verfügbarem RAM optimieren.

iinkognit0@K501:/K501GeminiNet$ [INFO] Ollama CPU-only Start

bash: [INFO]: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ [INFO] Context Length: 2048 tokens

bash: [INFO]: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ [INFO] Vulkan Disabled: 0

bash: [INFO]: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ [INFO] Loading models from: /home/iinkognit0/.ollama/models

bash: [INFO]: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ Error: unknown flag: --host

bash: Error:: Kommando nicht gefunden.

iinkognit0@K501:/K501GeminiNet$ iinkognit0@K501:/K501GeminiNet$ ~