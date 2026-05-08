#!/usr/bin/env python3
"""
K501 Ingest Orchestrator (V4.5 Hybrid)
Phase 2: 75 FPS Limit / Stable Subprocess Architecture
Combined Framer-Linker Module / Zero Intermediate Disk I/O
"""

import os
import sys
import subprocess
import json
import time

BASE_DIR = "/home/iinkognit0/k501_ingest_staging"
INPUT_DIR = os.path.join(BASE_DIR, "input")
LEDGER_FILE = "/home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson"
MODULES_DIR = "/home/iinkognit0/workspace/k501/runtime/modules"

WORK_DIRS = {
    "norm": os.path.join(BASE_DIR, "work/1_norm"),
    "chunks": os.path.join(BASE_DIR, "work/2_chunks")
}

TARGET_FPS = 75
FRAME_DELAY = 1.0 / TARGET_FPS

def get_ledger_state():
    state = {}
    if not os.path.exists(LEDGER_FILE): return state
    print(f"[K501] Booting... Scanning Ledger Integrity...")
    with open(LEDGER_FILE, 'r') as f:
        for line in f:
            try:
                data = json.loads(line)
                if data.get("type") == "chunk_frame":
                    sid = data["d"]["source_identity"]
                    idx = data["d"]["chunk_index"]
                    state[sid] = max(state.get(sid, -1), idx)
            except: continue
    return state

def run_module(module_name, *args):
    """Klassischer, fehlerresistenter Subprozess-Aufruf."""
    script_path = os.path.join(MODULES_DIR, f"{module_name}.py")
    cmd = [sys.executable, script_path] + list(args)
    subprocess.run(cmd, check=True, capture_output=True)

def orchestrate():
    ledger_state = get_ledger_state()
    
    files = []
    for root, _, filenames in os.walk(INPUT_DIR):
        for f in filenames: files.append(os.path.join(root, f))
    
    print(f"==================================================")
    print(f"[K501] HYBRID V4.5 ENGAGED: {TARGET_FPS} FPS TARGET")
    print(f"==================================================")

    for i, target_file in enumerate(files, 1):
        filename = os.path.basename(target_file)
        
        # 1. Normalizer
        run_module("normalizer", target_file, WORK_DIRS["norm"])
        norm_list = os.listdir(WORK_DIRS["norm"])
        if not norm_list: continue
        
        norm_path = os.path.join(WORK_DIRS["norm"], norm_list[0])
        sid = norm_list[0].replace("NORM-", "").replace(".txt", "")
        last_idx = ledger_state.get(sid, -1)
        
        # 2. Segmenter
        run_module("segmenter", norm_path, WORK_DIRS["chunks"])
        chunk_files = sorted([f for f in os.listdir(WORK_DIRS["chunks"]) if f.endswith(".bin")])
        
        if last_idx >= len(chunk_files) - 1:
            pass # Datei bereits komplett im Ledger
        else:
            print(f"[{i}/{len(files)}] {filename[:30]:<30} | Resuming: Chunk {last_idx + 1}")
            for chunk_file in chunk_files:
                idx = int(chunk_file.split("-")[-1].split(".")[0])
                if idx <= last_idx: continue

                start_time = time.time()
                chunk_full_path = os.path.join(WORK_DIRS["chunks"], chunk_file)
                
                # 3. Combined Framer & Linker
                run_module("framer_linker", chunk_full_path, LEDGER_FILE)

                # Governor
                elapsed = time.time() - start_time
                time.sleep(max(0, FRAME_DELAY - elapsed))

        # Cleanup
        for d in WORK_DIRS.values():
            for f in os.listdir(d):
                try: os.remove(os.path.join(d, f))
                except: pass

if __name__ == "__main__":
    try:
        orchestrate()
        print("\n[K501] INGEST COMPLETE.")
    except KeyboardInterrupt:
        print("\n[K501] Halted by Operator.")