**[HANDSHAKE CONFIRMED: CANONICAL MONOLITH INITIATED]**

**[TIMESTAMP SYNC: UNIX 1773704269 | 2026-03-17 00:37:49 CET]**

Systemzeit und Direktive bestätigt. Wir beenden die Ära der fragmentierten Subprozesse.

Dein T520 hat uns gezeigt, dass nicht die SSD oder der Kernel das Limit waren, sondern die Architektur des Skripts. Wenn Linux 75 Mal pro Sekunde einen neuen Python-Prozess aufbauen und wieder abreißen muss (für framer und linker), verbrennt die CPU ihre gesamte Energie im Betriebssystem-Overhead (Kontextwechsel), anstatt Daten zu schreiben.

Um auf 75 Bilder pro Sekunde zu kommen, müssen wir den Runner in einen **In-Memory Monolithen** verwandeln. Anstatt die Module über das Terminal aufzurufen (subprocess), laden wir sie direkt in den laufenden Arbeitsspeicher des Hauptskripts.

### Der V5 "Monolith" Orchestrator

Wir nutzen die native Python-Bibliothek runpy. Sie erlaubt es uns, deine bestehenden Module (framer.py, linker.py etc.) **ohne eine einzige Code-Änderung an den Modulen selbst** direkt im Hauptprozess auszuführen. Das eliminiert 100 % des Subprozess-Overheads.

Ersetze den Code in deiner ingest_runner.py durch diesen Monolithen:

Python

#!/usr/bin/env python3  
"""  
K501 Ingest Orchestrator (V5-Monolith)  
Phase 2: 75 FPS Limit / Zero-Overhead In-Memory Execution  
Deterministic Hash-Chain Integrity  
"""  
  
import os  
import sys  
import json  
import time  
import runpy  
  
# --- CONFIGURATION (ABSOLUTE PATHS) ---  
BASE_DIR = "/home/iinkognit0/k501_ingest_staging"  
INPUT_DIR = os.path.join(BASE_DIR, "input")  
LEDGER_FILE = "/home/iinkognit0/workspace/archive/little_alpha_storage/frames.ndjson"  
WORK_DIRS = {  
"norm": os.path.join(BASE_DIR, "work/1_norm"),  
"chunks": os.path.join(BASE_DIR, "work/2_chunks"),  
"frames": os.path.join(BASE_DIR, "work/3_frames")  
}  
  
# GOVERNOR SETTINGS  
TARGET_FPS = 75  
FRAME_DELAY = 1.0 / TARGET_FPS  
  
def get_ledger_state():  
state = {}  
if not os.path.exists(LEDGER_FILE): return state  
print(f"[K501] Scanning Ledger: {LEDGER_FILE}...")  
with open(LEDGER_FILE, 'r') as f:  
for line in f:  
try:  
data = json.loads(line)  
if data.get("type") == "chunk_frame":  
sid = data["d"]["source_identity"]  
idx = data["d"]["chunk_index"]  
state[sid] = max(state.get(sid, -1), idx)  
except: continue  
return state  
  
def run_module_in_memory(module_name, *args):  
"""  
MONOLITH-CORE: Führt externe Skripte direkt im RAM aus.  
Kein Subprozess, kein Forking, massiv reduzierte CPU-Last.  
"""  
script_path = f"/home/iinkognit0/workspace/k501/runtime/modules/{module_name}.py"  
  
# Sichern der originalen System-Argumente  
original_argv = sys.argv.copy()  
  
try:  
# Simulieren des Terminal-Aufrufs für das Modul  
sys.argv = [script_path] + list(args)  
runpy.run_path(script_path, run_name="__main__")  
finally:  
# Wiederherstellen der Argumente für den nächsten Durchlauf  
sys.argv = original_argv  
  
def orchestrate():  
ledger_state = get_ledger_state()  
  
files_to_process = []  
for root, _, files in os.walk(INPUT_DIR):  
for f in files: files_to_process.append(os.path.join(root, f))  
  
print(f"==================================================")  
print(f"[K501] V5 MONOLITH ENGAGED: {TARGET_FPS} FPS LIMIT")  
print(f"==================================================")  
  
for target_file in files_to_process:  
run_module_in_memory("normalizer", target_file, WORK_DIRS["norm"])  
norm_list = os.listdir(WORK_DIRS["norm"])  
if not norm_list: continue  
  
norm_path = os.path.join(WORK_DIRS["norm"], norm_list[0])  
sid = norm_list[0].replace("NORM-", "").replace(".txt", "")  
last_idx = ledger_state.get(sid, -1)  
  
run_module_in_memory("segmenter", norm_path, WORK_DIRS["chunks"])  
chunk_files = sorted([f for f in os.listdir(WORK_DIRS["chunks"]) if f.endswith(".bin")])  
  
print(f"\n[FILE] ID: {sid[:16]}... | Total Chunks: {len(chunk_files)}")  
if last_idx > -1:  
print(f"[RESUME] Skipping to Chunk > {last_idx}")  
  
for chunk_file in chunk_files:  
idx = int(chunk_file.split("-")[-1].split(".")[0])  
if idx <= last_idx: continue  
  
start_time = time.time()  
  
# Atomic Frame & Link (In-Memory)  
chunk_full_path = os.path.join(WORK_DIRS["chunks"], chunk_file)  
run_module_in_memory("framer", chunk_full_path, WORK_DIRS["frames"])  
  
frame_list = os.listdir(WORK_DIRS["frames"])  
if frame_list:  
frame_path = os.path.join(WORK_DIRS["frames"], frame_list[0])  
run_module_in_memory("linker", frame_path, LEDGER_FILE)  
os.remove(frame_path)  
  
# Governor  
elapsed = time.time() - start_time  
sleep_time = max(0, FRAME_DELAY - elapsed)  
time.sleep(sleep_time)  
  
# Cleanup  
for d in WORK_DIRS.values():  
for f in os.listdir(d): os.remove(os.path.join(d, f))  
  
if __name__ == "__main__":  
try:  
orchestrate()  
except KeyboardInterrupt:  
print("\n[K501] Governor stopped by Operator.")  

### Warum das den Durchbruch bringt

Die Zeile runpy.run_path(...) ist das Herzstück. Dein Skript verhält sich nun wie ein durchgehendes, solides Programm. Der Python-Interpreter muss nicht mehr tausende Male neu gestartet werden. Das bedeutet, die CPU-Last fällt drastisch ab und die **I/O-Verbindung zu deiner SSD kann endlich ihre volle Bandbreite entfalten**.

### Zündungs-Protokoll (V5)

1. **Monitor läuft?** Stelle sicher, dass der Monitor im zweiten Terminal bereit ist. Wir setzen jetzt exakt bei Chunk **58** der abgebrochenen Datei (39145d6c...) auf.
2. **Monolith starten:**  
    Bash  
    python3 ~/workspace/k501/runtime/ingest_runner.py  
    

**Würdest du mir die erste Zeile des Monitors nach dem Start kopieren?** Ich möchte sehen, ob die Velocity (V:) jetzt endlich die **75 FPS** Schallmauer durchbricht!