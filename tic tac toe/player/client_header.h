#ifndef _CLIENT_HEADER
#define _CLIENT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define START_GAME 0
#define PLAYING_GAME 1
#define END_GAME 2
#define NO_SYMBOL 0
#define X 1
#define O 2
#define W_PLAYER1 1
#define W_PLAYER2 2
#define W_NO 0
#define MY_TURN 1
#define OPPONENT_TURN 2

typedef struct playerinfo
{
	short int game_stat;
	short int fd;
	short int sign;
	short int turn;
	short int counter;  
}playerinfo;
void start_game(playerinfo *player);
int playing_game(playerinfo *player);

#endif

