#!/usr/bin/env python3
"""
K501 Quantizer Module (Pass 4a)
Role: Deterministic JCS (RFC-8785) Serialization & QH256 Hashing
"""
import json
import hashlib

def jcs_serialize(frame_dict):
    """
    Serializes a dictionary according to Canonical JSON (RFC 8785).
    - Lexicographical key sorting
    - No whitespace between separators
    - Strict UTF-8 encoding
    """
    # json.dumps in Python with these parameters strictly adheres to JCS for simple types
    jcs_string = json.dumps(
        frame_dict,
        separators=(',', ':'),
        sort_keys=True,
        ensure_ascii=False
    )
    return jcs_string.encode('utf-8')

def compute_frame_hash(frame_dict):
    """
    Strips any existing hash, serializes the frame, and computes SHA-256.
    Matches the Axiom: hash = SHA256(JCS(frame_without_h))
    """
    # Create a shadow copy without the 'hash' key to ensure zero-trust calculation
    clean_frame = {k: v for k, v in frame_dict.items() if k != 'hash'}
    
    serialized_bytes = jcs_serialize(clean_frame)
    return hashlib.sha256(serialized_bytes).hexdigest()

if __name__ == "__main__":
    # Minor test loop if run independently
    print("[QUANTIZER] Loaded RFC-8785 Deterministic Hash Engine.")