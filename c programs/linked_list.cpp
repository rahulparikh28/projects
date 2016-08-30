#include<stdio.h>
#include<stdlib.h>

#include<string.h>
typedef struct node
{
	int num;
	struct node *next;
}node;
node head,head1;
typedef struct string_value
{
	int strlen; 
	char *ptr;
	
}string_value;
void insert_node(node *,int );
void print(node *);
void delete_node(node *,int );
void ordered_list_insert(node *,int);
void reverse_list(node *);
void pointer(int **);

char * string(char **,int *);
int main()
{
	char *c[]={"rahul", "dhairya","muma", "papa","ishan"};
	int p,*q,i[2];
	node *head5=NULL;
	char  *str;
	head.num=0;
	head.next=NULL;
	head.num=13;
	head.next=NULL;
	insert_node(head5,30);
	
	insert_node(head5,40);

	insert_node(head5,50);
	
	print(head5);
	delete_node(&head,50);
	printf("\n");
	print(&head);
	printf("\n");
	ordered_list_insert(&head1,40);
	ordered_list_insert(&head1,30);
	ordered_list_insert(&head1,50);
	ordered_list_insert(head1.next,12);
	ordered_list_insert(&head1,1200);
	print(&head1);
	delete_node(&head1,1200);
	printf("\n");
	print(&head1);
	reverse_list(&head1);
	printf("\n");
	print(&head1);
	printf ("\n");
	p=98;
	q=&p;
	printf("&q is %d %d\n",&q,p);
	pointer(&q);
	printf("%d",p);
	str=string(c+4,&p);
	printf(" strlen=%d string=%s",str,p);
	
	return 1;
	
	
}

void insert_node(node *head,int num)
{
	if(head->next==NULL)
	{
		
		head->next=(node *)malloc(sizeof(node));
		head->next->num=num;
		head->next->next=NULL;
	}
	else 
	{
		
		node *current=head->next;
		node *trailcurrent=head;
		
		while(current!=NULL )
		{
			current=current->next;
			trailcurrent=trailcurrent->next;
		}
		current=(node *)malloc(sizeof(node));
		current->num=num;
		current->next=NULL;
		trailcurrent->next=current;
		
		
	}
	
}
void print(node *head)
{
	node * temp;
	temp=head->next;
	while(temp)
	{
		printf("%d->",temp->num);
		temp=temp->next;
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
			trailcurrent->next=NULL;
			free(current);
		}
		else 
		{
			trailcurrent->next=current->next;
			free (current);
		}
	}	
}
void ordered_list_insert(node *head,int num)
{
	node *current ,*trailcurrent,*new_node;
	bool found=false;
	
	new_node=(node * )malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	current=head->next;
	trailcurrent=head;
	
	if(current==NULL)
	{
		trailcurrent->next=new_node;
		
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
		}
		else 
		{
			trailcurrent->next=new_node;
			new_node->next=current;
		}
	}
}
void reverse_list(node *head)
{
	printf("inside reverse list\n");
	node *p,*q,*r;
	p=head->next->next;
	q=head->next;
	r=NULL;
		
	
	while(p)
	{
		q->next=r;
		r=q;
		q=p;
		p=p->next;
		
		
	}
	q->next=r;
	head->next=q;
	
	//printf("%d\n",q->next->num);
	//return q;
	
}
void pointer(int **ptr)
{
	int temp;
	printf("*ptr is %d\n",(*ptr));
	
}
char *string(char **ptr,int *t)
{
	int i;
	i=strlen(*ptr);
	//string_value str;
	//str.strlen=i;
	//str.ptr=*ptr;
	*t=i;
	return *ptr;
}


