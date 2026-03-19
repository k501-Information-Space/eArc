#ifndef K501_TYPES_H
#define K501_TYPES_H

#include <stdint.h>
#include <stdlib.h>

#define K501_MAX_PATH 1024

typedef struct {
    char path[K501_MAX_PATH];
    uint64_t size;
} K501_Document;

typedef struct {
    K501_Document *docs;
    size_t count;
} K501_DocumentSet;

typedef struct {
    char *data;
    size_t len;
} K501_NormalizedUnit;

typedef struct {
    K501_NormalizedUnit *units;
    size_t count;
} K501_NormalizedSet;

typedef struct {
    uint8_t hash[32];
    uint8_t *payload;
    size_t payload_len;
} K501_Frame;

typedef struct {
    K501_Frame *frames;
    size_t count;
} K501_State;

#endif