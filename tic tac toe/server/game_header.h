#ifndef _HEADER
#define _HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define START_GAME 0
#define PLAYING_GAME 1
#define END_GAME 2
#define NO_SYMBOL 0
#define X 1
#define O 2
#define NO_INPUT 0
#define LOSS 1
#define WIN 2
#define DRAW 1
#define W_NO 0
#define PLAYER1_TURN 1
#define PLAYER2_TURN 2

typedef struct playerinfo
{
	short int sign;
	short int game_stat;
	int fd;
	short int next_turn;
	short int result;
	short int counter;
	
}playerinfo;
typedef struct gameinfo
{
	short int array[9];
	short int turn;
	
	
	
}gameinfo;

void start_game(gameinfo *game,playerinfo *player1,playerinfo *player2);
int  check_input(gameinfo *game,char *c,playerinfo *player);
int game_result(gameinfo *game,playerinfo *player);
int playing_game(gameinfo *game,playerinfo *player);
void ending_game(gameinfo *game,playerinfo *player1,playerinfo *player2);


#endif
