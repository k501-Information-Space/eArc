#ifndef K501_ITERATION_H
#define K501_ITERATION_H

#include "k501_types.h"

int k501_iterate_fixpoint(
    K501_State *initial,
    K501_State *final,
    int max_iterations
);

#endif