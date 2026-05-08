import requests
import json
import time
import hashlib

API_URL = "http://localhost:11434/api/embed"
MODEL = "nomic-embed-text"

FRAME_PATH = "/home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson"
OUT_PATH = "/home/iinkognit0/workspace/archive/little_alpha_storage/semantic.ndjson"

def hash_text(text):
    return hashlib.sha256(text.encode()).hexdigest()

def embed(text):
    r = requests.post(API_URL, json={
        "model": MODEL,
        "input": text
    }, timeout=30)
    r.raise_for_status()
    return r.json()["embeddings"][0]

def process():
    seen = set()

    # bestehende refs laden (keine Duplikate)
    try:
        with open(OUT_PATH, "r") as f:
            for line in f:
                seen.add(json.loads(line)["ref"])
    except:
        pass

    with open(FRAME_PATH, "r") as f:
        for line in f:
            frame = json.loads(line)

            text = json.dumps(frame, sort_keys=True)
            ref = hash_text(text)

            if ref in seen:
                continue

            v = embed(text)

            record = {
                "ref": ref,
                "ts": int(time.time()),
                "dim": len(v),
                "v": v
            }

            with open(OUT_PATH, "a") as out:
                out.write(json.dumps(record) + "\n")

if __name__ == "__main__":
    process()
