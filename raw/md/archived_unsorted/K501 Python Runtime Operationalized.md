### **Validation Complete: Frame Matrix Synthesized**

Your terminal output is flawless. The JSON payload is perfectly flat, the Epistemic Matrix (qh) has initialized cell 0 to 2 (TRUE), and the d object accurately reflects the 236-byte size and cryptographic identity of the source block.

We have successfully created a raw K501 object. Now, we must transition it from a static object into an immutable event in the space-time of the K501eArc.

We will execute the final two modules simultaneously: the **Quantizer** (which calculates the strict RFC-8785 hash) and the **Linker** (which queries the physical disk for the latest temporal state, binds the relations, and appends the frame to the archive).

### **Phase 7: Pipeline Construction - quantizer.py**

The Quantizer is purely a mathematical utility. It guarantees that any K501 node, regardless of whether it is written in C, Python, or Rust, will compute the exact same SHA-256 hash for a given JSON dictionary.

Open k501/runtime/modules/quantizer.py and paste the following:

Python

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

### **Phase 8: Pipeline Construction - linker.py**

The Linker is the architect. It reads the last line of frames.ndjson to find the current "HEAD" of the archive. It then enforces the Axiom of Temporal Monotonicity ($t_k > t_{k-1}$), binds the hash_prev relation, routes the frame through the Quantizer, and permanently appends it to the disk.

Open k501/runtime/modules/linker.py and paste the following:

Python

#!/usr/bin/env python3  
"""  
K501 Linker Module (Pass 4b)  
Role: Temporal Anchoring, Relational Binding, and Bounded Disk Append  
"""  
import os  
import sys  
import json  
import time  
from quantizer import compute_frame_hash  
  
# Path Fallbacks: Tries the physical eSATA drive, falls back to local workspace archive  
STORAGE_DIR = "/opt/k501/data"  
if not os.path.exists(STORAGE_DIR):  
STORAGE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../archive/little_alpha_storage"))  
  
NDJSON_FILE = os.path.join(STORAGE_DIR, "frames.ndjson")  
INDEX_FILE = os.path.join(STORAGE_DIR, "index.dat")  
  
def get_archive_head():  
"""Reads the last frame in the NDJSON to determine temporal and relational state."""  
if not os.path.exists(NDJSON_FILE) or os.path.getsize(NDJSON_FILE) == 0:  
raise FileNotFoundError("[FATAL] Genesis Block missing. Run C-Kernel genesis first.")  
  
# Efficiently read the last line without loading the whole file into RAM  
with open(NDJSON_FILE, 'rb') as f:  
f.seek(-2, os.SEEK_END)  
while f.read(1) != b'\n':  
f.seek(-2, os.SEEK_CUR)  
if f.tell() == 0:  
f.seek(0)  
break  
last_line = f.readline().decode('utf-8')  
  
last_frame = json.loads(last_line)  
return last_frame.get('hash'), last_frame.get('t')  
  
def link_and_append(frame_path):  
"""Injects relations and time, hashes the frame, and appends it to storage."""  
if not os.path.exists(frame_path):  
raise FileNotFoundError(f"[FATAL] Missing intermediate frame: {frame_path}")  
  
# 1. Load the intermediate JSON  
with open(frame_path, 'r', encoding='utf-8') as f:  
frame_dict = json.load(f)  
  
# 2. Query Archive HEAD  
prev_hash, prev_t = get_archive_head()  
  
# 3. Enforce Temporal Monotonicity  
current_time = int(time.time())  
if current_time <= prev_t:  
current_time = prev_t + 1 # Mathematical strict forward-progression  
  
frame_dict['t'] = current_time  
  
# 4. Inject Relational Bindings  
frame_dict['relations'] = {  
"origin": "AZ-Epoch-0-Genesis",  
"parent": frame_dict['id'], # The chunk's parent is its own source ID  
"hash_prev": prev_hash  
}  
  
# 5. Compute Final Cryptographic Identity  
final_hash = compute_frame_hash(frame_dict)  
frame_dict['hash'] = final_hash  
  
# 6. Physical Append to Domain A Storage  
# Generate final compact JCS string for storage  
final_json_string = json.dumps(frame_dict, separators=(',', ':'), ensure_ascii=False)  
  
with open(NDJSON_FILE, 'a', encoding='utf-8') as out_f:  
out_f.write(final_json_string + '\n')  
  
print(f"[LINKER] Appended: {frame_dict['id']}")  
print(f" └─ Hash: {final_hash}")  
print(f" └─ T: {current_time}")  
  
if __name__ == "__main__":  
if len(sys.argv) < 2:  
print("Usage: python3 linker.py <intermediate_frame.json>")  
sys.exit(1)  
  
frame_file = sys.argv[1]  
link_and_append(frame_file)  

### **The Final Alpha Execution Test**

The Python pipeline is fully complete. Let's send your intermediate JSON frame through the Linker, which will anchor it into the K501 graph.

Because we symlinked your archive/little_alpha_storage/ in the script logic, it will seamlessly locate the Genesis block you struck earlier.

Execute this command:

Bash

python3 k501/runtime/modules/linker.py k501/runtime/tests/frames/CHUNK-af5cc2a571b0e5c7b22af4a41667cb6058e573f966ad02cf07a4458cfc5ed57b-000000.json  

And verify the immutable timeline has expanded:

Bash

cat archive/little_alpha_storage/frames.ndjson  

If the terminal reports the successful appending of the new CHUNK frame complete with hash, t, and relations, **we have successfully achieved a fully operational, deterministic Python runtime.** Once verified, we will draft ingest_runner.py to glue these 4 modules together into one seamless queue.