//  Rahul Parikh
//  This is disjoint set implementation
//  union set method is implemented by union and rank


// disjoint set node
typedef struct dis_node
{
	struct dis_node* parent;
	int data;
	int rank;
	int size;
}dis_node;

// makeset method take num as an arguent and create array of disjoint set node of size num
// return pointer to that array
dis_node* makeset(int num)
{
	dis_node* array=new dis_node[num];
	for(int i=0;i<num;i++)
	{
		array[i].parent=&array[i];
		array[i].data=i;
		array[i].rank=0;
		array[i].size=1;
	}
	return array;
}

// findset method that take two arguments as input 
// array is a pointer to the disjoint set
// findset method will return parent of key
int findset(dis_node* array,int key)
{
	if(array[key].parent==&array[key])
		return array[key].data;
	else
	{
		int data=findset(array,(array[key].parent)->data);
		return data;
	}
}

// unioun set takes pointer to the array and two keys as arguments
// it will make union of two sets by comparing the ranks of two sets
// set with the higher rank will be set as a parent to the lower rank set
void unionset(dis_node* array,int key1,int key2)
{
	
		int x=findset(array,key1);
		int y=findset(array,key2);
		if(x==y)
			return;
		else
		{
			if(array[x].rank>array[y].rank)
			{
				array[y].parent=&array[x];
				array[x].size+=array[y].size;
			}
			else if(array[y].rank>array[x].rank)
			{
				array[x].parent=&array[y];
				array[y].size+=array[x].size;
			}
			else
			{
				array[y].parent=&array[x];
				array[x].rank++;
				array[x].size+=array[y].size;
			}
		}
}


int main()
{
	dis_node* array1=NULL;
	array1=makeset(10);            // make set of 10 nodes
	unionset(array1,1,2);          // make union of key 1 and 2 
	                               // after this step 2's parent will be 1
	unionset(array1,2,3);          // after this union operation 3's parent will be 1 as 2's parent is 1 
	unionset(array1,7,9);
	int key=findset(array1,3);     // find operation will return 3's parent which is 1
	cout<<key;
}