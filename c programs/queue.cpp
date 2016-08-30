#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#define char_num 256
typedef struct node
{
	int num;
	struct node * next;
	
}node;
typedef struct queue{
	struct node *front,*rear;
}queue;

void print(queue **);
void add_queue(queue **,int);
node * dequeue(queue **);
int factorial(int);
unsigned int reverseBits(unsigned int);
bool detectloop(node **);
char first_non(char *);
int main ()
{
	int p[3]={2,1,3},*r;
	unsigned int q=0xffffffff;
	//p >>=3;
	q >>=3;
	r=p;
	r=r+2;
	*r--=5;
	bool t;
	node *ptr=NULL;
	ptr=(node *)malloc(sizeof(node));
	ptr->num=2;
	ptr->next=(node *)malloc(sizeof(node));
	ptr->next->num=4;
	ptr->next->next=ptr;
	printf("%d %d\n",*r,r);
	printf("%d\n",*r);
	r++;
	printf("%d\n",*r);
	queue *root,root1;
	//root->front=NULL;
	//root->rear=NULL;
	root1.front=NULL;
	root1.rear=NULL;
	root=&root1;
	//printf("in main \n");
	add_queue(&root,18);
	add_queue(&root,13);
	add_queue(&root,15);
	add_queue(&root,12);
	add_queue(&root,14);
	add_queue(&root,11);
	add_queue(&root,10);
	add_queue(&root,17);
	add_queue(&root,500);
	add_queue(&root,100);
	
	p[0]=factorial(6);
	printf("%x",q);
	q=reverseBits(q);
	printf("\n%x",q);
	t=detectloop(&ptr);
	if(t==true)
		printf("true\n");
	char s[256]="geeks for geeks";
	char c=first_non(s);
	printf("%c\n",c);
	return 1;
	
}

void add_queue(queue **root,int num)
{
	//printf("in add \n");
	node *new_node;
	new_node=(node * )malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	if((*root)->rear==NULL)
	{
		(*root)->rear=new_node;
		(*root)->front=new_node;
	}
	else 
	{
		(*root)->rear->next=new_node;
		(*root)->rear=new_node;
	}
}
void print(queue **root)
{
	//printf("in print");
	node *temp=(*root)->front;
	while(temp!=NULL)
	{
		printf("%d->",temp->num);
		temp=temp->next;
	}
	printf("\n");
}

node * dequeue(queue **root)
{
	node * temp;
	if((*root)->front==NULL)
		return NULL;
	else 
	{
		temp=(*root)->front;
		(*root)->front=(*root)->front->next;
	}
	if((*root)->front==NULL)
		(*root)->rear=NULL;
	return temp;
	
}

int factorial(int n)
{
	if (n==0)
	{
		return 0;
		
	}
	else if(n==1)
		return 1;
	else
		return factorial(n-1)+factorial(n-2);
}
void q_sort(node **start,node **end)
{
	node *pivot=(*start);
	node *cur,*pre,*less,*more;
	
	pre=cur;
	
	
}
unsigned int reverseBits(unsigned int num)
{
    unsigned int count = sizeof(num) * 8 - 1;
    unsigned int reverse_num = num;
     
    num >>= 1; 
    while(num)
    {
       reverse_num <<= 1;       
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}
bool detectloop(node **head)
{
	 node  *slow_p = *head, *fast_p = *head;
 
    while (slow_p && fast_p && fast_p->next)
    {
        slow_p = slow_p->next;
        fast_p  = fast_p->next->next;
 
        /* If slow_p and fast_p meet at some point then there
           is a loop */
        if (slow_p == fast_p)
        {
            //removeLoop(slow_p, list);
 
            /* Return 1 to indicate that loop is found */
            return true;
        }
    }
 
    /* Return 0 to indeciate that ther is no loop*/
    return false;
}
char first_non(char *s)
{
	int *count=(int *)malloc(sizeof(int)*256);
	int len=strlen(s),i,index=0;
	for(i=0;i<256;i++)
	{
		count[i]=0;
	}
	for(i=0;i<len;i++)
	{
		count[s[i]]++;
		
	}
	for(i=0;i<len;i++)
	{
		if(count[s[i]]==1)
		{
			return s[i];
		}
	}
	//printf("%d",count['g']);
	return 0;
}