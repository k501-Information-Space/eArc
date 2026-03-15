#include "qh_core.h"
#include <string.h>

void qhc_frame_init(frame_t *f, const char *id, uint64_t timestamp) {
    if (!f) return;
    
    memset(f, 0, sizeof(frame_t));
    
    if (id) {
        strncpy(f->id, id, sizeof(f->id) - 1);
        f->id[sizeof(f->id) - 1] = '\0'; 
    }
    
    f->time = timestamp;
    
    for (int i = 0; i < 56; ++i) {
        f->qh[i] = QH_UNKNOWN;
    }
}

bool qhc_set_qh_cell(frame_t *f, uint8_t index, qh_cell state) {
    if (!f || index >= 56 || !qh_validate(state)) {
        return false;
    }
    f->qh[index] = state;
    return true;
}

bool qhc_validate_frame_structure(const frame_t *f) {
    if (!f) return false;
    if (f->id[0] == '\0') return false;
    if (f->time < 1773524342ULL) return false;
    
    for (int i = 0; i < 56; ++i) {
        if (!qh_validate(f->qh[i])) return false;
    }
    return true;
}