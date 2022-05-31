.PHONY: all run clean
CC = gcc
GG = g++
FLAGS= -pthread
HEADERS = 
all: main1 client1 guard singleton reactor clientr

main1: main1.o
	$(CC) $< -o main1 $(FLAGS)

client1: client1.o
	$(CC) $< -o client1 

guard: 
	$(GG) guard.cpp -o guard $(FLAGS)

singleton: 
	$(GG) singleton.cpp -o singleton $(FLAGS)

reactor: pollserver.o
	$(CC) $<  -o reactor $(FLAGS)

clientr: pollclient.o
	$(CC) $<  -o clientr $(FLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f *.o main1 client1 guard singleton reactor clientr