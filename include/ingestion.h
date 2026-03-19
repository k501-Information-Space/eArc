#ifndef K501_INGESTION_H
#define K501_INGESTION_H

#include "k501_types.h"

int k501_ingest_directory(const char *path, K501_DocumentSet *out);

#endif