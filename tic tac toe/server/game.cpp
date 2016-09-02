#include"game_header.h"
int main (int argc,char *argv[])
{
	if(argc<2)
	{
		printf("not valid argumnet.\n");
		exit(0);
	}
	playerinfo player1,player2;
	gameinfo game;
	int activity,fd_max,received;
	char buf[100];
	player1.fd=atoi(argv[1]);
	player2.fd=atoi(argv[2]); 
	
	fd_set rd_fds,master;
	FD_ZERO(&master);
	memset(&game,0,sizeof(game));
	FD_SET(player1.fd,&master);
	FD_SET(player2.fd,&master);
	if(player1.fd>player2.fd)
		fd_max=player1.fd;
	else
		fd_max=player2.fd;
	
	player1.game_stat=START_GAME;
	player2.game_stat=START_GAME;
	start_game(&game,&player1,&player2);
	printf("fd1=%d fd2=%d \n",player1.fd,player2.fd);
	
	while(1)
	{
		rd_fds=master;
		if(select(fd_max+1,&rd_fds,NULL,NULL,NULL)==-1)
		{
			perror("Select\n");
			exit(4);
		}
		if(FD_ISSET(player1.fd,&rd_fds))
		{
			
			
			if(player1.game_stat==START_GAME)
			{
				printf("player1 startng game.\n");
				memset(buf,'\0',sizeof(buf));
				received=recv(player1.fd,buf,sizeof(buf),0);
				if(strcmp(buf,"player set")==0)
				{
					player1.game_stat=PLAYING_GAME;
					send(player1.fd,"game set",9,0);
					printf("player1 is ready to play.\n");
				}

			}
			else if(player1.game_stat==PLAYING_GAME)
			{
				if(game.turn=PLAYER1_TURN )
				{
	
				
					int status=playing_game(&game,&player1);
					if(status==-2)
					{
						send(player1.fd,"invalid msg",12,0);
					}
					else if(status==-1)
					{
						send(player1.fd,"recv failed",12,0);
						
					}
					else if(status==PLAYING_GAME)
					{
						send(player1.fd,"msg received",13,0);
						send(player2.fd,"your turn",10,0);
						player1.game_stat=status;
					}
					else if(status==END_GAME)	
					{
						printf("ending game.\n");
						ending_game(&game,&player1,&player2);
						break;	
					}	
				}
				else
				{
	 
 					recv(player1.fd,buf,sizeof(buf),0);
					send(player1.fd,"Not your turn",13,0);
				}		
				
				
			}
							
		}
		if(FD_ISSET(player2.fd,&rd_fds))
		{
			
			if(player2.game_stat==0)
			{
				printf("player2 starting game.\n");
				memset(buf,'\0',sizeof(buf));
				received=recv(player2.fd,buf,sizeof(buf),0);
				if(strcmp(buf,"player set")==0)
				{
					player2.game_stat=PLAYING_GAME;
					send(player2.fd,"game set",9,0);
					printf("player 2 is ready to play.\n");
				}


			}
			else if(player2.game_stat==PLAYING_GAME)
			{
				if(game.turn==PLAYER2_TURN )
				{
					int status=playing_game(&game,&player2);
					if(status==-2)
					{
						send(player2.fd,"invalid msg",12,0);
					}
					else if(status==-1)
					{
						send(player2.fd,"recv failed",12,0);
				
					}
					else if(status==PLAYING_GAME)
					{
						send(player2.fd,"msg received",13,0);
						send(player1.fd,"your turn",10,0);
						player2.game_stat=status;
					}
					else if(status==END_GAME)
					{
						printf("ending game.\n");
						ending_game(&game,&player1,&player2);
						break;
					}
				}
				else 
				{
					recv(player2.fd,buf,sizeof(buf),0);
					send(player2.fd,"Not your turn",13,0);
				
				}
			}
			
		}
	}
	close(player1.fd);
	close(player2.fd);
	exit(0);
}
