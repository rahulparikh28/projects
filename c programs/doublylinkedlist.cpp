#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int num;
	struct node *next,*pre;
	
}node;
void insert_node(node **,int);
void print(node **);
void inorder_insert(node **,int);
void delete_node(node **,int );
int main()
{
	node *head;
	head=NULL;
	insert_node(&head,40);
	insert_node(&head,50);
	insert_node(&head,20);
	insert_node(&head,780);
	insert_node(&head,12000);
	print(&head);
	inorder_insert(&head,80);
	printf("\n");
	print(&head);
	inorder_insert(&head,30);
	printf("\n");
	print(&head);
	
	inorder_insert(&head,13000);
	printf("\n");
	print(&head);
	delete_node(&head,30);
	delete_node(&head,13000);
	delete_node(&head,50);
	printf("\n");
	print(&head);
}
void insert_node(node ** head,int num)
{
	node *current,*new_node;
	current=*head;
	new_node=(node *)malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	new_node->pre=NULL;
	if (current==NULL)
	{
		*head=new_node;
		
	}
	else{
		while(current->next!=NULL)
		{
			current=current->next;
			
		}
		current->next=new_node;
		new_node->pre=current;
	}
}
void print(node **head)
{
	node *current;
	current =*head;
	while(current!=NULL)
	{
		printf("%d->",current->num);
		current=current->next;
		
	}
}
void inorder_insert(node **head,int num)
{
	bool found=false;
	node *current,*new_node,*trailcurrent;
	current=*head;
	trailcurrent=current;
	new_node=(node *)malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	new_node->pre=NULL;
	if(current==NULL)
	{
		current=new_node;
		
	}
	else if(num<=current->num)
	{
		new_node->next=current;
		current->pre=new_node;
		(*head)=new_node;
	}
	else{
		current=current->next;
		while(current!=NULL && found==false)
		{
			if(num<=current->num)
			{
				found=true;
				current->pre->next=new_node;
				new_node->pre=current->pre;
				new_node->next=current;
				current->pre=new_node;
			}
			else{
				current=current->next;
				trailcurrent=trailcurrent->next;
			}
		}
		if(found==false)
		{
			trailcurrent->next=new_node;
			new_node->pre=trailcurrent;
			
		}
	}
}
void delete_node(node **head,int num)
{
	bool found=false;
	node * current ,*trailcurrent,*temp;
	current=(*head);
	trailcurrent=current;
	if(current==NULL)
	{
		printf("List is empty.\n");
		
	}
	else if(current ->num==num)
	{
		temp=current;
		current->next->pre=NULL;
		current=current->next;
		*head=current ;
		free(temp);
		
	}
	else 
	{
		current=current->next;
		while(current!=NULL && found==false)
		{
			if(current->num==num)
			{
				found=true;
				temp=current;
				current->pre->next=current->next;
				current->next->pre=current->pre;
				free(temp);
				
			}
			else{
				current=current->next;
			}
		}
		if(found==false)
		{
			printf("node does not found.\n");
		}
	}
}