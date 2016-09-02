#include"game_header.h"

void start_game(gameinfo *game,playerinfo *player1,playerinfo *player2)
{
	int len,activity;
	
	player1->sign=X;
	player2->sign=O;
	player1->next_turn=player2->sign;
	player2->next_turn=player1->sign;
	player1->counter=5;
	player2->counter=4; 
	if(len=send(player1->fd,"assigned X first",17,0)!=17)
		printf("send failed\n");
	else
		printf("send assigned X\n");

	if(len=send(player2->fd,"assigned O last",16,0)!=16)
		printf("Send failed\n");
	else
		printf("send assigned O\n");
		
}

int  check_input(gameinfo *game,char *c,playerinfo *player)

{
	
	int pos=*c-'0';
	printf("%d\n",pos);
	if(game->array[pos]==NO_INPUT )
	{
		game->array[pos]=player->sign;
		return 1;
	}
	else
	{
		printf("player with sign %d has given invalid input.\n",player->sign);
		return -1;

	}
}
int game_result(gameinfo *game,playerinfo *player)
{
	if(game->array[0]==player->sign && game->array[1]==player->sign && game->array[2]==player->sign)
	{	
		
		return WIN;
	}
	else if(game->array[3]==player->sign && game->array[4]==player->sign && game->array[5]==player->sign)
	{	
		
		return WIN;
	} 
	else if(game->array[6]==player->sign && game->array[7]==player->sign && game->array[8]==player->sign)
	{	
		
		return WIN;
	} 
	else if(game->array[0]==player->sign && game->array[3]==player->sign && game->array[6]==player->sign)
	{	
		
		return WIN;
	} 
	else if(game->array[1]==player->sign && game->array[4]==player->sign && game->array[7]==player->sign)
	{	
		
		return WIN;
	} 
	else if(game->array[2]==player->sign && game->array[5]==player->sign && game->array[8]==player->sign)
	{	
		
		return WIN;
	} 
	else if(game->array[0]==player->sign && game->array[4]==player->sign && game->array[8]==player->sign)
	{	
		
		return WIN;
	} 
	else if(game->array[2]==player->sign && game->array[4]==player->sign && game->array[6]==player->sign)
	{	
		
		return WIN;
	} 	
	else 
	{
		if(player->counter ==0)
		{
			return DRAW;
		}
		else if(player->counter>0)
		{
			return W_NO;
		}
	}
}	





 
	
int playing_game(gameinfo *game,playerinfo *player)
{
	char buf[10];
	int received,input_check,result;
	if(received=recv(player->fd,buf,sizeof(buf),0)==-1)
	{
		printf("Error in recv.\n");
		return -1;
	}
		
	if(buf[0]=='I')
	{
		if(buf[2]>=48 && buf[2]<=56)
		{
			if(input_check=check_input(game,&buf[2],player)==-1)
			{
				game->turn=game->turn;
				return -2;
			}	
			else
			{
				
	
				game->turn=player->next_turn;
				(player->counter)--;
				player->result=game_result(game,player);
				if(player->result==WIN)
					return END_GAME ;
				else if(player->result==DRAW)
					return END_GAME;
				else
					return PLAYING_GAME;
			}
				
				
				
				
				
		}
		else
		{
			printf("Char is not number.\n");
			return -2;
		}
	}
	else
	{
		printf("Not valid command.\n");
		return -2;
	}
	
}
	
void ending_game(gameinfo *game,playerinfo *player1,playerinfo *player2)
{
	int i;
	if(player1->result==WIN)
	{
		printf("Player1 won\n");
		if(i=send(player1->fd,"Won",3,0)!=3)
		{
			printf("send");
		}	
		if(i=send(player2->fd,"Lost",4,0)!=4)
		{
			perror("send");
		}
	}	
	else if(player2->result==WIN)
	{
		printf("player 2 won\n");
	
		if(i=send(player2->fd,"Won",3,0)!=3)
		{
			perror("sned");
		}
		if(i=send(player1->fd,"Lost",4,0)!=4)
		{
			perror("send");
		}
	}
	else if(player1->result==DRAW || player2->result==DRAW)
	{
		printf("Draw \n");
		send(player1->fd,"Draw",4,0);
		send(player2->fd,"Draw",4,0);
	}	

}

