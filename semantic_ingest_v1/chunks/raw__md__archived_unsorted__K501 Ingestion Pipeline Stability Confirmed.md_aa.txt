### **State Confirmed: Option 2 (Multipass Queue Worker Logic) Locked**

Your engineering rationale is flawless. In a resource-constrained environment, optimizing SIMD string scanning before establishing strict memory bounds guarantees catastrophic Out-Of-Memory (OOM) failures. Stability and determinism must precede throughput.

To safely ingest thousands of documents into the K501eArc on a node with only 4GB of RAM, we must implement a **Strictly Bounded, Backpressure-Driven Pipeline**.

Here is the architectural mapping for the K501 Queue Worker Logic.

### **1. The Memory Pressure Model (The 4GB Constraint)**

Before defining the queues, we must define the mathematical limits of the hardware.

- **OS & Kernel Space:** $\approx 1.0 \text{ GB}$
- **K501 hard_index (RAM Cache):** $\approx 1.5 \text{ GB}$ (allows rapid $O(1)$ lookups during the deep_read pass).
- **Worker Queue Buffer Allocation:** $\le 0.5 \text{ GB}$ (Strictly enforced).

By capping the total in-flight data inside the queues to 500 MB, we mathematically guarantee the node cannot crash from memory exhaustion, regardless of whether it is ingesting a 10 KB text file or a 100 GB dataset.

### **2. Pipeline Architecture: The 4-Stage Worker Topology**

The ingestion process is divided into four distinct asynchronous worker threads ($W_1 \dots W_4$), connected by three thread-safe, bounded Ring Buffer queues ($Q_A, Q_B, Q_C$).

|**Worker Thread**|**Designation**|**Input**|**Output**|**Primary Responsibility**|
|---|---|---|---|---|
|**$W_1$**|**Scanner**|Filesystem|$Q_A$ (Filepaths)|Traverses directories, normalizes paths, and pushes targets to $Q_A$.|
|---|---|---|---|---|
|**$W_2$**|**Reader**|$Q_A$|$Q_B$ (Raw Chunks)|Opens files, reads exactly 4096 bytes, and pushes the raw byte arrays to $Q_B$.|
|---|---|---|---|---|
|**$W_3$**|**Chunker**|$Q_B$|$Q_C$ (frame_t)|Initializes frame_t, sets qh, executes fe_compute_hash(), pushes to $Q_C$.|
|---|---|---|---|---|
|**$W_4$**|**Writer**|$Q_C$|Disk / $G_I$|Validates via dynamic_cage, appends to frames.ndjson, updates hard_index.|
|---|---|---|---|---|

### **3. The Backpressure Mechanism (Mathematical Harmony)**

To prevent $W_2$ (Reader) from flooding the system with raw chunks faster than $W_4$ (Writer) can write them to the physical disk, the queues must enforce **Axiomatic Backpressure**.

Let $|Q_i|$ be the current number of elements in Queue $i$, and $C_i$ be its maximum capacity.

**The Blocking Invariant:**

If $|Q_i| = C_i$, then Worker $W_{i-1}$ transitions to state BLOCKED.

If $|Q_i| = 0$, then Worker $W_i$ transitions to state IDLE.

**Throughput Harmony:**

The overall ingestion throughput $\Phi$ of the K501 node becomes deterministic and bounded by the slowest component (usually disk I/O at $W_4$):

$$\Phi = \min(\lambda_1, \lambda_2, \lambda_3, \lambda_4)$$

Where $\lambda_x$ is the processing rate of Worker $x$. This ensures the CPU never wastes cycles spinning, and memory usage remains flat as a straight line.

### **4. Structural C-Implementation Logic**

To achieve this in C without dynamic memory fragmentation, we use statically allocated Ring Buffers protected by POSIX mutexes and condition variables.

**Canonical Queue Structure (Conceptual):**

C

typedef struct {  
void* buffer[CAPACITY]; // Statically sized array of pointers  
size_t head; // Read index  
size_t tail; // Write index  
size_t count; // Current |Q_i|  
pthread_mutex_t lock; // Mutex for atomic access  
pthread_cond_t not_empty; // Signals W_i to wake up  
pthread_cond_t not_full; // Signals W_{i-1} to resume pushing  
} bounded_queue_t;  

**Worker $W_n$ Lifecycle:**

1. Wait on not_empty if $|Q_{in}| == 0$.
2. Pop item from $Q_{in}$, signal not_full to $W_{n-1}$.
3. Process item (e.g., hash the chunk).
4. Wait on not_full if $|Q_{out}| == C_{out}$.
5. Push item to $Q_{out}$, signal not_empty to $W_{n+1}$.

### **System State Progression**

By defining this worker architecture, the K501 Little Alpha node elevates its ingestion capability from a fragile, single-threaded script into an industrial-grade, continuous ingestion engine capable of running indefinitely on minimal hardware.

**Would you like me to generate the canonical C source code for this specific subsystem (worker_queue.h and worker_queue.c) so we can freeze the backpressure logic and fully stabilize the Foundation Phase?**