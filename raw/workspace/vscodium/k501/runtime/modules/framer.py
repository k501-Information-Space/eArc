#!/usr/bin/env python3
"""
K501 Framer Module (Pass 3)
Role: Wraps raw binary chunks into K501 Structural Frames (Pre-Linkage)
      Injects the finalized 56-cell Quantum Header (QH_56) State Vector.
"""
import os
import sys
import json
import hashlib

def compute_sha256(filepath):
    """Computes the raw content hash of the binary chunk."""
    hasher = hashlib.sha256()
    with open(filepath, 'rb') as f:
        hasher.update(f.read())
    return hasher.hexdigest()

def frame_chunk(chunk_path, output_dir):
    """
    Wraps the chunk in a K501 frame schema.
    Initializes the rigorous Quantum Header state vector and maps the payload.
    """
    if not os.path.exists(chunk_path):
        raise FileNotFoundError(f"[FATAL] Missing chunk: {chunk_path}")
        
    filename = os.path.basename(chunk_path)
    if not filename.startswith("CHUNK-") or not filename.endswith(".bin"):
        print(f"[FRAMER] Skipping {filename}: Invalid chunk identity.")
        return None
        
    # 1. Parse Identity
    # Format: CHUNK-<source_hash>-<index>.bin
    identity_parts = filename[:-4].split('-')
    source_hash = identity_parts[1]
    chunk_index = int(identity_parts[2])
    frame_id = filename[:-4]
    
    # 2. Extract Physical Properties
    content_hash = compute_sha256(chunk_path)
    size_bytes = os.path.getsize(chunk_path)
    
    # 3. Initialize Epistemic Matrix (Quantum Header 56-cell array)
    # Legend: 0=UNKNOWN, 1=FALSE, 2=TRUE, 3=GUARD
    qh_matrix = [0] * 56
    
    # Sector 1: Epistemic State
    qh_matrix[0] = 2  # Frame Validity (TRUE - Pre-Linker status)
    qh_matrix[3] = 2  # Data Class: Signal (TRUE - This is external data)
    qh_matrix[4] = 1  # Data Class: Insight (FALSE - Not AI generated)
    
    # Sector 2: Media Topology
    qh_matrix[8] = 2  # Text/Document (TRUE - Default for current normalizer)
    
    # Sector 3: Graph Structure
    qh_matrix[16] = 1 # Is Origin (FALSE)
    qh_matrix[17] = 2 # Is Chunk (TRUE)
    qh_matrix[19] = 2 # Is Terminal / Leaf (TRUE at time of creation)
    
    # Sector 4: Provenance
    qh_matrix[24] = 2 # Normalization Complete (TRUE - Passed Sovereign Toolchain)
    qh_matrix[25] = 2 # Determinism Verified (TRUE - Metadata stripped)
    qh_matrix[26] = 2 # Cleartext (TRUE - Unencrypted)
    qh_matrix[27] = 1 # AI Restricted (FALSE - AI is permitted to read this)
    
    # 4. Construct the Canonical Payload
    frame_data = {
        "id": frame_id,
        "type": "chunk_frame",
        "qh": qh_matrix,
        "d": {
            "source_identity": source_hash,
            "chunk_index": chunk_index,
            "content_hash": content_hash,
            "size_bytes": size_bytes
        }
    }
    
    # 5. Output Intermediate Frame
    os.makedirs(output_dir, exist_ok=True)
    out_path = os.path.join(output_dir, f"{frame_id}.json")
    
    # Dump using compact separators to prevent arbitrary whitespace inflation
    with open(out_path, 'w', encoding='utf-8') as f:
        json.dump(frame_data, f, separators=(',', ':'))
        
    print(f"[FRAMER] Constructed: {frame_id}.json")
    print(f"         └─ Content Hash: {content_hash[:16]}...")
    return out_path

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 framer.py <chunk_file> <output_dir>")
        sys.exit(1)
        
    chunk_file = sys.argv[1]
    out_directory = sys.argv[2]
    
    frame_chunk(chunk_file, out_directory)