#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include "ingestion.h"
#include "qh_core.h"
#include "frame_engine.h"
#include "hard_index.h"
#include "dynamic_cage.h"

#define CHUNK_SIZE 4096
#define LEDGER_PATH "archive/little_alpha_storage/frames.ndjson"

bool ingest_document(const char *filepath) {
    FILE *source = fopen(filepath, "rb");
    if (!source) {
        perror("[K501] Source Error");
        return false;
    }

    FILE *ledger = fopen(LEDGER_PATH, "ab");
    if (!ledger) {
        perror("[K501] Ledger Error");
        fclose(source);
        return false;
    }

    uint8_t buffer[CHUNK_SIZE];
    uint32_t idx = 0;

    while (true) {
        size_t bytes_read = fread(buffer, 1, CHUNK_SIZE, source);
        if (bytes_read == 0) break;

        frame_t frame;
        char fid[128];
        snprintf(fid, sizeof(fid), "F-%06u-%s", idx, filepath);
        qhc_frame_init(&frame, fid, (uint64_t)time(NULL));

        // Content Hash berechnen
        unsigned char c_hash[32];
        SHA256(buffer, bytes_read, c_hash);
        for(int i=0; i<32; i++) sprintf(frame.content_hash + (i*2), "%02x", c_hash[i]);

        // QH-Stabilisierung
        for(int i=0; i<56; i++) qhc_set_qh_cell(&frame, i, QH_GUARD);

        if (dc_validate_for_append(&frame)) {
            fe_compute_hash(&frame);
            
            uint64_t offset = (uint64_t)ftell(ledger);
            char jcs[8192];
            fe_build_jcs(&frame, jcs, sizeof(jcs));

            fprintf(ledger, "{\"f\":%s,\"hash\":\"%s\"}\n", jcs, frame.hash);
            fflush(ledger);
            
            hi_append_entry(frame.hash, offset);
            idx++;
        } else {
            fprintf(stderr, "[!] Cage Interdiction at chunk %u\n", idx);
            break;
        }
    }

    fclose(source);
    fclose(ledger);
    printf("[K501] Ingested %u chunks.\n", idx);
    return true;
}