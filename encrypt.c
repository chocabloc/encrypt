#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "sha-256.h"
#include "rng.h"

int main(int argc, char** args) {
    unassert(argc <= 1, "encrypt what?");

    // open file and get its size
    FILE* file = fopen(args[1], "rb");
    unassert(file == NULL, "file doesn't exist.");

    // input passkey
    printf("enter passkey (max 100 chars): ");
    char pwd[101] = {0};
    fgets(pwd, 100, stdin);
    
    // calc sha256 of the passkey
    uint256_t pwdh = U256(0, 0, 0, 0);
    calc_sha_256((uint8_t*)(&pwdh), (void*)pwd, 100);

    // use that to seed our rng
    rng_seed(pwdh);

    // create output file
    char* outname;
    if (argc >= 3)
        outname = args[2];
    else {
        outname = calloc(strlen(args[1]) + strlen(".encrypted") + 1, 1);
        sprintf(outname, "%s.encrypted", args[1]);
    }
    FILE* out = fopen(outname, "wb");
    unassert(out == NULL, "couldn't create output file");

    // encrypt the file
    while (!feof(file)) {
        uint256_t dat;
        int len = fread((void*)(&dat), 1, 32, file);
        u256_xor(&dat, dat, pwdh);
        fwrite((void*)(&dat), 1, len, out);
        pwdh = rng_get();
    }

    printf("\x1b[A\rdone");
    fclose(out);
    fclose(file);
    return 0;
}