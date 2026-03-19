#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ingestion.h"

int k501_ingest_directory(const char *path, K501_DocumentSet *out) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0) return -1;

    out->docs = malloc(sizeof(K501_Document) * n);
    out->count = 0;

    for (int i = 0; i < n; i++) {
        if (namelist[i]->d_name[0] == '.') {
            free(namelist[i]);
            continue;
        }

        snprintf(out->docs[out->count].path, K501_MAX_PATH,
                 "%s/%s", path, namelist[i]->d_name);

        out->docs[out->count].size = 0;
        out->count++;

        free(namelist[i]);
    }

    free(namelist);
    return 0;
}