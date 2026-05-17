#!/bin/bash

# Ollama CPU-only Startscript für Intel HD iGPU

# Author: iinkognit0

# Date: 2026-03-14

# --- Environment Setup ---

export OLLAMA_VULKAN=0 # Vulkan deaktivieren, da iGPU nicht unterstützt

export OLLAMA_MULTIUSER_CACHE=false # Single-user, Cache lokal

export OLLAMA_NO_CLOUD=true # Cloud-Features deaktivieren

export OLLAMA_CONTEXT_LENGTH=2048 # RAM-schonender Token-Kontext

export OLLAMA_LOAD_TIMEOUT=5m0s # Timeout für Modell-Load

export OLLAMA_MAX_QUEUE=128 # CPU-only Queue verkleinern

export OLLAMA_MODELS="$HOME/.ollama/models"

export OLLAMA_MAX_LOADED_MODELS=1 # Nur 1 Modell gleichzeitig laden

# 3. Anpassungen: OLLAMA_CONTEXT_LENGTH & OLLAMA_MAX_QUEUE je nach verfügbarem RAM optimieren.

[INFO] Ollama CPU-only Start

[INFO] Context Length: 2048 tokens

[INFO] Vulkan Disabled: 0

[INFO] Loading models from: /home/iinkognit0/.ollama/models

Error: unknown flag: --host

iinkognit0@K501:/K501GeminiNet$