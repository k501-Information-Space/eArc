#ifndef K501_HARD_INDEX_H
#define K501_HARD_INDEX_H

#include <stdint.h>
#include <stdbool.h>

/* K501 Canonical Index Entry */
typedef struct {
    char hash[65];      // Null-terminated SHA-256 hash string
    uint64_t offset;    // Physical byte offset in frames.ndjson
} index_entry_t;

/* Hard Index Prototypes */
bool hi_init(void);
bool hi_append_entry(const char *hash, uint64_t offset);
uint64_t hi_lookup_hash(const char *hash);

#endif // K501_HARD_INDEX_H