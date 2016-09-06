// stack_implementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"stack.h"

typedef struct treenode
{
	int data;
	struct treenode *next;
}treenode;
int main()
{
	int data;
	stack<int> stack1,stack2;
	treenode node1, node2,node3;
	node1.data = 40;
	node2.data = 30;
	//stack<treenode> stack3;
	//stack3.push(node1);
	//stack3.push(node2);
	//node3 = stack3.pop();
	//printf("%d\n", node3.data);
	//node3 = stack3.pop();
	//printf("%d\n", node3.data);

	stack1+40;
	stack1 + 80;
	stack1 + 90; 
	stack1 + 110;
	stack1 + 200;
	stack1 + 10;
	data=--stack1;
	data = --stack1;
	data = --stack1;
	data = --stack1;

	stack2 = stack1;

    return 0;
}

