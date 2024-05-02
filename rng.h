#pragma once

#include "common.h"

void rng_seed(uint256_t seed);
uint256_t rng_get();
uint64_t trng_get64();
void trng_init();