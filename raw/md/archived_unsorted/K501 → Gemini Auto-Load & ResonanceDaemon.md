# ============================================================

# FILENAME: scripts/k501_gemini_autoload.py

# PURPOSE: Auto-Load migrated QAL frames into Gemini

# Initialize ResonanceDaemon for Ledger sync

# ============================================================

import json

from k501_core import Gemini, ResonanceDaemon

GEMINI_JSON_PATH = "~/K501_Vault/archive/migration_gemini.json"

# 1. Gemini-Instanz initialisieren

gemini = Gemini()

resonance = ResonanceDaemon(gemini)

# 2. JSON laden

with open(GEMINI_JSON_PATH, "r", encoding="utf-8") as f:

data = json.load(f)

frames = data.get("frames", [])

epoch = data.get("epoch")

quantum_root = data.get("quantum_root")

frame_count = data.get("frame_count")

print(f"[*] Loading {frame_count} frames into Gemini")

print(f"[*] Epoch: {epoch}, QuantumRoot: {quantum_root}")

# 3. Frames injizieren

for frame_dict in frames:

gemini.ingest_frame(frame_dict)

# 4. ResonanceDaemon starten

resonance.start(sync=True)

print("[*] ResonanceDaemon started, Ledger synchronized.")

# 5. Statuscheck

status = gemini.status()

print(f"[*] Gemini Status: {status}")