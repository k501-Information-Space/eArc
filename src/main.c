#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "qh_core.h"
#include "frame_engine.h"
#include "dynamic_cage.h"
#include "hard_index.h"
#include "ingestion.h"

// Der Pfad muss exakt mit deiner Baumstruktur übereinstimmen
#define LEDGER_PATH "archive/little_alpha_storage/frames.ndjson"

bool append_frame_to_disk(frame_t *f) {
    FILE *out = fopen(LEDGER_PATH, "ab");
    if (!out) {
        perror("[K501] Ledger Access Error");
        return false;
    }

    char jcs_buffer[8192];
    if (!fe_build_jcs(f, jcs_buffer, sizeof(jcs_buffer))) {
        fclose(out);
        return false;
    }

    uint64_t offset = (uint64_t)ftell(out);
    
    // Schreiben des kanonischen Frames
    fprintf(out, "{\"f\":%s,\"hash\":\"%s\"}\n", jcs_buffer, f->hash);
    fclose(out);

    // Index-Eintrag schreiben
    hi_append_entry(f->hash, offset);
    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("K501 Node Alpha\nUsage: ./k501_alpha [genesis|ingest <file>]\n");
        return 1;
    }

    // Initialisierung mit Fehlerprüfung
    if (!hi_init()) {
        fprintf(stderr, "[K501] FATAL: Hard Index initialization failed. Check path: archive/little_alpha_storage/\n");
        return 1;
    }

    uint64_t now = (uint64_t)time(NULL);
    dc_init(now); 

    if (strcmp(argv[1], "genesis") == 0) {
        printf("[K501] Initiating Genesis...\n");
        frame_t f0;
        qhc_frame_init(&f0, "AZ-Epoch-0-Genesis", now);
        qhc_set_qh_cell(&f0, 0, QH_GUARD); 
        fe_compute_hash(&f0);
        
        dc_force_time(0); 
        if (dc_validate_for_append(&f0)) {
            if (append_frame_to_disk(&f0)) {
                printf("[K501] Genesis Locked. Hash: %s\n", f0.hash);
            }
        } else {
            printf("[K501] FATAL: Genesis failed Cage validation.\n");
        }
    } 
    else if (strcmp(argv[1], "ingest") == 0) {
        if (argc < 3) return 1;
        ingest_document(argv[2]);
    }

    return 0;
}