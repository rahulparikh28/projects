#include"server_header.h"



int main (int argc,char *argv[])
{
	int sockfd,newfd,newfd1;
	struct addrinfo hints,*servinfo,*p;
	struct sockaddr_storage their_addr,their_addr1; // connector's address information
	socklen_t sin_size;
	int len,rv,pid;
	struct sigaction sa;
	queue *online_queue;
	online_queue=(queue *)malloc(sizeof(queue));
	online_queue->first=NULL;
	online_queue->last=NULL;
	char *c=(char *)malloc(sizeof(char )*100);
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	

	if ((rv = getaddrinfo(NULL,"3000" , &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);
	
	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
			
	if (listen(sockfd, 10) == -1) {
		perror("listen");
		exit(1);
	}
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	while(1)
	
	{
		sin_size = sizeof their_addr;
		char c[32],c1[32];
		int fd1,fd2;
		newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

		push(&online_queue,newfd);
		if(online_queue->first->next!=NULL && online_queue->first!=NULL)
		
		{
			fd1=pop(&online_queue);
			fd2=pop(&online_queue);
			
			
			snprintf(c,32,"%d",fd1);
		
			snprintf(c1,32,"%d",fd2);
			

			if (newfd == -1) {
			perror("accept");
			continue;
			}
			
			if(newfd1==-1)
			{
				perror("accept");
				continue;
			}
			pid=fork();
			if(pid<0)
			{
				printf("fork failed.\n");
			}
			else if(pid==0)
			{
			
				execl("./gameexe","./gameexe",c,c1,NULL);
			}
		
			close(fd1);
			close(fd2);
		
		}
		
	
	}
}
