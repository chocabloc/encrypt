// XORShift random number generator

#include <stdio.h>
#include "common.h"
#include "rng.h"

static uint256_t rst;
static FILE* urandom;
static bool init = false;

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

void trng_init() {
    urandom = fopen("/dev/urandom", "rb");
    unassert(urandom == NULL, "couldn't open /dev/urandom.");
    init = true;
}

uint64_t trng_get64() {
    unassert(!init, "used without initialisation.");
    uint64_t rn;
    fread(&rn, 1, 8, urandom);
    return rn;
}
