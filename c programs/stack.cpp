#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int num;
	struct node *next;
}node;

class base 
{
	private:
	int heaight,weight,width;
	public:
	base();
	virtual ~base();
	base operator+(const base first);
	int geth();
	int getw();
	int getwi();
	
	
};
base::base()
{
	heaight=9;
	weight=10;
	width=90;
	printf("inside the constructor of base\n");
}
base::~base()
{
	printf("inside the destructor of the base\n");
}
int base::geth()
{
	return heaight;
}
int base:: getw()
{
	return weight;
	
}
int base::getwi()
{
	return width;
}
base base::operator+(const base first)
{
	base temp;
	temp.heaight=this->heaight+first.heaight;
	temp.weight=this->weight+first.weight;
	temp.width=this->width+first.width;
	return temp;
}
class derived :public base
{
	private:
	int x;
	int y;
	public :
	derived();
	~derived();
	
};
derived:: derived ()
{
	x=0;
	y=0;
	printf("inside the constructor of derived\n");
}
derived::~derived()
{
	printf("inside the destructor of derived\n");
}

node *push(node *, int);
node *pop(node *);
void func(base *);
int main()
{
	//base first,two,three;
	derived four;
	//three=first+two;
	//printf("%d\n",three.getwi());
	node *sp;
	sp=NULL;
	sp=push(sp,2);
	sp=push(sp,3);
	sp=push(sp,4);
	sp=push(sp,9);
	
	printf("%d\n",sp->num);
	sp=pop(sp);
	sp=pop(sp);
	//sp=pop(sp);
	//sp=pop(sp);
	//printf("%d\n",sp->num);
	base *ptr=new derived;
	func(&four);
	//free(ptr);
	delete ptr;
	return 1;
	
}
node *push(node *sp,int num)
{
	node *new_node;
	new_node=(node *)malloc(sizeof(node));
	new_node->num=num;
	new_node->next=NULL;
	
	if(sp==NULL)
	{
		sp=new_node;
		return sp;
		
	}
	else
	{
		new_node->next=sp;
		sp=new_node;
		return sp;
	}
}
node *pop(node *sp)
{
	node *temp;
	if(sp==NULL)
	{
		printf("stack is empty\n");
	}
	else
	{
		temp=sp;
		sp=sp->next;
		free(temp);
		return sp;
	}
}
void func (base *ptr)
{
	
}