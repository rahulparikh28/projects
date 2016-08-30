#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int num;
	struct node *next,*pre;
}node;
void insert_node(node *,int);
void insert_node_pos(node *,int ,int);
void print(const node *);
void inordered_list(node *,int );
void delete_node(node *,int);
int main ()
{
	node head,*temp,head1;
	head.num=0;
	head.next=NULL;
	head.pre=NULL;
	head1.num=0;
	head1.next=NULL;
	head1.pre=NULL;
	insert_node(&head,20);
	insert_node(&head,10);
	insert_node(&head,30);
	insert_node(&head,40);
	insert_node(&head,80);
	insert_node(&head,90);
	insert_node(head.next->next,30);
	temp=head.next->next;
	
	print(temp);
	printf("\n");
	insert_node_pos(&head,3,1200);
	print(&head);
	printf("\n");
	inordered_list(&head1,133);
	inordered_list(&head1,433);
	inordered_list(&head1,23);
	inordered_list(&head1,53);
	inordered_list(&head1,13376);
	inordered_list(&head1,134);
	print(&head1);
	delete_node(&head1,13376);
	printf("\n");
	print(&head1);
	return 1;
}
void insert_node(node *head,int num)
{
	node *current,*new_node,*trailcurrent;
	new_node=(node *)malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	new_node->pre=NULL;
	current=head->next;
	trailcurrent=head;
	if(current==NULL)
	{
		head->next=new_node;
		new_node->pre=head;
		
	}
	else 
	{
		while(current)
		{
			current=current->next;
			trailcurrent=trailcurrent->next;
			
		}
		trailcurrent->next=new_node;
		new_node->pre=trailcurrent;
		
	}
}
void insert_node_pos(node * head,int pos,int num)
{
	node *current,*trailcurrent,*new_node;
	new_node=(node*)malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	new_node->pre=NULL;
	current=head->next;
	trailcurrent=head;
	if(current==NULL)
	{
		printf("List is empty\n");
	}
	else
	{
		while(pos)
		{
			current=current->next;
			trailcurrent=trailcurrent->next;
			pos--;
			
		}
		current->next->pre=new_node;
		new_node->next=current->next;
		new_node->pre=current;
		current->next=new_node;	
		
	}
}
void print( const node *head)
{
	
	while(head)
	{
		printf("%d->",head->num);
		head=head->next;
	}
}
void inordered_list(node *head,int num)
{
	bool found=false;
	node *current, *trailcurrent ,*new_node;
	current=head->next;
	trailcurrent=head;
	new_node=(node*)malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	new_node->pre=NULL;
	if(current==NULL)
	{
		trailcurrent->next=new_node;
		new_node->pre=trailcurrent;
		
	}
	else 
	{
		while (current!=NULL && found==false)
		{
			if(current->num>=num)
			{
				found=true;
				break;
				
			}
			current =current->next;
			trailcurrent=trailcurrent->next;
		}
		if(current==NULL && found==false)
		{
			trailcurrent->next=new_node;
			new_node->pre=trailcurrent;
		}
		else 
		{
			new_node->pre=trailcurrent;
		new_node->next=current;
		current->pre=new_node;
		trailcurrent->next=new_node;
		}
		
	}
	
}
void delete_node(node * head,int num)

{
	node *current ,* trailcurrent;
	bool found=false;
	current=head->next;
	trailcurrent=head;
	if(current==NULL )
	{
		printf("List does not exist.\n");
		
	}
	else 
	{
		
		while(current!=NULL && found==false)
		{
			if(num==current->num)
			{
				found=true;
				break;
			}
			current=current->next;
			trailcurrent=trailcurrent->next;
		}
		
		if(current==NULL && found==false)
			printf("Node does not exist\n");
		
		else if (current->next==NULL && found==true)
		{
			current->pre->next=NULL;
			free(current);
		}
		else 
		{
			current->next->pre=current->pre;
			current->pre->next=current->next;
			free (current);
		}
	}	
}
