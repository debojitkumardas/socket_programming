CC=gcc
CFLAGS=-Wall -Werror -Wextra -g

SRC=$(wildcard *.c)
BIN=$(patsubst %.c, %, $(SRC))

all: $(BIN)

clean:
	rm $(BIN)
