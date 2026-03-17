CC = gcc
CFLAGS = -O3 -Wall -Wextra -I./include
LIBS = -lssl -lcrypto
OBJ = src/main.o src/qh_algebra.o src/qh_core.o src/frame_engine.o \
      src/dynamic_cage.o src/hard_index.o src/ingestion.o

k501_alpha: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f src/*.o k501_alpha