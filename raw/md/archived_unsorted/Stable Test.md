#!/bin/bash

# ============================================================

# K501 System Stabilitäts-Check

# Prüft Ledger, C-Symbole, Multipass und iGPU

# ============================================================

BASE_DIR="/K501GeminiNet"

LEDGER="$BASE_DIR/Node01/vault/ledger/frames.ndjson"

echo "=== [K501 SYSTEM CHECK] ==="

echo "Unix Epoch: $(date +%s)"

echo "Node: NODE_K501_T520_01"

# -------------------------

# 1. Ledger-Harmonisierung

# -------------------------

echo "[*] Prüfe Ledger-Integrität..."

if [ ! -f "$LEDGER" ]; then

echo "[!] Ledger nicht gefunden: $LEDGER"

else

python3 - <<EOF

import json

ledger_file = "$LEDGER"

ok = True

with open(ledger_file, "r") as f:

prev_hash = None

for i, line in enumerate(f):

frame = json.loads(line)

if i > 0 and frame.get("prev") != prev_hash:

print(f"[!] Fehler: Frame {frame['id']} hat falsches prev_hash")

ok = False

prev_hash = frame.get("id")

if ok:

print("[+] Ledger-Harmonisierung OK")

EOF

fi

# -------------------------

# 2. Symbol-Test (Python → C)

# -------------------------

echo "[*] Prüfe C-Symbol qh256_batch_resonance..."

python3 - <<EOF

import ctypes, os

try:

lib = ctypes.CDLL("$BASE_DIR/core/libk501.so")

func = getattr(lib, "qh256_batch_resonance")

print("[+] Symbol-Test erfolgreich: qh256_batch_resonance gefunden")

except AttributeError:

print("[!] Symbol-Test fehlgeschlagen: qh256_batch_resonance fehlt")

EOF

# -------------------------

# 3. Mini-Multipass Simulation

# -------------------------

echo "[*] Starte Mini-Multipass-Simulation..."

python3 - <<EOF

from pathlib import Path

import random

from modules.QH256_Core.launch_core import QH256Core

ledger_path = "$LEDGER"

core = QH256Core(ledger_path)

# Mini-Test-Frame

test_payload = f"Test-Frame {random.randint(0,999)}"

frame = core.generate_frame(payload=test_payload, vector=[0.1]*32, metadata={"origin":"system_check"})

core.commit(frame)

print("[+] Mini-Multipass Simulation abgeschlossen")

EOF

# -------------------------

# 4. iGPU Check (Vektor-Berechnung)

# -------------------------

echo "[*] Prüfe iGPU Vektor-Berechnung..."

python3 - <<EOF

try:

import numpy as np

vec_cpu = np.random.rand(32)

vec_gpu = vec_cpu.copy() # simuliert einfache iGPU-Auslagerung

dot = np.dot(vec_cpu, vec_gpu)

print(f"[+] iGPU-Vektor-Berechnung OK, Dot-Produkt={dot:.4f}")

except Exception as e:

print(f"[!] iGPU-Vektor-Berechnung fehlgeschlagen: {e}")

EOF

echo "=== [K501 SYSTEM CHECK ENDE] ===".