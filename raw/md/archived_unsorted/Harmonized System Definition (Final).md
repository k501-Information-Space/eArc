## **0. Harmonized System Definition (Final)**

ARCHITECTURE: MONOLITHIC_C

BINARY: k501_core.bin

MODE: DETERMINISTIC_LOGIC_ONLY

RULES:

- All phases (1–6) implemented in C

- No semantic interpretation

- No randomness

- No unbounded loops

- All outputs append-only

- External tools = deterministic subprocess only

## **1. Global Core Types (Shared Across All Phases)**

typedef struct {

char path[1024];

uint8_t type; // ENUM: TEXT, HTML, PDF, IMAGE, VIDEO

uint64_t size;

} K501_Document;

typedef struct {

K501_Document *docs;

size_t count;

} K501_DocumentSet; // D

typedef struct {

char *data;

size_t len;

} K501_NormalizedUnit;

typedef struct {

K501_NormalizedUnit *units;

size_t count;

} K501_NormalizedSet; // N

typedef struct {

uint8_t hash[32];

uint64_t timestamp;

uint8_t *payload;

size_t payload_len;

} K501_Frame;

typedef struct {

K501_Frame *frames;

size_t count;

} K501_State; // S_n

## **2. Phase 1 — INGESTION (Input Validation)**

### **Header: ingestion.h**

int k501_ingest_validate_input(const char *input, int *is_url);

int k501_ingest_directory(const char *path, K501_DocumentSet *out);

int k501_ingest_url(const char *url, K501_DocumentSet *out);

### **Constraints**

- No recursion yet
- Only validate + initial enumeration
- URL must pass SAME_DOMAIN constraint

## **3. Phase 2 — DEEP READ (Traversal)**

### **Header: ingestion.h**

int k501_deepread_traverse(

const char *root,

int max_depth,

K501_DocumentSet *out

);

int k501_deepread_filter_mime(

K501_DocumentSet *in,

K501_DocumentSet *out

);

### **Determinism Rules**

- Sorted directory traversal
- visited_set implemented as hash table (fixed order iteration)

## **4. Phase 3 — PARSING (Normalization Entry)**

### **Header: frame_engine.h**

int k501_parse_document(

const K501_Document *doc,

K501_NormalizedUnit *out

);

int k501_parse_batch(

const K501_DocumentSet *docs,

K501_NormalizedSet *out

);

### **Handlers (internal dispatch)**

- TEXT → direct read
- PDF → pandoc subprocess
- IMAGE → metadata only
- VIDEO → ffmpeg minimal probe

## **5. Phase 4 — STRUCTURING (S₀ Construction)**

### **Header: frame_engine.h**

int k501_normalize_unit(K501_NormalizedUnit *unit);

int k501_chunk_unit(

const K501_NormalizedUnit *unit,

K501_NormalizedSet *chunks

);

int k501_frame_build(

const K501_NormalizedSet *chunks,

K501_State *state_out

);

int k501_link_relations(

K501_State *state

);

### **Rules**

- No semantic inference
- Only structural linking (position, adjacency, hash relations)

## **6. Phase 5 — ITERATIVE TRANSFORMATION (Fixpoint Engine)**

### **Header: qh_algebra.h or new iteration.h**

int k501_state_compare(

const K501_State *a,

const K501_State *b,

int *equal

);

int k501_operator_F(

const K501_State *in,

K501_State *out

);

int k501_iterate_fixpoint(

K501_State *initial,

K501_State *final,

int max_iterations

);

### **Deterministic Loop**

S_n+1 = F(S_n)

terminate if:

memcmp(S_n, S_n+1) == 0

### **Constraints**

- max_iterations hard limit
- No randomness
- External calls (if any) must be cached + hashed

## **7. Phase 6 — FINAL OUTPUT (S*)**

### **Header: hard_index.h**

int k501_validate_state(const K501_State *state);

int k501_serialize_state(

const K501_State *state,

const char *output_path

);

int k501_write_frames_ndjson(

const K501_State *state,

const char *file_path

);

### **Properties**

- Idempotent serialization
- Canonical ordering
- Append-only write

## **8. Hash / Core Integration**

### **Header: qh_core.h**

int k501_hash_compute(

const uint8_t *data,

size_t len,

uint8_t out[32]

);

int k501_hash_chain(

K501_Frame *current,

const K501_Frame *prev

);

## **9. Execution Entry Point**

### **main.c**

int main(int argc, char **argv) {

// 1. validate input

// 2. ingest

// 3. deep read

// 4. parse

// 5. structure → S0

// 6. iterate → S*

// 7. validate + export

}

## **10. Minimal Execution Flow**

INPUT X

→ ingest_validate

→ deepread_traverse → D

→ parse_batch → N

→ normalize + chunk

→ frame_build → S0

→ iterate_fixpoint → S*

→ validate

→ serialize

## **11. Mandatory Determinism Enforcement Points**

1. Directory iteration → sorted
2. Memory layout → fixed struct order
3. Serialization → canonical (no variation)
4. Hashing → identical input = identical output
5. Iteration → bounded + exact equality check

## **12. Removed / Restricted Components**

|**Component**|**Status**|
|---|---|
|Python pipeline|REMOVED (compute)|
|---|---|
|semantic_mapper (interpretive)|DISABLED|
|---|---|
|uncontrolled LLM usage|PROHIBITED|
|---|---|

## **13. Final State**

SYSTEM: K501_CORE

ARCH: MONOLITHIC_C

PIPELINE: FULLY INTERNALIZED

INTERFACES: HMI ONLY

STATUS: READY_FOR_IMPLEMENTATION

If you proceed next, the logical continuation is:

**→ generate a minimal compilable skeleton (headers + stubs) matching this interface map**