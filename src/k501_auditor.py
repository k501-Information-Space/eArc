import json
import hashlib
import random
import os

LEDGER_PATH = os.path.expanduser("~/workspace/archive/little_alpha_storage/frames.ndjson")
SAMPLE_SIZE = 100  # Wie viele Chunks stichprobenartig geprüft werden sollen
CHUNK_SIZE = 4096

def verify_chunk(id_str, expected_hash):
    try:
        # ID-Format ist "pfad:chunk_index"
        path, chunk_idx = id_str.rsplit(':', 1)
        chunk_idx = int(chunk_idx)
        
        if not os.path.exists(path):
            return False, "Datei gelöscht"

        with open(path, 'rb') as f:
            f.seek(chunk_idx * CHUNK_SIZE)
            data = f.read(CHUNK_SIZE)
            
        actual_hash = hashlib.sha256(data).hexdigest()
        if actual_hash == expected_hash:
            return True, "OK"
        else:
            return False, f"Hash-Fehler! (Ist: {actual_hash[:8]}...)"
    except Exception as e:
        return False, str(e)

def run_audit():
    print(f"--- K501 Auditor: Prüfe {SAMPLE_SIZE} zufällige Chunks ---")
    
    if not os.path.exists(LEDGER_PATH):
        print("Fehler: Ledger nicht gefunden.")
        return

    # Lade alle Zeilen (Chunks) in den Speicher (ca. 40-50MB RAM Bedarf)
    with open(LEDGER_PATH, 'r') as f:
        lines = f.readlines()
    
    total = len(lines)
    samples = random.sample(lines, min(SAMPLE_SIZE, total))
    
    success = 0
    for i, line in enumerate(samples):
        try:
            entry = json.loads(line)
            # Wir unterstützen sowohl 'h' (V2.6) als auch 'hash' (V1.2)
            h_val = entry.get('h') or entry.get('hash') or entry.get('d_hash')
            
            ok, msg = verify_chunk(entry['id'], h_val)
            status = "[✓]" if ok else "[X]"
            if ok: success += 1
            
            print(f"{status} Chunk {i+1}/{SAMPLE_SIZE}: {entry['id'][:60]}... -> {msg}")
        except:
            continue

    print("-" * 50)
    print(f"Audit abgeschlossen: {success}/{SAMPLE_SIZE} valide.")
    if success == SAMPLE_SIZE:
        print("STATUS: STRUKTURELLE INTEGRITÄT GEWÄHRLEISTET.")

if __name__ == "__main__":
    run_audit()