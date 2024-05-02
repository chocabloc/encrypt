#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define unassert(cond, msg) do {                                        \
    if (!(cond)) break;                                                 \
    fprintf(stderr, "\e[1;31merror:\e[0m %s \e[0;90m("                  \
    "%d@%s: %s)\e[0m\n", (msg), __LINE__, __FILE__, (#cond));           \
    exit(-1);                                                           \
} while(0);

#define U256(a, b, c, d) (uint256_t) { {a, b, c, d} };

typedef struct {
    uint64_t dat[4];
} uint256_t;

[[maybe_unused]] static void u256_xor(uint256_t* ret, uint256_t a, uint256_t b) {
    for (int i = 0; i < 4; i++)
        ret->dat[i] = a.dat[i] ^ b.dat[i];
}