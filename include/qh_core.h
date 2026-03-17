#ifndef K501_QH_CORE_H
#define K501_QH_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include "qh_algebra.h"

typedef struct {
    char id[128];          // Erweitert für längere Pfade
    uint64_t time;         // Unix Epoch
    qh_cell qh[56];        // Quantum Header Matrix
    char content_hash[65]; // Hash des 4KB Chunks (Der Anker zum Dokument)
    char hash[65];         // Hash des gesamten Frames (Die Kette)
} frame_t;

void qhc_frame_init(frame_t *f, const char *id, uint64_t timestamp);
bool qhc_set_qh_cell(frame_t *f, uint8_t index, qh_cell state);
bool qhc_validate_frame_structure(const frame_t *f);

#endif