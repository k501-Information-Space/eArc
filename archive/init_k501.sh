#!/bin/bash
# K501 Little Alpha - Workspace Generator

echo "[K501] Initiating deterministic workspace generation..."

# 1. Generate Directory Tree
mkdir -p k501_alpha/{src,include,storage,docs/input}
cd k501_alpha || exit

# 2. Scaffold Canonical C Source Files
touch src/qh_algebra.c \
      src/qh_core.c \
      src/frame_engine.c \
      src/hard_index.c \
      src/dynamic_cage.c \
      src/ingestion.c \
      src/main.c

# 3. Scaffold Header Files
touch include/qh_algebra.h \
      include/qh_core.h \
      include/hard_index.h \
      include/dynamic_cage.h \
      include/ingestion.h

# 4. Initialize Storage Manifold
touch storage/frames.ndjson
touch storage/index.dat

# 5. Generate Makefile for gcc Compilation
cat << 'EOF' > Makefile
CC = gcc
CFLAGS = -O2 -I./include -Wall -Wextra -Werror
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = k501_alpha

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f src/*.o $(EXEC)
EOF

echo "[K501] Directory structure locked. Makefile generated."
echo "[K501] Launching VSCodium..."

# 6. Launch VSCodium in the generated workspace
codium .