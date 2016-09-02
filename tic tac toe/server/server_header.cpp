#include"server_header.h"
void push(queue **node,int descriptor)
{
	if(*node!=NULL)
	{
		queue *current=*node;
		queue_node *newnode;
		newnode=(queue_node *)malloc(sizeof(queue_node));
		newnode->file_descriptor=descriptor;
		newnode->next=NULL;
		if(current->last ==NULL)
		{
			current->first=newnode;
			current->last=newnode;
		}
		else 
		{
			current->last->next=newnode;
			current->last=newnode;
		}
	}else 
	{
		printf("Cannot add to null queue.\n");
	}
	
}
int pop(queue **node)
{
	if(*node!=NULL)
	{
		int fd;
		queue *current=*node;
		queue_node *popnode;
		popnode=current->first;
		current->first=current->first->next;

		fd=popnode->file_descriptor;
		free(popnode);
		if(current->first==NULL)
		{
			current->last=NULL;
		}
		
		return fd;
	}
	return -1;
}
	
void sigchld_handler(int s)
{

	int saved_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

