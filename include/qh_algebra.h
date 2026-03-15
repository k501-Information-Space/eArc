#ifndef K501_QH_ALGEBRA_H
#define K501_QH_ALGEBRA_H

#include <stdint.h>
#include <stdbool.h>

/* K501 Canonical QH States (Binary Representation) */
#define QH_UNKNOWN 0x00  // 00
#define QH_FALSE   0x01  // 01
#define QH_TRUE    0x02  // 10
#define QH_GUARD   0x03  // 11

typedef uint8_t qh_cell;

/* Epistemic Operator Prototypes */
qh_cell qh_and(qh_cell a, qh_cell b);
qh_cell qh_or(qh_cell a, qh_cell b);
qh_cell qh_guard_lock(qh_cell a);
bool qh_validate(qh_cell a);

#endif // K501_QH_ALGEBRA_H