#ifndef K501_FRAME_ENGINE_H
#define K501_FRAME_ENGINE_H

#include "k501_types.h"

int k501_parse_batch(const K501_DocumentSet *docs, K501_NormalizedSet *out);
int k501_frame_build(const K501_NormalizedSet *chunks, K501_State *state_out);

#endif