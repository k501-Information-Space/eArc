#include "ingestion.h"
#include "qh_core.h"
#include "frame_engine.h"
#include "dynamic_cage.h"
#include "hard_index.h"
#include <stdio.h>
#include <string.h>

/* Extern hooks to main.c */
extern uint64_t get_monotonic_time(void);
extern bool append_frame_to_disk(frame_t *f);

bool ingest_document(const char *filepath) {
    FILE *in = fopen(filepath, "rb");
    if (!in) {
        printf("[K501] Error: Cannot open document %s\n", filepath);
        return false;
    }

    char chunk_buffer[4096];
    size_t bytes_read;
    uint32_t chunk_index = 0;

    printf("[K501] Ingesting %s...\n", filepath);

    while ((bytes_read = fread(chunk_buffer, 1, sizeof(chunk_buffer), in)) > 0) {
        frame_t f;
        char frame_id[64];
        
        snprintf(frame_id, sizeof(frame_id), "DOC-CHUNK-%u", chunk_index);
        qhc_frame_init(&f, frame_id, get_monotonic_time());
        qhc_set_qh_cell(&f, 0, QH_TRUE);

        fe_compute_hash(&f);

        if (dc_validate_for_append(&f)) {
            if (append_frame_to_disk(&f)) {
                printf("  -> Appended: %s [Hash: %.16s...]\n", f.id, f.hash);
            }
        } else {
            printf("[K501] Cage Rejected Frame: %s\n", f.id);
        }

        chunk_index++;
    }

    fclose(in);
    printf("[K501] Ingestion complete. %u chunks processed.\n", chunk_index);
    return true;
}