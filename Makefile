CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -Werror -O0 -g
BIN     := bin/cat-lite
SRC     := src/cat-lite.c

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN) /etc/hosts

clean:
	rm -rf bin
