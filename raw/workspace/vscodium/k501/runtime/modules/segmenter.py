#!/usr/bin/env python3
"""
K501 Segmenter Module (Pass 2)
Role: Deterministic Streaming Block Extraction (4096 Bytes)
"""
import os
import sys

CHUNK_SIZE = 4096

def validate_normalized_filename(filename):
    """Ensures the segmenter only processes mathematically bound files."""
    if not filename.startswith("NORM-") or not filename.endswith(".txt"):
        return False
    return True

def segment_file(input_path, output_dir):
    """
    Streams a file and splits it into strict 4096-byte logical chunks.
    No semantic parsing occurs here. Memory profile is perfectly flat.
    """
    if not os.path.exists(input_path):
        raise FileNotFoundError(f"[FATAL] Missing normalized input: {input_path}")
        
    filename = os.path.basename(input_path)
    if not validate_normalized_filename(filename):
        print(f"[SEGMENTER] Skipping {filename}: Not a valid K501 normalized file.")
        return 0

    # Extract the locked source hash from the filename (e.g., NORM-<hash>.txt)
    # This ensures child chunks retain their parent's genetic identity
    source_identity = filename[5:-4] 
    
    os.makedirs(output_dir, exist_ok=True)
    
    chunk_index = 0
    bytes_processed = 0
    
    # Bounded Streaming Read (Prevents OOM on large files)
    with open(input_path, 'rb') as f:
        while True:
            chunk = f.read(CHUNK_SIZE)
            if not chunk:
                break
                
            # Deterministic Chunk Naming Convention
            # Format: CHUNK-<source_identity>-<sequential_index>.bin
            chunk_filename = f"CHUNK-{source_identity}-{chunk_index:06d}.bin"
            chunk_path = os.path.join(output_dir, chunk_filename)
            
            with open(chunk_path, 'wb') as out_f:
                out_f.write(chunk)
                
            chunk_index += 1
            bytes_processed += len(chunk)

    print(f"[SEGMENTER] Processed {bytes_processed} bytes into {chunk_index} blocks.")
    return chunk_index

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 segmenter.py <normalized_file> <output_dir>")
        sys.exit(1)
        
    input_file = sys.argv[1]
    out_directory = sys.argv[2]
    
    segment_file(input_file, out_directory)