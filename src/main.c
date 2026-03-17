#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>    // Fix: Definiert uint64_t
#include <time.h>      // Fix: Definiert time()
#include "qh_core.h"
#include "frame_engine.h"
#include "dynamic_cage.h"
#include "hard_index.h"
#include "ingestion.h"

#define LEDGER_PATH "archive/little_alpha_storage/frames.ndjson"

// Hilfsfunktion: Sucht den letzten Zeitstempel im Ledger
uint64_t get_last_timestamp(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return 1773524342ULL; 

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size < 50) { fclose(f); return 1773524342ULL; }

    long read_len = (size > 512) ? 512 : size;
    fseek(f, -read_len, SEEK_END);
    char buf[513];
    size_t n = fread(buf, 1, read_len, f);
    buf[n] = '\0';
    fclose(f);

    char *ptr = strstr(buf, ",\"t\":");
    if (!ptr) return 1773524342ULL;
    
    char *last_ptr = ptr;
    char *next_ptr;
    while ((next_ptr = strstr(last_ptr + 1, ",\"t\":"))) {
        last_ptr = next_ptr;
    }

    return (uint64_t)strtoull(last_ptr + 5, NULL, 10);
}

// Hilfsfunktion zum Schreiben einzelner Frames (Genesis)
bool append_frame_to_disk(frame_t *f) {
    FILE *out = fopen(LEDGER_PATH, "ab");
    if (!out) return false;
    char jcs_buffer[8192];
    if (!fe_build_jcs(f, jcs_buffer, sizeof(jcs_buffer))) { fclose(out); return false; }
    uint64_t offset = (uint64_t)ftell(out);
    fprintf(out, "{\"f\":%s,\"hash\":\"%s\"}\n", jcs_buffer, f->hash);
    fclose(out);
    hi_append_entry(f->hash, offset);
    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("K501 Alpha\nUsage: ./k501_alpha [genesis|ingest <file>]\n");
        return 1;
    }

    hi_init();

    uint64_t ledger_time = get_last_timestamp(LEDGER_PATH);
    dc_init(ledger_time); 

    if (strcmp(argv[1], "genesis") == 0) {
        printf("[K501] Initiating Genesis...\n");
        frame_t f0;
        qhc_frame_init(&f0, "AZ-Epoch-0-Genesis", ledger_time);
        qhc_set_qh_cell(&f0, 0, QH_GUARD); 
        fe_compute_hash(&f0);
        dc_force_time(0); 
        if (dc_validate_for_append(&f0)) {
            append_frame_to_disk(&f0);
            printf("[K501] Genesis Locked. Hash: %s\n", f0.hash);
        }
    } 
    else if (strcmp(argv[1], "ingest") == 0) {
        if (argc < 3) return 1;
        printf("[K501] Synchronized Cage to: %llu\n", (unsigned long long)ledger_time);
        ingest_document(argv[2]);
    }

    return 0;
}