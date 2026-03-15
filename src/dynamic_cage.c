#include "dynamic_cage.h"
#include "frame_engine.h"
#include <string.h>

static cage_state_t g_cage = {0, false};

bool dc_init(uint64_t genesis_time) {
    g_cage.last_time = genesis_time;
    g_cage.is_active = true;
    return true;
}

void dc_force_time(uint64_t override_time) {
    g_cage.last_time = override_time;
}

bool dc_validate_for_append(const frame_t *candidate_frame) {
    if (!g_cage.is_active || !candidate_frame) return false;
    if (!qhc_validate_frame_structure(candidate_frame)) return false;
    if (candidate_frame->time <= g_cage.last_time) return false;

    frame_t shadow_copy;
    memcpy(&shadow_copy, candidate_frame, sizeof(frame_t));
    memset(shadow_copy.hash, 0, 65); 

    if (!fe_compute_hash(&shadow_copy)) return false;

    if (strncmp(candidate_frame->hash, shadow_copy.hash, 64) != 0) {
        return false; 
    }

    g_cage.last_time = candidate_frame->time;
    return true;
}