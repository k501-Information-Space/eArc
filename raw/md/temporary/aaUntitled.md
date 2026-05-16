#!/usr/bin/env python3
"""
Essay → FrameCode (IAL) Compiler v0.1 (MINIMAL)

- Read-first
- Deterministisch (hash-based IDs)
- Keine Interpretation im Kernel-Sinn
- Heuristik bewusst simpel

Usage:
  python3 essay_to_framecode.py < essay.txt
  python3 essay_to_framecode.py essay.md
"""

import sys
import hashlib
import datetime
import re

UTC = datetime.datetime.utcnow().replace(microsecond=0).isoformat() + "Z"

def sha_id(s, prefix):
    h = hashlib.sha256(s.encode("utf-8")).hexdigest()[:24]
    return f"{prefix}_{h}"

def read_input():
    if len(sys.argv) > 1:
        with open(sys.argv[1], "r", encoding="utf-8") as f:
            return f.read()
    return sys.stdin.read()

def normalize(text):
    return "\n".join(line.rstrip() for line in text.strip().splitlines())

def extract_sentences(text):
    # sehr einfache Satztrennung
    parts = re.split(r'(?<=[.!?])\s+', text)
    return [p.strip() for p in parts if len(p.strip()) > 0]

def is_claim(sentence):
    triggers = ["ist", "sind", "bedeutet", "heißt", "führt", "entsteht"]
    return any(t in sentence.lower() for t in triggers)

def is_concept(sentence):
    return " ist " in sentence.lower()

def main():
    raw = read_input()
    text = normalize(raw)

    essay_id = sha_id(text[:256], "essay")

    print(f"# IAL FrameCode v0.1")
    print(f"# essay_id: {essay_id}")
    print(f"# generated_utc: {UTC}")
    print()

    sentences = extract_sentences(text)

    claims = []
    concepts = []

    for i, s in enumerate(sentences):
        sid = sha_id(f"{essay_id}|s{i}|{s}", "seg")

        if is_claim(s):
            cid = sha_id(f"CLM|{essay_id}|{s}", "clm")
            claims.append(cid)
            print(f"CLM {cid} {UTC} essay={essay_id} | {s}")

        if is_concept(s):
            term = s.split(" ist ")[0].strip().lower().replace(" ", "_")[:32]
            cpid = sha_id(f"CNPT|{essay_id}|{term}", "cnpt")
            concepts.append(cpid)
            print(f"CNPT {cpid} {UTC} essay={essay_id} term={term} | {s}")

    # minimale Relation: alle Claims hängen am ersten Concept (falls vorhanden)
    if concepts:
        base = concepts[0]
        for cid in claims:
            rid = sha_id(f"REL|{cid}|{base}", "rel")
            print(f"REL {rid} {UTC} essay={essay_id} from={cid} to={base} rel=depends_on")

if __name__ == "__main__":
    main()