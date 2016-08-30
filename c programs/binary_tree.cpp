#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int num;
	struct node *left,*right;
}node;
void insert_node(node **,int);
bool search(node **,int);
int main()
{
	int const *ptr;
	int p=9,q=10;
	node *root=NULL,*root1=NULL;
	bool found;
	//root=(node *)malloc(sizeof(node));
	//root->num=50;
	insert_node(&root1,50);
	printf("some\n");
	insert_node(&root,60);
	insert_node(&root,70);
	insert_node(&root,65);
	insert_node(&root,30);
	insert_node(&root,34);
	insert_node(&root,31);
	found=search(&root,34);
	if(found==true)
		printf("found");
	printf("%d",root->right->num);
	ptr=&p;
	*ptr =10;
	printf("\nptr=%d",*ptr);
	return 1;
}
void insert_node(node **root,int num)
{
	
	
	
	if(*root==NULL)
	{
		
		*root=(node *)malloc(sizeof(node));
		(*root)->num=num;
		(*root)->right=NULL;
		(*root)->left=NULL;
		
	}
	else
	{
		if(num>(*root)->num)
			insert_node(&(*root)->right,num);
		else
			insert_node(&(*root)->left,num);
	}
	
}
bool search(node **root,int num)
{
	bool found=false;
	if(*root==NULL)
	{
		return found;
		
	}
	else{
		if((*root)->num<num)
			search(&(*root)->right,num);
		else if((*root)->num>num)
			search(&(*root)->left,num);
		else 
			return true;
	}
}
