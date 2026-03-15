#ifndef K501_DYNAMIC_CAGE_H
#define K501_DYNAMIC_CAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "qh_core.h"

/* Cage Runtime State */
typedef struct {
    uint64_t last_time;     
    bool is_active;         
} cage_state_t;

/* Guardian Prototypes */
bool dc_init(uint64_t genesis_time);
bool dc_validate_for_append(const frame_t *candidate_frame);
void dc_force_time(uint64_t override_time);

#endif // K501_DYNAMIC_CAGE_H