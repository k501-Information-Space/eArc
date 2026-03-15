#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qh_core.h"
#include "frame_engine.h"
#include "dynamic_cage.h"
#include "hard_index.h"
#include "ingestion.h"

static uint64_t current_time = 1773524342ULL; 

uint64_t get_monotonic_time(void) {
    current_time++; 
    return current_time;
}

bool append_frame_to_disk(frame_t *f) {
    FILE *out = fopen("storage/frames.ndjson", "ab");
    if (!out) return false;

    uint64_t offset = (uint64_t)ftell(out);

    fprintf(out, "{\"id\":\"%s\",\"t\":%llu,\"hash\":\"%s\"}\n", 
            f->id, (unsigned long long)f->time, f->hash);
    
    fclose(out);

    hi_append_entry(f->hash, offset);
    return true;
}

void print_usage() {
    printf("K501 Little Alpha Node\n");
    printf("Usage:\n");
    printf("  ./k501_alpha genesis         - Bootstrap AZ-Epoch-0\n");
    printf("  ./k501_alpha ingest <file>   - Ingest document into frames\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    hi_init();
    dc_init(1773524342ULL); 

    if (strcmp(argv[1], "genesis") == 0) {
        printf("[K501] Initiating Genesis Sequence...\n");
        frame_t f0;
        qhc_frame_init(&f0, "AZ-Epoch-0-Genesis", 1773524342ULL);
        qhc_set_qh_cell(&f0, 0, QH_GUARD); 
        
        fe_compute_hash(&f0);
        
        // Safely force manual bypass of temporal check for the very first frame
        dc_force_time(0); 
        
        if (dc_validate_for_append(&f0)) {
            append_frame_to_disk(&f0);
            printf("[K501] Genesis Locked. Hash: %s\n", f0.hash);
        } else {
            printf("[K501] FATAL: Genesis failed Cage validation.\n");
        }
    } 
    else if (strcmp(argv[1], "ingest") == 0) {
        if (argc < 3) {
            printf("[K501] Missing file path.\n");
            return 1;
        }
        ingest_document(argv[2]);
    } 
    else {
        print_usage();
    }

    return 0;
}