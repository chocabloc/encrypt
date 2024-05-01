# Source and Object files
SRC = decrypt.c encrypt.c rng.c sha-256.c
OBJ = $(SRC:.c=.o)

# Compiler options
CC = gcc
LD = gcc
CFLAGS = -std=gnu2x -Ofast -flto -fopenmp -march=native -Wall -Wno-missing-braces
LDFLAGS = -flto -fopenmp -lm

# Output binary
OUT = ./encrypt ./decrypt

# Rules
.phony = clean

all: $(OUT)

$(OUT): $(OBJ)
	$(LD) decrypt.o sha-256.o rng.o $(LDFLAGS) -o ./decrypt
	$(LD) encrypt.o sha-256.o rng.o $(LDFLAGS) -o ./encrypt

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ)
