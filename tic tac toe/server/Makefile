cc=g++
cflag=-c -g 

all: gameexe server

gameexe: game.o game_header.o
	$(cc) -o gameexe game.o game_header.o
game.o: game.cpp game_header.h
	$(cc) $(cflag) game.cpp
game_header.o: game_header.cpp game_header.h
	$(cc) $(cflag) game_header.cpp
server: server.o server_header.o
	$(cc) -o server server.o server_header.o
server.o: server.cpp server_header.h
	$(cc) $(cflag) server.cpp
server_header.o: server_header.cpp server_header.h
	$(cc) $(cflag) server_header.cpp
clean:
	rm -rf *.o server gameexe 
	
