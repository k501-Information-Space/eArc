#ifndef K501_QH_CORE_H
#define K501_QH_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include "qh_algebra.h"

/* K501 Canonical Frame Structure */
typedef struct {
    char id[64];      // Null-terminated identifier
    uint64_t time;    // Unix Epoch timestamp
    qh_cell qh[56];   // 56-cell Quantum Header matrix
    char hash[65];    // Null-terminated SHA-256 hex string
} frame_t;

/* Frame Lifecycle Prototypes */
void qhc_frame_init(frame_t *f, const char *id, uint64_t timestamp);
bool qhc_set_qh_cell(frame_t *f, uint8_t index, qh_cell state);
bool qhc_validate_frame_structure(const frame_t *f);

#endif // K501_QH_CORE_H