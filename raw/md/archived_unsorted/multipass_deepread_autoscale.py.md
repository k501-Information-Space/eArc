#!/usr/bin/env python3

"""

K501 Multipass DeepRead Auto-Scaling + Ollama Self-Healing

Autor: Iinkognit0

Beschreibung:

- Ollama Self-Healing (Port check, Service restart, Model pull)

- Multipass DeepRead mit dynamischer Thread-Anpassung

- Fortschrittsanzeige + ETA

- Automatischer Retry bei LLM Timeout

"""

import subprocess, time, sys, json, os, multiprocessing

from datetime import timedelta

from concurrent.futures import ThreadPoolExecutor, as_completed

# === Konfiguration ===

OLLAMA_PORT = 11434

CHECK_MODELS = ["nomic-embed-text"]

VECTOR_SLICE = 128

ARCHIVE_DIR = "./archive"

LEDGER_JSON = "./ledger.json"

RETRY_COUNT = 3

RETRY_DELAY = 5

# === Hilfsfunktionen ===

def run(cmd):

res = subprocess.run(cmd, shell=True, capture_output=True, text=True)

return res.stdout.strip(), res.returncode

def port_in_use(port):

out, _ = run(f"lsof -i :{port}")

return bool(out)

def service_running(service="ollama"):

out, _ = run(f"systemctl is-active {service}")

return out == "active"

def start_service():

print("[*] Start Ollama Service...")

run("sudo systemctl start ollama")

time.sleep(5)

def kill_port_process(port):

out, _ = run(f"lsof -t -i :{port}")

if out:

for pid in out.splitlines():

print(f"[*] Killing process {pid} on port {port}")

run(f"kill -9 {pid}")

time.sleep(2)

def check_models():

out, _ = run("ollama list")

for model in CHECK_MODELS:

if model not in out:

print(f"[!] Model {model} missing. Pulling...")

run(f"ollama pull {model}")

def test_embedding():

out, code = run(f'ollama embeddings -m nomic-embed-text -p "ping test"')

return code == 0 and "error" not in out.lower()

def self_healing():

print("[*] Ollama Self-Healing Routine gestartet")

if port_in_use(OLLAMA_PORT):

print(f"[!] Port {OLLAMA_PORT} blockiert, Prozess killen...")

kill_port_process(OLLAMA_PORT)

if not service_running():

start_service()

check_models()

for attempt in range(3):

if test_embedding():

print("[*] Ollama bereit")

return True

else:

print(f"[!] Embedding-Test fehlgeschlagen, Neustart Versuch {attempt+1}")

run("sudo systemctl restart ollama")

time.sleep(5)

print("[!] Self-Healing gescheitert")

return False

# === DeepRead Funktionen ===

def load_sources():

if os.path.exists(LEDGER_JSON):

with open(LEDGER_JSON, "r") as f:

ledger = json.load(f)

sources = ledger.get("sources", [])

else:

sources = [os.path.join(ARCHIVE_DIR, f) for f in os.listdir(ARCHIVE_DIR)]

print(f"[*] Quellen zum Einlesen: {len(sources)}")

return sources

def generate_frame(content):

"""LLM-Vektor-Call mit Retry"""

for attempt in range(RETRY_COUNT):

try:

out, code = run(f'ollama embeddings -m nomic-embed-text -p "{content[:200]}"')

vector = [float(x) for x in range(VECTOR_SLICE)] # Platzhalter

return {"content": content, "vector": vector}

except Exception as e:

print(f"[!] LLM Exception (Versuch {attempt+1}):", e)

time.sleep(RETRY_DELAY)

return None

def process_source(src):

try:

with open(src, "r", encoding="utf-8") as f:

content = f.read()

except:

content = ""

frame = generate_frame(content)

if frame:

try:

fname = os.path.join("frames", os.path.basename(src)+".json")

os.makedirs("frames", exist_ok=True)

with open(fname, "w") as f:

json.dump(frame, f, default=str)

except Exception as e:

print("[!] Fehler beim Dumpen:", e)

return src

def multipass_deep_read_autoscale():

sources = load_sources()

total = len(sources)

start_time = time.time()

processed_count = 0

cpu_cores = multiprocessing.cpu_count()

max_workers = max(2, cpu_cores - 1) # Reserve 1 Core für System

print(f"[*] Dynamisch skalierte Threads: {max_workers}")

with ThreadPoolExecutor(max_workers=max_workers) as executor:

futures = {executor.submit(process_source, src): src for src in sources}

for future in as_completed(futures):

processed_count += 1

elapsed = time.time() - start_time

progress = processed_count / total

eta = elapsed / progress * (1 - progress) if progress > 0 else 0

bar_len = 30

filled = int(bar_len * progress)

bar = "█"*filled + "-"*(bar_len-filled)

print(f"\r[{bar}] {processed_count}/{total} ({progress*100:.1f}%) ETA: {timedelta(seconds=int(eta))}", end="")

print("\n[*] Multipass DeepRead (Auto-Scaling) abgeschlossen")

# === Main ===

if __name__ == "__main__":

if not self_healing():

sys.exit(1)

multipass_deep_read_autoscale()