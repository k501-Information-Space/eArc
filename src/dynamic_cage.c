#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "qh_core.h"
#include "frame_engine.h"
#include "dynamic_cage.h"
#include "hard_index.h"
#include "ingestion.h"

#define LEDGER_PATH "archive/little_alpha_storage/frames.ndjson"

// Hilfsfunktion: Sucht den letzten Zeitstempel im Ledger
uint64_t get_last_timestamp(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return 1773524342ULL; // Genesis-Fallback

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size < 50) { fclose(f); return 1773524342ULL; }

    // Die letzten 512 Bytes lesen
    long read_len = (size > 512) ? 512 : size;
    fseek(f, -read_len, SEEK_END);
    char buf[513];
    size_t n = fread(buf, 1, read_len, f);
    buf[n] = '\0';
    fclose(f);

    // Suche rückwärts nach dem Zeitstempel-Tag
    char *ptr = strstr(buf, ",\"t\":");
    if (!ptr) return 1773524342ULL;
    
    // Finde das letzte Vorkommen von "t":
    char *last_ptr = ptr;
    while ((ptr = strstr(last_ptr + 1, ",\"t\":"))) {
        last_ptr = ptr;
    }

    return (uint64_t)strtoull(last_ptr + 5, NULL, 10);
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    hi_init();

    // KERNEL-SYNCHRONISATION: Zeit aus physischem Ledger extrahieren
    uint64_t ledger_time = get_last_timestamp(LEDGER_PATH);
    dc_init(ledger_time);

    if (strcmp(argv[1], "genesis") == 0) {
        // ... (Genesis Logik wie gehabt)
    } 
    else if (strcmp(argv[1], "ingest") == 0) {
        if (argc < 3) return 1;
        
        // Sicherstellen, dass der erste Frame des neuen Laufs 
        // nicht vor dem Ledger liegt
        uint64_t now = (uint64_t)time(NULL);
        if (now < ledger_time) now = ledger_time;

        ingest_document(argv[2]);
    }

    return 0;
}