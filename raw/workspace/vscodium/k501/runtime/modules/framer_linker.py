#!/usr/bin/env python3
"""
K501 Framer & Linker (Combined Module)
Reads a chunk, builds the canonical frame, fetches the previous hash, and appends directly to the Ledger.
Zero intermediate disk I/O.
"""

import sys
import os
import time
import json
import hashlib

# Importiere den Quantizer aus demselben Verzeichnis
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quantizer

def get_last_hash(ledger_path):
    """Liest extrem schnell den letzten Hash aus dem Ledger, ohne die ganze Datei zu laden."""
    if not os.path.exists(ledger_path) or os.path.getsize(ledger_path) == 0:
        return "GENESIS_HASH_00000000000000000000000000000000000000000000000000000"
    
    with open(ledger_path, 'rb') as f:
        f.seek(0, 2)
        size = f.tell()
        # Gehe 2048 Bytes zurück, um sicher die letzte Zeile zu erwischen
        f.seek(max(size - 2048, 0), 0)
        lines = f.readlines()
        if lines:
            last_line = lines[-1].decode('utf-8').strip()
            if last_line:
                try:
                    return json.loads(last_line).get("hash", "ERROR_NO_HASH")
                except json.JSONDecodeError:
                    pass
    return "ERROR_READING_LEDGER"

def main():
    if len(sys.argv) != 3:
        print("Usage: framer_linker.py <chunk_bin_path> <ledger_ndjson_path>")
        sys.exit(1)

    chunk_path = sys.argv[1]
    ledger_path = sys.argv[2]

    # 1. Metadaten aus Dateinamen extrahieren (Format: CHUNK-[HASH]-[INDEX].bin)
    filename = os.path.basename(chunk_path)
    parts = filename.replace(".bin", "").split("-")
    sid = parts[1]
    idx = int(parts[2])

    # 2. Chunk-Daten lesen und hashen
    with open(chunk_path, 'rb') as f:
        data = f.read()
    content_hash = hashlib.sha256(data).hexdigest()
    size_bytes = len(data)

    # Standard Quantum Header (Statisch für dieses Stadium)
    qh = [2,0,0,2,1,0,0,0,2,0,0,0,0,0,0,0,1,2,0,2,0,0,0,0,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

    # 3. Frame Konstruktion (Framer)
    frame = {
        "id": f"CHUNK-{sid}-{idx:06d}",
        "type": "chunk_frame",
        "qh": qh,
        "d": {
            "source_identity": sid,
            "chunk_index": idx,
            "content_hash": content_hash,
            "size_bytes": size_bytes
        },
        "t": int(time.time()),
        "relations": {
            "origin": "AZ-Epoch-0-Genesis",
            "parent": f"CHUNK-{sid}-{idx:06d}",
            "hash_prev": get_last_hash(ledger_path)
        }
    }

    # 4. Hash Berechnung (Linker + Quantizer)
    frame["hash"] = quantizer.compute_frame_hash(frame)

    # 5. Atomarer Append an den Ledger
    with open(ledger_path, 'a', encoding='utf-8') as f:
        f.write(json.dumps(frame, separators=(',', ':'), ensure_ascii=False) + '\n')

if __name__ == "__main__":
    main()