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

#define RING_SIZE 16384
#define FRAME_MAX 1024
#define CHUNK_SIZE 4096
#define LEDGER_FILE "archive/little_alpha_storage/frames.ndjson"

typedef struct { char data[FRAME_MAX]; size_t len; } frame_t;

static frame_t ring[RING_SIZE];
static volatile uint32_t head = 0, tail = 0;
static int ledger_fd;
static volatile int producer_done = 0;
static uint64_t total_chunks = 0;

void hash_to_hex(const unsigned char *h, char *out) {
    static const char *t = "0123456789abcdef";
    for(int i = 0; i < 32; i++) { out[i*2] = t[h[i]>>4]; out[i*2+1] = t[h[i]&15]; }
    out[64] = 0;
}

void process_file_mmap(const char *path, EVP_MD_CTX *ctx, const EVP_MD *md) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return;
    struct stat st;
    fstat(fd, &st);
    if (st.st_size == 0 || !S_ISREG(st.st_mode)) { close(fd); return; }

    unsigned char *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) { close(fd); return; }

    unsigned char hash[32];
    char hashhex[65];
    size_t offset = 0;
    uint32_t chunk_idx = 0;

    while (offset < st.st_size) {
        size_t current_chunk = (st.st_size - offset < CHUNK_SIZE) ? st.st_size - offset : CHUNK_SIZE;
        uint32_t next = (head + 1) % RING_SIZE;
        while (next == tail) { __builtin_ia32_pause(); next = (head + 1) % RING_SIZE; }

        EVP_DigestInit_ex(ctx, md, NULL);
        EVP_DigestUpdate(ctx, map + offset, current_chunk);
        EVP_DigestFinal_ex(ctx, hash, NULL);
        hash_to_hex(hash, hashhex);

        frame_t *f = &ring[head];
        f->len = snprintf(f->data, FRAME_MAX, "{\"id\":\"%s:%u\",\"t\":%lu,\"h\":\"%s\"}\n", path, chunk_idx, (uint64_t)time(NULL), hashhex);

        head = next;
        offset += current_chunk;
        chunk_idx++;
        total_chunks++;
    }
    munmap(map, st.st_size);
    close(fd);
}

void crawl_recursive(const char *name, EVP_MD_CTX *ctx, const EVP_MD *md) {
    DIR *dir = opendir(name);
    if (!dir) return;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
        struct stat st;
        stat(path, &st);
        if (S_ISDIR(st.st_mode)) crawl_recursive(path, ctx, md);
        else if (S_ISREG(st.st_mode)) process_file_mmap(path, ctx, md);
    }
    closedir(dir);
}

void* producer(void *arg) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    crawl_recursive((const char*)arg, ctx, EVP_sha256());
    EVP_MD_CTX_free(ctx);
    producer_done = 1;
    return NULL;
}

void* writer(void *arg) {
    while (!producer_done || head != tail) {
        if (tail == head) { __builtin_ia32_pause(); continue; }
        write(ledger_fd, ring[tail].data, ring[tail].len);
        tail = (tail + 1) % RING_SIZE;
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    ledger_fd = open(LEDGER_FILE, O_CREAT | O_APPEND | O_WRONLY, 0644);
    pthread_t p, w;
    pthread_create(&p, NULL, producer, argv[1]);
    pthread_create(&w, NULL, writer, NULL);
    pthread_join(p, NULL); pthread_join(w, NULL);
    fsync(ledger_fd); close(ledger_fd);
    printf("[K501] Ingested Chunks: %lu\n", total_chunks);
    return 0;
}