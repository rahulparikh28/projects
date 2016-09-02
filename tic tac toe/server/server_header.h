#ifndef _SERVER_HEADER
#define _SERVER_HEADER

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

typedef struct queue_node
{
	int file_descriptor;
	struct queue_node *next;
}queue_node;
typedef struct queue
{
	queue_node *first;
	queue_node *last;
}queue;
void push(queue **node,int descriptor);
int pop(queue **node);
void sigchld_handler(int s);

#endif
