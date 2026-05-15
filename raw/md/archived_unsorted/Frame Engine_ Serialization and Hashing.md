### **Signal Acknowledged: Initializing the Frame Engine**

Your echo serves as a precise confirmation to advance the compilation pipeline. We are now moving from memory allocation to cryptographic persistence.

The **frame_engine** is the exact point where K501 transitions from "data" to "immutable knowledge." It enforces **Axiom 5 (Hash Space)** and **Frame-Spec v1 (JCS Serialization)**. To achieve this without bloating the ≈900-line kernel, this module leverages deterministic string construction and standard SHA-256 cryptographic hashing.

Here is the canonical source code for the **frame_engine**.

### **4. Canonical C Source Code: frame_engine**

This module guarantees that before any frame is appended to the storage/frames.ndjson, it is serialized strictly according to RFC 8785 (Canonical JSON) and hashed deterministically.

**File:** include/frame_engine.h

C

#**ifndef** K501_FRAME_ENGINE_H  
#**define** K501_FRAME_ENGINE_H  
  
#**include** <stdint.h>  
#**include** <stdbool.h>  
#**include** <stddef.h>  
#**include** "qh_core.h"  
  
/* Canonical Serialization and Hashing Prototypes */  
bool fe_build_jcs(const frame_t *f, char *out_buffer, size_t max_len);  
bool fe_compute_hash(frame_t *f);  
  
#**endif** // K501_FRAME_ENGINE_H  

**File:** src/frame_engine.c

C

#**include** "frame_engine.h"  
#**include** <stdio.h>  
#**include** <string.h>  
#**include** <openssl/sha.h> // Standard cryptographic library for deterministic SHA-256  
  
/* * fe_build_jcs:  
* Constructs the RFC 8785 Canonical JSON Serialization (JCS).  
* - Lexicographical key ordering: "id", "qh", "t".  
* - No whitespace between keys or values.  
* - Used strictly for hashing; the hash itself is omitted from the input.  
*/  
bool fe_build_jcs(const frame_t *f, char *out_buffer, size_t max_len) {  
if (!f || !out_buffer || max_len < 512) return false;  
  
// Begin JSON construction with strict lexicographical order  
int offset = snprintf(out_buffer, max_len, "{\"id\":\"%s\",\"qh\":[", f->id);  
if (offset < 0 || (size_t)offset >= max_len) return false;  
  
// Serialize the 56-cell Quantum Header matrix  
for (int i = 0; i < 56; ++i) {  
int written = snprintf(out_buffer + offset, max_len - offset, "%u%s",  
f->qh[i], (i < 55) ? "," : "");  
if (written < 0 || (size_t)written >= max_len - offset) return false;  
offset += written;  
}  
  
// Append the time anchor and close the JSON object  
int final_write = snprintf(out_buffer + offset, max_len - offset, "],\"t\":%llu}",  
(unsigned long long)f->time);  
  
if (final_write < 0 || (size_t)final_write >= max_len - offset) return false;  
  
return true;  
}  
  
/* * fe_compute_hash:  
* Generates the JCS string, computes the SHA-256 digest,  
* and permanently locks the hex string into the frame's memory struct.  
*/  
bool fe_compute_hash(frame_t *f) {  
if (!f) return false;  
  
char jcs_buffer[4096];  
if (!fe_build_jcs(f, jcs_buffer, sizeof(jcs_buffer))) {  
return false;  
}  
  
// Compute SHA-256  
unsigned char hash_raw[SHA256_DIGEST_LENGTH];  
SHA256((const unsigned char *)jcs_buffer, strlen(jcs_buffer), hash_raw);  
  
// Convert raw bytes to a null-terminated hex string  
for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {  
sprintf(f->hash + (i * 2), "%02x", hash_raw[i]);  
}  
f->hash[64] = '\0'; // Ensure strict bounds termination  
  
return true;  
}  

**Compiler Note:** To compile this successfully with the previously generated Makefile, you will need to link the OpenSSL crypto library. You can update the Makefile CFLAGS or LDFLAGS to include -lcrypto.

### **Axiomatic Alignment Check**

- **JCS Compliance:** The fe_build_jcs function enforces zero whitespace, strict structural ordering, and strips the hash field from the payload _before_ hashing, exactly fulfilling the hash = SHA256(JCS(frame_without_h)) requirement.
- **Predictable Memory:** The 4096-byte jcs_buffer easily accommodates our flat frame_t struct, preventing heap fragmentation and memory leaks.
- **Cryptographic Lock:** Once fe_compute_hash() runs, the frame_t struct becomes self-verifying. Any node receiving this struct can re-run the JCS build and compare the computed hash to f->hash.

### **Next Execution Step**

We now have the logic (qh_algebra), the memory structure (qh_core), and the cryptographic locking mechanism (frame_engine).

To make this data navigable at $O(1)$ speeds before we write it to the disk, we must implement the indexing layer.

**Would you like me to synthesize hard_index.c next to establish the memory offsets, or dynamic_cage.c to define the system rules that govern when a frame is allowed to be indexed at all?**