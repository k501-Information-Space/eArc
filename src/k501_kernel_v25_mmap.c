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
#include <dirent.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <openssl/evp.h>

/* --- CONFIG --- */
#define RING_SIZE 16384
#define FRAME_MAX 1024
#define CHUNK_SIZE 4096
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
static volatile int producer_done = 0;

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

/* --- MMAP INGEST LOGIC --- */
void process_file(const char *path, EVP_MD_CTX *ctx, const EVP_MD *md) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return;

    struct stat st;
    fstat(fd, &st);
    if (st.st_size == 0) { close(fd); return; }

    // Map the whole file into memory
    unsigned char *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) { close(fd); return; }

    unsigned char hash[32];
    char hashhex[65];
    size_t offset = 0;
    uint32_t file_chunk_idx = 0;

    while (offset < st.st_size) {
        size_t remaining = st.st_size - offset;
        size_t current_chunk = (remaining < CHUNK_SIZE) ? remaining : CHUNK_SIZE;

        // Wait for ring space
        uint32_t next = (head + 1) % RING_SIZE;
        while (next == tail) { __builtin_ia32_pause(); next = (head + 1) % RING_SIZE; }

        // Hash chunk directly from memory map
        EVP_DigestInit_ex(ctx, md, NULL);
        EVP_DigestUpdate(ctx, map + offset, current_chunk);
        EVP_DigestFinal_ex(ctx, hash, NULL);
        hash_to_hex(hash, hashhex);

        frame_t *f = &ring[head];
        f->len = snprintf(f->data, FRAME_MAX, 
                 "{\"id\":\"%s:%u\",\"t\":%lu,\"d_hash\":\"%s\"}\n", 
                 path, file_chunk_idx, (uint64_t)time(NULL), hashhex);

        head = next;
        offset += current_chunk;
        file_chunk_idx++;
    }

    munmap(map, st.st_size);
    close(fd);
}

/* --- PRODUCER (Directory Crawler) --- */
void* producer(void *arg) {
    const char *dir_path = (const char*)arg;
    pin_cpu(1);
    
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();

    DIR *d = opendir(dir_path);
    if (!d) { producer_done = 1; return NULL; }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, dir->d_name);
            process_file(full_path, ctx, md);
        }
    }

    closedir(d);
    EVP_MD_CTX_free(ctx);
    producer_done = 1;
    return NULL;
}

/* --- WRITER --- */
void* writer(void *arg) {
    pin_cpu(0);
    while (!producer_done || head != tail) {
        if (tail == head) { __builtin_ia32_pause(); continue; }
        frame_t *f = &ring[tail];
        write(ledger_fd, f->data, f->len);
        tail = (tail + 1) % RING_SIZE;
    }
    return NULL;
}

/* --- MAIN --- */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <target_directory>\n", argv[0]);
        return 1;
    }

    ledger_fd = open(LEDGER_FILE, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (ledger_fd < 0) { perror("ledger open"); return 1; }

    printf("[K501] Kernel V2.5 MMAP-Ingest Active\n");

    pthread_t prod_thread, writ_thread;
    pthread_create(&prod_thread, NULL, producer, argv[1]);
    pthread_create(&writ_thread, NULL, writer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(writ_thread, NULL);

    fsync(ledger_fd);
    close(ledger_fd);
    
    printf("[K501] eArc Ingest Complete.\n");
    return 0;
}