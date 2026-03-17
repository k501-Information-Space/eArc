#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <sched.h>
#include <openssl/evp.h>

/* --- CONFIG --- */
#define RING_SIZE 16384
#define FRAME_MAX 1024
#define LEDGER_FILE "archive/little_alpha_storage/frames.ndjson"

typedef struct {
    char data[FRAME_MAX];
    size_t len;
} frame_t;

/* --- STATE --- */
static frame_t ring[RING_SIZE];
static volatile uint32_t head = 0;
static volatile uint32_t tail = 0;
static int ledger_fd;
static volatile int keep_running = 1;

/* --- UTILS --- */
void hash_to_hex(const unsigned char *h, char *out) {
    static const char *t = "0123456789abcdef";
    for(int i = 0; i < 32; i++) {
        out[i*2] = t[h[i]>>4];
        out[i*2+1] = t[h[i]&15];
    }
    out[64] = 0;
}

void pin_cpu(int cpu) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu, &set);
    sched_setaffinity(0, sizeof(set), &set);
}

/* --- PRODUCER (Engine) --- */
void* producer(void *arg) {
    pin_cpu(1); // Producer on Core 1
    uint64_t seq = 0;
    unsigned char hash[32];
    char hashhex[65];
    char id[64];
    
    /* Persistent OpenSSL Context */
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();

    while(keep_running) {
        uint32_t next = (head + 1) % RING_SIZE;
        if(next == tail) {
            __builtin_ia32_pause();
            continue;
        }

        snprintf(id, sizeof(id), "F-%012lu", seq);
        
        /* Fast Hashing */
        EVP_DigestInit_ex(ctx, md, NULL);
        EVP_DigestUpdate(ctx, id, strlen(id));
        EVP_DigestFinal_ex(ctx, hash, NULL);
        
        hash_to_hex(hash, hashhex);
        uint64_t ts = (uint64_t)time(NULL);

        /* Build Frame directly in Ring */
        frame_t *f = &ring[head];
        f->len = snprintf(f->data, FRAME_MAX, 
                 "{\"id\":\"%s\",\"t\":%lu,\"hash\":\"%s\"}\n", 
                 id, ts, hashhex);

        head = next;
        seq++;
        
        if(seq >= 1000000) keep_running = 0;
    }
    
    EVP_MD_CTX_free(ctx);
    return NULL;
}

/* --- WRITER (Persistence) --- */
void* writer(void *arg) {
    pin_cpu(0); // Writer on Core 0
    while(keep_running || head != tail) {
        if(tail == head) {
            __builtin_ia32_pause();
            continue;
        }

        frame_t *f = &ring[tail];
        write(ledger_fd, f->data, f->len);
        
        tail = (tail + 1) % RING_SIZE;
    }
    return NULL;
}

/* --- MAIN --- */
int main() {
    ledger_fd = open(LEDGER_FILE, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if(ledger_fd < 0) {
        perror("[K501] Ledger open failed");
        return 1;
    }

    printf("[K501] Kernel V2.4 High-Inertia Mode Active\n");
    printf("[K501] Core 0: Writer | Core 1: Producer\n");

    pthread_t prod_thread, writ_thread;
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&writ_thread, NULL, writer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(writ_thread, NULL);

    fsync(ledger_fd);
    close(ledger_fd);
    
    printf("[K501] Sequence Complete. 1M Frames anchored.\n");
    return 0;
}