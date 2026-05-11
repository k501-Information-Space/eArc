CC = gcc

CFLAGS = -Iinclude -Wall -O2

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/obj/%.o,$(SRC))

TARGET = build/bin/k501_core.bin

LOGDIR = build/logs

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ)

build/obj/%.o: src/%.c
	@mkdir -p build/obj
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -DDEBUG
debug: clean all

release: clean all

clean:
	rm -f build/obj/*.o
	rm -f $(TARGET)

logs:
	@mkdir -p $(LOGDIR)

run: all
	./$(TARGET)

info:
	@echo "Sources : $(SRC)"
	@echo "Objects : $(OBJ)"
	@echo "Target  : $(TARGET)"