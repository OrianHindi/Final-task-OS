CC=gcc
FLAGS = -Wall -g


all:  client server

client: client.c
	$(CC) $(FLAGS) -o client client.c

server: server.c
	$(CC) $(FLAGS) -o server server.c

.PHONY: clean

clean:
	rm -f client server
