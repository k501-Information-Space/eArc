CC=gcc
CFLAGS=-Iinclude -Wall -O2

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

k501_core.bin: $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -f src/*.o k501_core.bin