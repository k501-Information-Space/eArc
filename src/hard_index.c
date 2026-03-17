#include "hard_index.h"
#include <stdio.h>
#include <string.h>

static const char *INDEX_FILE = "archive/little_alpha_storage/index.dat";

bool hi_init(void) {
    FILE *f = fopen(INDEX_FILE, "ab");
    if (!f) return false;
    fclose(f);
    return true;
}

bool hi_append_entry(const char *hash, uint64_t offset) {
    if (!hash) return false;

    index_entry_t entry;
    memset(&entry, 0, sizeof(index_entry_t));
    strncpy(entry.hash, hash, 64);
    entry.offset = offset;

    FILE *f = fopen(INDEX_FILE, "ab");
    if (!f) return false;

    size_t written = fwrite(&entry, sizeof(index_entry_t), 1, f);
    fclose(f);

    return (written == 1);
}

uint64_t hi_lookup_hash(const char *hash) {
    if (!hash) return UINT64_MAX;

    FILE *f = fopen(INDEX_FILE, "rb");
    if (!f) return UINT64_MAX;

    index_entry_t entry;
    uint64_t found_offset = UINT64_MAX;

    while (fread(&entry, sizeof(index_entry_t), 1, f) == 1) {
        if (strncmp(entry.hash, hash, 64) == 0) {
            found_offset = entry.offset;
            break;
        }
    }

    fclose(f);
    return found_offset;
}