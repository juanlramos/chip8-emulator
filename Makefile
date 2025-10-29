CC = g++
CFLAGS = -I src -pthread
LDFLAGS = -lSDL2 -lm
SRC = $(wildcard src/*.cpp)
TARGET = chip8

.PHONY: all build run clean debug release

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run: build
	@if [ -z "$(ROM)" ]; then \
		echo "Usage: make run ROM=roms/TETRIS [ARGS=\"--scale 50\"]"; exit 1; \
	fi
	./$(TARGET) $(ROM) $(ARGS)

debug:
	$(CC) $(SRC) $(CFLAGS) -g $(LDFLAGS) -o $(TARGET)

release:
	$(CC) $(SRC) $(CFLAGS) -O2 -march=native $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
