// Rahul Parikh
// Binary Heap implementation


// Heap class
#include<iostream>
#include<vector>

using namespace std;

class Heap
{
	public:
		Heap();
		~Heap();
		int delete_min();
		void print()const;
		void insert(int key);
		int size();
		
	private:
		vector<int> data;
		int parent(int child);
		int left(int parent);
		int right(int parent);
		void heapifyup(int index);
		int heapifydown(int index);
		
	
};

// constructor of Heap class
Heap::Heap()
{
	
}

// destructor of Heap class
Heap::~Heap()
{
	
}

// size method will return the size of the Heap
int Heap::size()
{
	return data.size();
}

// parent method will return the parent of the child
// return -1 if parent is out of bound
int Heap::parent(int child)
{
	if(child!=0)
	{
		int parent=(child-1)>>1;
		if(parent <size())
			return parent;
		else
			return -1;
	}
	return -1;
	
}

// left will return the left child index of parent
// return -1 if child is out of bound
int Heap::left(int parent)
{
	int child=(parent<<1)+1;
	return child<this->size()?child:-1;
}

// right will return the right child index of parent
// return -1 if child is out of bound
int Heap::right(int parent)
{
	int child=(parent<<1)+2;
	return child<this->size()?child:-1;
}

// heapifyup will check heap property on parent of every child recursively
void Heap::heapifyup(int index)
{
	int par=parent(index);
	if(par>=0 && data[par]>data[index])
	{
		int temp=data[par];
		data[par]=data[index];
		data[index]=temp;
		heapifyup(par);
	}
}

// heapifydown will check heap property on both child of indexx recursively
int Heap::heapifydown(int index)
{
	int lchild=left(index);
	int rchild=right(index);
	int smallest=index;
	if(lchild>0  && data[lchild]<data[smallest])
	{
		smallest=lchild;
		
	}
	if(rchild>0 && data[rchild]<data[smallest])
	{
		smallest=rchild;
		
	}
	if(smallest!=index)
	{
		int temp=data[index];
		data[index]=data[smallest];
		data[smallest]=temp;
		heapifydown(smallest);
	}
}

// delete_min method will remove first element and replace it with last element 
// check heap property on first element recursively
int Heap::delete_min()
{
	int min=data.front();
	data[0]=data[data.size()-1];
	data.pop_back();
	heapifydown(0);
	return min;
}
void Heap::insert(int key)
{
	data.push_back(key);
	heapifyup(size()-1);
	
}
void Heap::print()const
{
	for(int i=0;i<data.size();i++)
		cout<<data[i]<<" ";
	cout<<endl;
	
}


int main()
{
	int arr[10]={2,9,57,3,1,200,-1,-9,-10,5};
	Heap min_heap;
	for(int i=0;i<10;i++)
		min_heap.insert(arr[i]);
	for(int i=0;i<10;i++)
	{
		int temp=min_heap.delete_min();
		cout<<temp<<" ";
	}
}