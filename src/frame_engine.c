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

    if (size <= 0) {
        fclose(f);
        return NULL;
    }

    char *buf = malloc(size + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t read_bytes = fread(buf, 1, size, f);
    fclose(f);

    if (read_bytes != (size_t)size) {
        free(buf);
        return NULL;
    }

    buf[size] = 0;
    *len = size;
    return buf;
}

int k501_parse_batch(const K501_DocumentSet *docs, K501_NormalizedSet *out) {
    out->units = NULL;
    out->count = 0;

    for (size_t i = 0; i < docs->count; i++) {

        size_t len = 0;
        char *data = read_file(docs->docs[i].path, &len);

        if (!data) {
            continue; // skip invalid files
        }

        out->units = realloc(out->units, sizeof(K501_NormalizedUnit) * (out->count + 1));

        out->units[out->count].data = data;
        out->units[out->count].len = len;

        out->count++;
    }

    return 0;
}

int k501_frame_build(const K501_NormalizedSet *chunks, K501_State *state_out) {
    state_out->frames = NULL;
    state_out->count = 0;

    for (size_t i = 0; i < chunks->count; i++) {

        if (!chunks->units[i].data) continue;

        state_out->frames = realloc(state_out->frames, sizeof(K501_Frame) * (state_out->count + 1));

        K501_Frame *f = &state_out->frames[state_out->count];

        k501_hash_compute(
            (uint8_t*)chunks->units[i].data,
            chunks->units[i].len,
            f->hash
        );

        f->payload = (uint8_t*)chunks->units[i].data;
        f->payload_len = chunks->units[i].len;

        state_out->count++;
    }

    return 0;
}