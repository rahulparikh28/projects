cc=g++
cflag=-c -g 

all: playerexe

playerexe: client.o client_header.o
	$(cc) -o playerexe client.o client_header.o
client.o: client.cpp client_header.h
	$(cc) $(cflag) client.cpp
client_header.o:client_header.cpp client_header.h
	$(cc) $(cflag) client_header.cpp
