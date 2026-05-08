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

    K501_DocumentSet docs = {0};
    K501_NormalizedSet norm = {0};
    K501_State state = {0}, final = {0};

    if (k501_ingest_directory(argv[1], &docs) != 0) {
        printf("ERROR: ingestion failed\n");
        return 1;
    }

    if (docs.count == 0) {
        printf("ERROR: no valid files found\n");
        return 1;
    }

    k501_parse_batch(&docs, &norm);

    if (norm.count == 0) {
        printf("ERROR: parsing produced no data\n");
        return 1;
    }

    k501_frame_build(&norm, &state);

    if (state.count == 0) {
        printf("ERROR: no frames built\n");
        return 1;
    }

    k501_iterate_fixpoint(&state, &final, 10);

    k501_write_frames_ndjson(&final, "output.ndjson");

    printf("SUCCESS: %zu frames\n", final.count);
    return 0;
}