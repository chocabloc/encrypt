// XORShift random number generator

#include "common.h"
#include "rng.h"

static uint256_t rst;

void rng_seed(uint256_t seed)
{
    rst = seed;
}

uint256_t rng_get() {
    for (int i = 0; i < 4; i++) {
        rst.dat[i] ^= rst.dat[i] << 13;
        rst.dat[i] ^= rst.dat[i] >> 17;
        rst.dat[i] ^= rst.dat[i] << 5;
    }
    return rst;
}