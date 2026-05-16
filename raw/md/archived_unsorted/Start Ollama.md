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

export OLLAMA_NUM_PARALLEL=1 # CPU-only: keine Parallel-GPU-Inferenz

# --- Logging ---

echo "[INFO] Ollama CPU-only Start"

echo "[INFO] Context Length: $OLLAMA_CONTEXT_LENGTH tokens"

echo "[INFO] Vulkan Disabled: $OLLAMA_VULKAN"

echo "[INFO] Loading models from: $OLLAMA_MODELS"

# --- Start Ollama Server ---

ollama serve \

--host 127.0.0.1 \

--port 11434 \

--keep-alive 5m \

--debug INFO

# --- Hinweise ---

# 1. Für große Modelle oder lange Kontextketten (4096+) kann der Server langsam werden.

# 2. CPU-Auslastung: Ollama kann alle Kerne nutzen, RAM-Limit beachten.

# 3. Anpassungen: OLLAMA_CONTEXT_LENGTH & OLLAMA_MAX_QUEUE je nach verfügbarem RAM optimieren.