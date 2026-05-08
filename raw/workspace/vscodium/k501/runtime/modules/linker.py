#!/usr/bin/env python3
"""
K501 Linker Module (Pass 4b)
Role: Temporal Anchoring, Relational Binding, and Bounded Disk Append
"""
import os
import sys
import json
import time
from quantizer import compute_frame_hash

# Path Fallbacks: Tries the physical eSATA drive, falls back to local workspace archive
STORAGE_DIR = "/opt/k501/data"
if not os.path.exists(STORAGE_DIR):
    STORAGE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../archive/little_alpha_storage"))

NDJSON_FILE = os.path.join(STORAGE_DIR, "frames.ndjson")
INDEX_FILE = os.path.join(STORAGE_DIR, "index.dat")

def get_archive_head():
    """Reads the last frame in the NDJSON to determine temporal and relational state."""
    if not os.path.exists(NDJSON_FILE) or os.path.getsize(NDJSON_FILE) == 0:
        raise FileNotFoundError("[FATAL] Genesis Block missing. Run C-Kernel genesis first.")
        
    # Efficiently read the last line without loading the whole file into RAM
    with open(NDJSON_FILE, 'rb') as f:
        f.seek(-2, os.SEEK_END)
        while f.read(1) != b'\n':
            f.seek(-2, os.SEEK_CUR)
            if f.tell() == 0:
                f.seek(0)
                break
        last_line = f.readline().decode('utf-8')
        
    last_frame = json.loads(last_line)
    return last_frame.get('hash'), last_frame.get('t')

def link_and_append(frame_path):
    """Injects relations and time, hashes the frame, and appends it to storage."""
    if not os.path.exists(frame_path):
        raise FileNotFoundError(f"[FATAL] Missing intermediate frame: {frame_path}")

    # 1. Load the intermediate JSON
    with open(frame_path, 'r', encoding='utf-8') as f:
        frame_dict = json.load(f)

    # 2. Query Archive HEAD
    prev_hash, prev_t = get_archive_head()

    # 3. Enforce Temporal Monotonicity
    current_time = int(time.time())
    if current_time <= prev_t:
        current_time = prev_t + 1  # Mathematical strict forward-progression

    frame_dict['t'] = current_time

    # 4. Inject Relational Bindings
    frame_dict['relations'] = {
        "origin": "AZ-Epoch-0-Genesis",
        "parent": frame_dict['id'],  # The chunk's parent is its own source ID
        "hash_prev": prev_hash
    }

    # 5. Compute Final Cryptographic Identity
    final_hash = compute_frame_hash(frame_dict)
    frame_dict['hash'] = final_hash

    # 6. Physical Append to Domain A Storage
    # Generate final compact JCS string for storage
    final_json_string = json.dumps(frame_dict, separators=(',', ':'), ensure_ascii=False)
    
    with open(NDJSON_FILE, 'a', encoding='utf-8') as out_f:
        out_f.write(final_json_string + '\n')

    print(f"[LINKER] Appended: {frame_dict['id']}")
    print(f"         └─ Hash: {final_hash}")
    print(f"         └─ T:    {current_time}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 linker.py <intermediate_frame.json>")
        sys.exit(1)
        
    frame_file = sys.argv[1]
    link_and_append(frame_file)