#ifndef K501_QH_CORE_H
#define K501_QH_CORE_H

#include <stdint.h>
#include <stddef.h>

int k501_hash_compute(const uint8_t *data, size_t len, uint8_t out[32]);

#endif