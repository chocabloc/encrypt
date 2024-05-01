# Source and Object files
SRC = decrypt.c encrypt.c rng.c
OBJ = $(SRC:.c=.o)

# Compiler options
CC = gcc
LD = gcc
CFLAGS = -std=gnu2x -Ofast -flto -fopenmp -march=native -Wall -Wno-missing-braces
LDFLAGS = -flto -fopenmp -L/usr/X11R6/lib -lX11 -lm

# Output binary
OUT = ./encrypt ./decrypt

# Rules
.phony = clean

all: $(OUT)

$(OUT): $(OBJ)
	$(LD) decrypt.o $(LDFLAGS) -o ./decrypt
	$(LD) encrypt.o $(LDFLAGS) -o ./encrypt

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ)
