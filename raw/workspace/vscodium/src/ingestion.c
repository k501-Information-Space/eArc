#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "ingestion.h"

int k501_ingest_directory(const char *path, K501_DocumentSet *out) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0) return -1;

    out->docs = NULL;
    out->count = 0;

    for (int i = 0; i < n; i++) {
        if (namelist[i]->d_name[0] == '.') {
            free(namelist[i]);
            continue;
        }

        char fullpath[K501_MAX_PATH];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, namelist[i]->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0 && S_ISREG(st.st_mode)) {

            out->docs = realloc(out->docs, sizeof(K501_Document) * (out->count + 1));

            strncpy(out->docs[out->count].path, fullpath, K501_MAX_PATH);
            out->docs[out->count].size = st.st_size;

            out->count++;
        }

        free(namelist[i]);
    }

    free(namelist);
    return 0;
}