#pragma once
#include<iostream>
template<class type>
struct nodetype
{
	type data;
	struct nodetype *next;
};
template<class type>
class stack
{
public:
	void initialise_stack();
	type pop();
	void push(const type&);
	void destroy_stack();
	void operator+(const type& );
	type operator--();
	void operator=(const stack&);
	void copy_stack(const stack&);
	stack(const stack&);
	stack();
	~stack();
private:
	nodetype<type> *stack_top;
};

template<class type>
void stack<type>::initialise_stack()
{
	destroy_stack();
}
template<class type>
void stack<type>::destroy_stack()
{
	nodetype<type> *temp;
	while (stack_top != NULL)
	{
		temp = stack_top;
		stack_top = stack_top->next;
		free(temp);
	}

}
template<class type>
stack<type>::stack()
{
	stack_top = NULL;
}
template<class type>
stack<type>::~stack()
{
	destroy_stack();
}
template<class type>
stack<type>::stack(const stack& otherstack)
{
	copy_stack(otherstack);
}
template<class type>
void stack<type>::copy_stack(const stack& otherstack)
{
	nodetype<type> *temp,*last,*newnode;
	if (!stack_top)
	{
		destroy_stack();
	}
	temp = otherstack.stack_top;
	if (!temp)
	{
		stack_top = NULL;
	}
	else
	{
		newnode = (nodetype<type>*) malloc(sizeof(nodetype<type>));
		newnode->data = temp->data;
		newnode->next = NULL;
		stack_top = newnode;
		last = newnode;
		temp = temp->next;
		while (temp != NULL)
		{
			newnode = (nodetype<type>*) malloc(sizeof(nodetype<type>));
			newnode->data = temp->data;
			newnode->next = NULL;
			last->next = newnode;
			last = last->next;
			temp = temp->next;


		}
		
	}
	
}
template<class type>
void stack<type>::push(const type& data)
{
	nodetype<type> *newnode;
	
		
		newnode = (nodetype<type>*)malloc(sizeof(nodetype<type>));
		newnode->data = data;
		
		newnode->next = stack_top;
		stack_top = newnode;
	
}
template<class type>
type stack<type>::pop()
{
	nodetype<type> *temp;
	type data;
	temp = stack_top;
	stack_top = stack_top->next;
	data = temp->data;
	free(temp);
	return data;
}
template<class type>
void stack<type>:: operator+(const type& data)
{
	push(data);

}
template<class type>
type stack<type>:: operator--()
{
	type data;
	data=pop();
	return data;
}
template<class type>
void stack<type>:: operator=(const stack& otherstack)
{
	copy_stack(otherstack);

}