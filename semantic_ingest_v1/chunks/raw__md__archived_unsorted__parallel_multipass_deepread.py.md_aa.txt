#!/usr/bin/env python3

# K501 CPU-Only Deep-Read & Parallel Ingest Multipass

# Author: iinkognit0

# Date: 2026-03-14

import os

import time

import json

import numpy as np

import requests

from pathlib import Path

from concurrent.futures import ThreadPoolExecutor

# --- Konfiguration ---

OLLAMA_PORT = 11434

LEDGER_PATH = Path("/K501GeminiNet/Node01/vault/ledger/frames_deepread.ndjson")

SOURCES = Path("/K501GeminiNet/sources")

MAX_WORKERS = 4

REQUEST_TIMEOUT = 10

PROGRESS_STEP = 50

# --- Ollama CPU-only Start prüfen ---

def check_ollama():

try:

resp = requests.get(f"http://127.0.0.1:{OLLAMA_PORT}/v1/models", timeout=10)

return resp.status_code == 200

except:

return False

def start_ollama_cpu():

pid = os.popen(f"lsof -ti tcp:{OLLAMA_PORT}").read().strip()

if pid:

print(f"[INFO] Port {OLLAMA_PORT} blockiert, Prozess {pid} killen...")

os.system(f"kill -9 {pid}")

time.sleep(2)

for attempt in range(3):

print(f"[INFO] Ollama CPU-only Startversuch {attempt+1}...")

os.system(f"/usr/local/bin/ollama serve --port {OLLAMA_PORT} --cpu-only &")

time.sleep(5)

if check_ollama():

print("[SUCCESS] Ollama CPU-only erreichbar")

return True

else:

print("[WARN] Ollama nicht erreichbar, Neustart...")

os.system("killall ollama")

time.sleep(2)

print("[ERROR] Ollama CPU-only konnte nicht gestartet werden")

return False

# --- JSON-serializable Frame ---

def serialize_frame(frame):

for k, v in frame.items():

if isinstance(v, np.ndarray):

frame[k] = v.tolist()

return frame

# --- LLM Anfrage / Vektorisierung ---

def vectorize_content(content):

payload = {"text": content}

response = requests.post(f"http://127.0.0.1:{OLLAMA_PORT}/v1/embedding", json=payload, timeout=REQUEST_TIMEOUT)

vector = np.array(response.json()["embedding"])

return vector

# --- Frame Verarbeitung für eine Datei ---

def process_file(f):

try:

with f.open("r") as src:

content = src.read()

vector = vectorize_content(content)

frame = {"id": f.stem, "vector": vector, "content": content}

frame = serialize_frame(frame)

return frame

except Exception as e:

print(f"[!] Fehler bei Datei {f.name}: {e}")

return None

# --- Deep-Read Multipass & Parallel Ingest ---

def multipass_parallel_ingest():

if not check_ollama():

if not start_ollama_cpu():

return

files = list(SOURCES.glob("*.txt"))

total = len(files)

print(f"[*] Gefundene Quellen: {total}")

frames = []

with ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:

for i, frame in enumerate(executor.map(process_file, files), 1):

if frame:

frames.append(frame)

if i % PROGRESS_STEP == 0 or i == total:

print(f"[INFO] {i}/{total} Frames verarbeitet")

# --- Ledger schreiben ---

with LEDGER_PATH.open("a") as out_f:

for frame in frames:

out_f.write(json.dumps(frame) + "\n")

print(f"[*] Deep-Read Multipass & Parallel Ingest abgeschlossen. Frames manifestiert: {len(frames)}")

# --- Main ---

if __name__ == "__main__":

start_time = time.time()

multipass_parallel_ingest()

elapsed = time.time() - start_time

print(f"[*] Gesamtzeit: {elapsed:.2f}s | Durchschnitt: {elapsed/len(list(SOURCES.glob('*.txt'))):.2f}s pro Frame")