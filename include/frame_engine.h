#ifndef K501_FRAME_ENGINE_H
#define K501_FRAME_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "qh_core.h"

/* Canonical Serialization and Hashing Prototypes */
bool fe_build_jcs(const frame_t *f, char *out_buffer, size_t max_len);
bool fe_compute_hash(frame_t *f);

#endif // K501_FRAME_ENGINE_H