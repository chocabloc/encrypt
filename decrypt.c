#include <stdio.h>
#include "common.h"
#include "sha-256.h"
#include "rng.h"

int main(int argc, char** args) {
    unassert(argc <= 1, "decrypt what?");

    // open file and get its size
    FILE* file = fopen(args[1], "rb");
    unassert(file == NULL, "file doesn't exist.");

    // get salt from file
    uint64_t salt;
    fread(&salt, 1, 8, file);

    // input passkey
    printf("enter passkey: ");
    char pwd[101] = {0};
    fgets(pwd, 100, stdin);

    // add salt to the passkey
    int pwdlen = strlen(pwd) - 1;
    *(uint64_t*)(pwd + pwdlen) = salt;
    pwdlen += 8;
    
    // calc sha256 of the passkey
    uint256_t pwdh = U256(0, 0, 0, 0);
    calc_sha_256((uint8_t*)(&pwdh), (void*)pwd, pwdlen);

    // use that to seed our rng
    rng_seed(pwdh);

    // create output file
    char* outname;
    if (argc >= 3)
        outname = args[2];
    else {
        outname = calloc(strlen(args[1]) + strlen(".decrypted") + 1, 1);
        sprintf(outname, "%s.decrypted", args[1]);
    }
    FILE* out = fopen(outname, "wb");
    unassert(out == NULL, "couldn't create output file.");

    // decrypt the file
    while (!feof(file)) {
        uint256_t dat;
        int len = fread((void*)(&dat), 1, 32, file);
        u256_xor(&dat, dat, pwdh);
        fwrite((void*)(&dat), 1, len, out);
        pwdh = rng_get();
    }

    printf("\x1b[A\33[2K\rdone\n");
    fclose(out);
    fclose(file);
    return 0;
}