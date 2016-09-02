#include"client_header.h"



		

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[100];
	struct addrinfo hints, *servinfo, *p;
	int rv,msglen,activity;
	char s[INET6_ADDRSTRLEN];
	playerinfo player;
	fd_set rd_fds,w_fds,master;
	FD_ZERO(&master);
	//FD_ZERO(&w_fds);
	//if (argc != 2) {
	//	fprintf(stderr,"usage: client hostname\n");
	//	exit(1);
	//}
	

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;


	if ((rv = getaddrinfo("127.0.0.1", argv[1], &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}


	// loop through all the results and connect to the first we can
	

	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}


		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
		}
		if (p == NULL) {
			fprintf(stderr, "client: failed to connect\n");
			return 2;
		}
		player.fd=sockfd;
		player.game_stat=START_GAME;
		player.turn=0;
		player.sign=0;
		
		FD_SET(player.fd,&master);
		
		freeaddrinfo(servinfo);
		
		while(1)
		{
			rd_fds=master;
			
			if(select(player.fd+1,&rd_fds,NULL,NULL,NULL)==-1)
			{
				printf("Error in select\n");
				break;
			}
			if(FD_ISSET(player.fd,&rd_fds))
			{
				//printf("received something\n");
				if(player.game_stat==0)
				{
					printf("starting game.\n");
					
					if(player.sign==0 && player.turn==0)
					{
						//printf("turn sign.\n");
						
						start_game(&player);
					}
				
				
				}
				
				else if(player.game_stat==PLAYING_GAME)
				{
					//int val;
					//printf("val1=%d\n",val);
					int val=playing_game(&player);
					if(val==1)
					{
						break;
					}
					else if(val==0)
						break;
					else 
					{
						//printf("val=%d\n",val);
					}				
				}
			}
		}

		close(sockfd);
}

