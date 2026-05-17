iinkognit0@K501:/K501GeminiNet/core$ cd /K501GeminiNet/core

sudo make clean

sudo make

rm -f libk501.so *.o

gcc -O3 -mavx -pthread -fPIC -Wall -shared -o libk501.so qh256_algebra.c

iinkognit0@K501:/K501GeminiNet/core$ sudo PYTHONPATH=/K501GeminiNet python3 /K501GeminiNet/search.py "Worauf stützt sich die Logik der Hardware?"

[*] STARTE SEMANTISCHE RESONANZ-ANALYSE

[*] Query: "Worauf stützt sich die Logik der Hardware?"

Speicherzugriffsfehler

iinkognit0@K501:/K501GeminiNet/core$ ^[[200~#!/bin/bash

bash: !/bin/bash: event not found

iinkognit0@K501:/K501GeminiNet/core$ # ============================================================

iinkognit0@K501:/K501GeminiNet/core$ # K501 System Stabilitäts-Check

iinkognit0@K501:/K501GeminiNet/core$ # Prüft Ledger, C-Symbole, Multipass und iGPU

iinkognit0@K501:/K501GeminiNet/core$ # ============================================================

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ BASE_DIR="/K501GeminiNet"

iinkognit0@K501:/K501GeminiNet/core$ LEDGER="$BASE_DIR/Node01/vault/ledger/frames.ndjson"

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ echo "=== [K501 SYSTEM CHECK] ==="

=== [K501 SYSTEM CHECK] ===

iinkognit0@K501:/K501GeminiNet/core$ echo "Unix Epoch: $(date +%s)"

Unix Epoch: 1773415396

iinkognit0@K501:/K501GeminiNet/core$ echo "Node: NODE_K501_T520_01"

Node: NODE_K501_T520_01

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ # 1. Ledger-Harmonisierung

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ echo "[*] Prüfe Ledger-Integrität..."

[*] Prüfe Ledger-Integrität...

iinkognit0@K501:/K501GeminiNet/core$ if [ ! -f "$LEDGER" ]; then

> echo "[!] Ledger nicht gefunden: $LEDGER"

> else

> python3 - <<EOF

> import json

>

> ledger_file = "$LEDGER"

> ok = True

> with open(ledger_file, "r") as f:

> prev_hash = None

> for i, line in enumerate(f):

> frame = json.loads(line)

> if i > 0 and frame.get("prev") != prev_hash:

> print(f"[!] Fehler: Frame {frame['id']} hat falsches prev_hash")

> ok = False

> prev_hash = frame.get("id")

> if ok:

> print("[+] Ledger-Harmonisierung OK")

> EOF

> fi

[!] Fehler: Frame e8c4a2845129fe6684b9fb9f65bf3afd9efadf6b3c0a5e6f8dddfb0a404b6589 hat falsches prev_hash

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ # 2. Symbol-Test (Python → C)

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ echo "[*] Prüfe C-Symbol qh256_batch_resonance..."

[*] Prüfe C-Symbol qh256_batch_resonance...

iinkognit0@K501:/K501GeminiNet/core$ python3 - <<EOF

> import ctypes, os

> try:

> lib = ctypes.CDLL("$BASE_DIR/core/libk501.so")

> func = getattr(lib, "qh256_batch_resonance")

> print("[+] Symbol-Test erfolgreich: qh256_batch_resonance gefunden")

> except AttributeError:

> print("[!] Symbol-Test fehlgeschlagen: qh256_batch_resonance fehlt")

> EOF

[+] Symbol-Test erfolgreich: qh256_batch_resonance gefunden

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ # 3. Mini-Multipass Simulation

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ echo "[*] Starte Mini-Multipass-Simulation..."

[*] Starte Mini-Multipass-Simulation...

iinkognit0@K501:/K501GeminiNet/core$ python3 - <<EOF

> from pathlib import Path

> import random

> from modules.QH256_Core.launch_core import QH256Core

>

> ledger_path = "$LEDGER"

> core = QH256Core(ledger_path)

>

> # Mini-Test-Frame

> test_payload = f"Test-Frame {random.randint(0,999)}"

> frame = core.generate_frame(payload=test_payload, vector=[0.1]*32, metadata={"origin":"system_check"})

> core.commit(frame)

> print("[+] Mini-Multipass Simulation abgeschlossen")

> EOF

Traceback (most recent call last):

File "<stdin>", line 3, in <module>

ModuleNotFoundError: No module named 'modules'

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ # 4. iGPU Check (Vektor-Berechnung)

iinkognit0@K501:/K501GeminiNet/core$ # -------------------------

iinkognit0@K501:/K501GeminiNet/core$ echo "[*] Prüfe iGPU Vektor-Berechnung..."

[*] Prüfe iGPU Vektor-Berechnung...

iinkognit0@K501:/K501GeminiNet/core$ python3 - <<EOF

> try:

> import numpy as np

> vec_cpu = np.random.rand(32)

> vec_gpu = vec_cpu.copy() # simuliert einfache iGPU-Auslagerung

> dot = np.dot(vec_cpu, vec_gpu)

> print(f"[+] iGPU-Vektor-Berechnung OK, Dot-Produkt={dot:.4f}")

> except Exception as e:

> print(f"[!] iGPU-Vektor-Berechnung fehlgeschlagen: {e}")

> EOF

[+] iGPU-Vektor-Berechnung OK, Dot-Produkt=11.8031

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ echo "=== [K501 SYSTEM CHECK ENDE] ===".

=== [K501 SYSTEM CHECK ENDE] ===.

iinkognit0@K501:/K501GeminiNet/core$

iinkognit0@K501:/K501GeminiNet/core$ ~