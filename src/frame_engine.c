#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frame_engine.h"
#include "qh_core.h"

static char *read_file(const char *path, size_t *len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = malloc(size + 1);
    fread(buf, 1, size, f);
    fclose(f);

    buf[size] = 0;
    *len = size;
    return buf;
}

int k501_parse_batch(const K501_DocumentSet *docs, K501_NormalizedSet *out) {
    out->units = malloc(sizeof(K501_NormalizedUnit) * docs->count);
    out->count = docs->count;

    for (size_t i = 0; i < docs->count; i++) {
        out->units[i].data = read_file(docs->docs[i].path, &out->units[i].len);
    }

    return 0;
}

int k501_frame_build(const K501_NormalizedSet *chunks, K501_State *state_out) {
    state_out->frames = malloc(sizeof(K501_Frame) * chunks->count);
    state_out->count = chunks->count;

    for (size_t i = 0; i < chunks->count; i++) {
        k501_hash_compute(
            (uint8_t*)chunks->units[i].data,
            chunks->units[i].len,
            state_out->frames[i].hash
        );

        state_out->frames[i].payload =
            (uint8_t*)chunks->units[i].data;

        state_out->frames[i].payload_len =
            chunks->units[i].len;
    }

    return 0;
}