#include "qh_algebra.h"

qh_cell qh_and(qh_cell a, qh_cell b) {
    if (a == QH_GUARD || b == QH_GUARD) return QH_GUARD;
    if (a == QH_FALSE || b == QH_FALSE) return QH_FALSE;
    if (a == QH_UNKNOWN || b == QH_UNKNOWN) return QH_UNKNOWN;
    return QH_TRUE; 
}

qh_cell qh_or(qh_cell a, qh_cell b) {
    if (a == QH_GUARD || b == QH_GUARD) return QH_GUARD;
    if (a == QH_TRUE || b == QH_TRUE) return QH_TRUE;
    if (a == QH_UNKNOWN || b == QH_UNKNOWN) return QH_UNKNOWN;
    return QH_FALSE; 
}

qh_cell qh_guard_lock(qh_cell a) {
    (void)a; 
    return QH_GUARD;
}

bool qh_validate(qh_cell a) {
    return (a == QH_UNKNOWN || a == QH_FALSE || a == QH_TRUE || a == QH_GUARD);
}