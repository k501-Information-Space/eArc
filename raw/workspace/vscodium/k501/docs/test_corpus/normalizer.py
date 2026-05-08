#!/usr/bin/env python3
"""
K501 Normalizer Module (Pass 1)
Role: Deterministic Metadata Stripping & Format Unification
      Now includes Sovereign FFmpeg integration for Video/Audio.
"""
import os
import subprocess
import hashlib
import sys
import shutil

# 1. Strict Path Execution (Binding to the Sovereign Toolchain)
ST_ROOT_BIN = "/opt/k501/st_root/bin"

def get_binary_path(binary_name):
    st_path = os.path.join(ST_ROOT_BIN, binary_name)
    if os.path.exists(st_path):
        return st_path
    sys_path = shutil.which(binary_name)
    if not sys_path:
        raise FileNotFoundError(f"[FATAL] Sovereign Toolchain binary missing: {binary_name}")
    return sys_path

def compute_sha256(filepath):
    """Computes a deterministic hash of a file."""
    hasher = hashlib.sha256()
    with open(filepath, 'rb') as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hasher.update(chunk)
    return hasher.hexdigest()

def normalize_media(input_path, output_path):
    """
    Uses Sovereign FFmpeg to strip all metadata from AV containers.
    -bitexact: Forces the encoder to use bit-exact algorithms.
    -map_metadata -1: Strips all global metadata.
    """
    ffmpeg_bin = get_binary_path("ffmpeg")
    # We use a neutral .mkv or .mp4 container but force bitexact output
    cmd = [
        ffmpeg_bin, "-i", input_path,
        "-map_metadata", "-1",
        "-fflags", "+bitexact",
        "-flags:v", "+bitexact",
        "-flags:a", "+bitexact",
        "-c", "copy", # Copy streams to avoid generational loss, just strip container junk
        output_path, "-y"
    ]
    subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def normalize_pdf(input_path, output_path):
    pdftotext_bin = get_binary_path("pdftotext")
    cmd = [pdftotext_bin, "-enc", "UTF-8", "-nopgbrk", input_path, output_path]
    subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def normalize_markdown(input_path, output_path):
    pandoc_bin = get_binary_path("pandoc")
    cmd = [pandoc_bin, "-f", "markdown", "-t", "plain", "--wrap=none", input_path, "-o", output_path]
    subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def process_file(input_path, output_dir):
    if not os.path.exists(input_path):
        raise FileNotFoundError(f"[FATAL] Missing input: {input_path}")
        
    filename = os.path.basename(input_path)
    ext = filename.lower().split('.')[-1]
    source_hash = compute_sha256(input_path)
    
    normalized_filename = f"NORM-{source_hash}.txt"
    output_path = os.path.join(output_dir, normalized_filename)
    
    # Routing Logic
    if ext == 'pdf':
        normalize_pdf(input_path, output_path)
    elif ext in ['md', 'html', 'txt']:
        normalize_markdown(input_path, output_path)
    elif ext in ['mp4', 'mkv', 'avi', 'mp3', 'wav', 'ogg']:
        # Media files retain their binary nature but stripped of metadata
        output_path = os.path.join(output_dir, f"NORM-{source_hash}.media")
        normalize_media(input_path, output_path)
    else:
        shutil.copy2(input_path, output_path)
            
    norm_hash = compute_sha256(output_path)
    print(f"[NORMALIZER] Source: {filename} (Hash: {source_hash[:16]}...)")
    print(f"[NORMALIZER] Output: {os.path.basename(output_path)} (Hash: {norm_hash[:16]}...)")
    return output_path, norm_hash

if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(1)
    process_file(sys.argv[1], sys.argv[2])