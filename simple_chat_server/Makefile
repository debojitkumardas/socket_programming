CC=gcc
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Werror -Wextra -g -I . $(DEFFLAGS)

SRC=$(wildcard *.c)
HDR=$(patsubst %.c, %.d, $(SRC))
OBJ=$(patsubst %.c, %.o, $(SRC))
BIN=tcp_client tcp_server

all: $(BIN)

tcp_server: $(filter-out tcp_client.o, $(OBJ))
	$(CC) $(CFLAGS) -o $@ $^

tcp_client: $(filter-out tcp_server.o, $(OBJ))
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(HDR) $(OBJ) $(BIN)
