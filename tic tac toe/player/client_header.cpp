
#include"client_header.h"

void start_game(playerinfo *player)
{
	//printf("start game.\n");
	char buf[100];
	int msglen;
	int received=recv(player->fd,buf,sizeof(buf),0);
	if(strcmp(buf,"assigned X first")==0)
	{
		player->sign=X;
		player->turn=MY_TURN;
		player->counter=5;
		player->game_stat=PLAYING_GAME;
		if(msglen=send(player->fd,"player set",11,0)!=11)
		{
			printf("not\n");
		}
		
		printf("inside assigned X\n");
	}
	else if(strcmp(buf,"assigned O last")==0)
	{
		player->sign=O;
		player->turn=OPPONENT_TURN;
		player->counter=4;
		player->game_stat=PLAYING_GAME;
		if(msglen=send(player->fd,"player set",11,0)!=11)
		{
			printf("Not\n");
		}

		printf("inside assigned O\n");
	}
	else if(strcmp(buf,"first")==0)
	{
		player->turn=MY_TURN;
		printf("inside first\n");
	}
	else if(strcmp(buf,"last")==0)
	{
		player->turn=OPPONENT_TURN;
		printf("inside last\n");
	}
		

}
int playing_game(playerinfo *player)
{
	char buf[30],msg[30],c;
	int msglen;
	memset(buf,'\0',30);
	msglen=recv(player->fd,buf,30,0);
	if(msglen==0)
	{
		printf("connection lost\n");
		return 0;
	}
	
	if(strcmp(buf,"game set")==0  )
	{
		
		if(player->turn==MY_TURN)
		{
			

			printf("your turn\n");
			fgets(msg,30,stdin);
			msglen=strlen(msg);
			send(player->fd,msg,msglen,0);
			return -1;
		}
		else 
		{
			printf("Wait for your turn.\n");
			return 2;
		}
		
		
	}
	else if(strcmp(buf,"msg received")==0)
	{
		if(player->turn!=OPPONENT_TURN)
		{
			player->turn=OPPONENT_TURN;
			(player->counter)--;
			return -1;
		}
		//return -1;
		
	}
	else if(strcmp(buf,"your turn")==0 )
	{
		
		printf("your turn\n");
		fgets(msg,30,stdin);
		msglen=strlen(msg);
		send(player->fd,msg,msglen,0);
		return -1;
		
	}
	else if(strcmp(buf,"Won")==0)
	{
		printf("congratulations you won.\n");
		return 1;
	}
	else if(strcmp(buf,"Lost")==0)
	{
		printf("Sorry you lost.\n");
		return 1;
	}
	else if(strcmp(buf,"Draw")==0)
	{
		printf("the game is draw.\n");
		return 1;
	}	
	else if(strcmp(buf,"recv failed")==0)
	{
		printf("recv failed\n");
		return -1;
	}
	else if(strcmp(buf,"invalid msg")==0)
	{	
		
		fgets(msg,30,stdin);
		msglen=strlen(msg);
		send(player->fd,msg,msglen,0);
		return -1;
	}
}	

