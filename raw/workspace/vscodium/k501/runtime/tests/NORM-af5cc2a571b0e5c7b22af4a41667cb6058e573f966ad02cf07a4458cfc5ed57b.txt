CC = gcc
CFLAGS = -O2 -I./include -Wall -Wextra -Werror
LDFLAGS = -lcrypto
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = k501_alpha

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f src/*.o $(EXEC)