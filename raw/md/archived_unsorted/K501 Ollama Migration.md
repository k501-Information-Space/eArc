## type: technical_reference domain: Protocols status: active node: K501_NODE_001

# 🛰️ K501 Local LLM Migration: Ollama Integration

Diese Dokumentation beschreibt den Wechsel von Cloud-basierten Modellen (Gemini) zu lokalen Instanzen auf dem T520.

## 1. Installation (Debian Terminal)

Führe das offizielle Installationsskript aus:

curl -fsSL [https://ollama.com/install.sh](https://ollama.com/install.sh) | sh  

## 2. Modell-Auswahl (Optimiert für T520/8GB RAM)

Da das T520 primär über die CPU rechnet, wählen wir Modelle mit hoher Effizienz:

|**Modell**|**Befehl**|**Zweck**|
|---|---|---|
|**Qwen2.5-Coder (1.5B/3B)**|ollama pull qwen2.5-coder:3b|Hauptmodell für K501-Skripte & Logik|
|---|---|---|
|**Gemma 3 (1B)**|ollama pull gemma3:1b|Ultraschnelle Dashboard- & Index-Updates|
|---|---|---|
|**DeepSeek-R1 (7B-Distill)**|ollama pull deepseek-r1:7b|Komplexe Analysen (langsamer, aber präzise)|
|---|---|---|

## 3. Obsidian Copilot Anbindung

Um Copilot mit Ollama zu verbinden, ändere die Einstellungen in Obsidian:

1. **Provider:** Wähle Ollama.
2. **Ollama URL:** http://localhost:11434 (Standard).
3. **Model ID:** Trage den exakten Namen ein (z.B. qwen2.5-coder:3b).
4. **Indexierung:** Aktiviere unter "Vault QA" die lokale Indexierung, damit Ollama deine Notizen lesen kann, ohne die Cloud zu nutzen.

## 4. K501 Node-Spezifische Konfiguration

Erstelle ein Alias für schnelle Status-Checks im Terminal:

echo "alias k501-stats='ollama ps && free -h'" >> ~/.bashrc  

_K501_ISOS_LOCAL_AI_V1_