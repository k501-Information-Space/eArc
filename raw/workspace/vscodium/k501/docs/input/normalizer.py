#!/usr/bin/env python3
"""
K501 Normalizer Module (Pass 1)
Role: Deterministic Metadata Stripping & Format Unification
"""
import os
import subprocess
import hashlib
import sys
import shutil

# 1. Strict Path Execution (Binding to the Sovereign Toolchain)
# Falls back to local system binaries if /opt is not yet populated
ST_ROOT_BIN = "/opt/k501/st_root/bin"

def get_binary_path(binary_name):
    st_path = os.path.join(ST_ROOT_BIN, binary_name)
    if os.path.exists(st_path):
        return st_path
    # Fallback to system path for development/testing phase
    sys_path = shutil.which(binary_name)
    if not sys_path:
        raise FileNotFoundError(f"[FATAL] Sovereign Toolchain binary missing: {binary_name}")
    return sys_path

def compute_sha256(filepath):
    """Computes a deterministic hash of a file without loading it all into RAM."""
    hasher = hashlib.sha256()
    with open(filepath, 'rb') as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hasher.update(chunk)
    return hasher.hexdigest()

def normalize_pdf(input_path, output_path):
    """Extracts text deterministically, stripping layout and PDF metadata."""
    pdftotext_bin = get_binary_path("pdftotext")
    # -enc UTF-8 : Enforce UTF-8 byte structure
    # -nopgbrk   : Strip page break control characters (form feeds)
    cmd = [pdftotext_bin, "-enc", "UTF-8", "-nopgbrk", input_path, output_path]
    subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def normalize_markdown(input_path, output_path):
    """Strips YAML frontmatter and normalizes markdown to pure text."""
    pandoc_bin = get_binary_path("pandoc")
    # --wrap=none : Prevents arbitrary line wrapping dependent on terminal configuration
    cmd = [pandoc_bin, "-f", "markdown", "-t", "plain", "--wrap=none", input_path, "-o", output_path]
    subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def process_file(input_path, output_dir):
    """Routes the file to the correct normalizer and verifies determinism."""
    if not os.path.exists(input_path):
        raise FileNotFoundError(f"[FATAL] Missing input: {input_path}")
        
    filename = os.path.basename(input_path)
    ext = filename.lower().split('.')[-1]
    
    # 1. Capture Original Source Hash
    source_hash = compute_sha256(input_path)
    
    # 2. Define Output Path (Named by source hash to ensure ID permanence)
    normalized_filename = f"NORM-{source_hash}.txt"
    output_path = os.path.join(output_dir, normalized_filename)
    
    # 3. Route to Normalizer
    if ext == 'pdf':
        normalize_pdf(input_path, output_path)
    elif ext in ['md', 'html', 'txt']:
        normalize_markdown(input_path, output_path)
    else:
        # Fallback for unrecognized raw text: strict byte copy
        shutil.copy2(input_path, output_path)
            
    # 4. Capture Normalized Output Hash
    norm_hash = compute_sha256(output_path)
    
    print(f"[NORMALIZER] Source: {filename} (Hash: {source_hash[:16]}...)")
    print(f"[NORMALIZER] Output: {normalized_filename} (Hash: {norm_hash[:16]}...)")
    
    return output_path, norm_hash

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 normalizer.py <input_file> <output_dir>")
        sys.exit(1)
    
    input_file = sys.argv[1]
    out_directory = sys.argv[2]
    
    os.makedirs(out_directory, exist_ok=True)
    process_file(input_file, out_directory)