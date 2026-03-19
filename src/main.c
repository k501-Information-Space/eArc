#include <stdio.h>
#include "ingestion.h"
#include "frame_engine.h"
#include "iteration.h"
#include "hard_index.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <dir>\n", argv[0]);
        return 1;
    }

    K501_DocumentSet docs;
    K501_NormalizedSet norm;
    K501_State state, final;

    k501_ingest_directory(argv[1], &docs);
    k501_parse_batch(&docs, &norm);
    k501_frame_build(&norm, &state);
    k501_iterate_fixpoint(&state, &final, 10);
    k501_write_frames_ndjson(&final, "output.ndjson");

    printf("OK\n");
    return 0;
}