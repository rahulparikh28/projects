// Rahul Parikh
// Bidirectional Graph implementation

#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<cmath>

using namespace std;

// class of graph node
class graph_node
{
	public:
		list<int> edge;     // edge comprises all the direct links to other node
		
		int key;            // key is the identifier of the node  
		graph_node(int num);
		~graph_node();
};

// constructor of class graph_node
graph_node::graph_node(int num)
{
	key=num;
	
	
}

// destructor of class graph_node
graph_node::~graph_node()
{
	this->edge.erase(this->edge.begin(),this->edge.end());
	
}


// class of graph
class graph{
	private:
		map<int,graph_node*> g;                 // g maps all the key value to its node pointer
		int size;
		map<int, list<int> > path_availble;     // path_availble contains all the path key has
		
	public:
		graph();
		~graph();
		graph_node get_graphnode(int key);
		int get_size();
		void add_graphnode(int key);
		bool delete_graphnode(int key );
		void add_path(int key1,int key2);
		void delete_path(int key1,int key2);
		void bfs_print(int key1);
		void graph_print();
		void dfs_print(int key);
		list<int>* bfs_nodes(int key);
		bool find(int key,list<int>* l);
		bool search_path(int key1,int key2);
		void available_path_print(int key);
		bool find(int key,list<int>& l);
		void print_all_path();
};
graph::graph()
{
	size=0;
}
graph::~graph()
{
	g.erase(g.begin(),g.end());
}


// adds graphnode with identifier key 
void graph::add_graphnode(int key)
{
	graph_node* node=new graph_node(key);
	g[key]=node;
	size++;
	
	
}

// it will delete graph_node with identifier key
bool graph::delete_graphnode(int key)
{
	graph_node* node=g[key];
	delete node;
	size--;
	return true;
}

// returns size of the graph

int graph::get_size()
{
	return size;
	
}


// return ture if key is one of the element of list
bool graph::find(int key,list<int>& l)
{
	
	
	for(list<int>::iterator it=l.begin();it!=l.end();it++)
	{
		
		if(*it==key)
			return true;
		
			
	}
	
	return false;
}

// return ture if key is one of the element of list
bool graph::find(int key,list<int>* l)
{
	
	
	for(list<int> ::iterator it=l->begin();it!=l->end();it++)
	{
		
		if(*it==key)
			return true;
		
	}
	
	return false;
}

// add bidirectional edge between key1 and key2
// also update path_availble matrix so all the other edges of key1 and key2 will be updated
void graph::add_path(int key1,int key2)
{
	graph_node* node1,*node2;                        // pointers to node with idetifier key1 and key2 respectively
	node1=g[key1];
	node2=g[key2];
	
	// if path already exist between key1 and key2
	if(find(key2,path_availble[key1]))                 
	{
		// add bidirectional edge  
		
		node1->edge.push_back(key2);
		node2->edge.push_back(key1);
		
		return;
	}
	
	// else update the path_availble matrix
	else
	{
		// add bidirectional edge 	
		node1->edge.push_back(key2);
		node2->edge.push_back(key1);
		
		// add all the available path from key2 to every available node at key1
		
		for(list<int>::iterator it=path_availble[key1].begin();it!=path_availble[key1].end();it++)
		{
			if(!path_availble[key2].empty())
			{
				path_availble[*it].push_back(key2);
				for(list<int>::iterator i=path_availble[key2].begin();i!=path_availble[key2].end();i++)
				{
			
					
					path_availble[*it].push_back(*i);
				}
			}
			else
			{
				path_availble[*it].push_back(key2);
			}
		}
		// add all the available path from key1 to every available node at key2
		
		for(list<int>::iterator it=path_availble[key2].begin();it!=path_availble[key2].end();it++)
		{
			if(!path_availble[key1].empty())
			{
				path_availble[*it].push_back(key1);
				for(list<int>::iterator i=path_availble[key1].begin();i!=path_availble[key1].end();i++)
				{
			
					
					path_availble[*it].push_back(*i);
				}
			}
			else
			{
				path_availble[*it].push_back(key1);
			}
		}
		
		// add all the available path from key2 to key1 
		
		for(list<int>::iterator i=path_availble[key2].begin();i!=path_availble[key2].end();i++)
		{
			
				path_availble[key1].push_back(*i);
				
		}
		
		// add all the available path from key1 to key2
		
		for(list<int>::iterator i=path_availble[key1].begin();i!=path_availble[key1].end();i++)
		{
			
				path_availble[key2].push_back(*i);
				
		}
		
		path_availble[key1].push_back(key2);
		path_availble[key2].push_back(key1);
		
	}
	
	

}

// delete path between key1 and key2
void graph::delete_path(int key1,int key2)
{
	graph_node* node1,*node2;                   // pointers to node with idetifier key1 and key2 respectively
	node1=g[key1];
	node2=g[key2];
	
	// remove bidirectional edge between key1 and key2
	node1->edge.remove(key2);
	node2->edge.remove(key1);
	
	// get all the nodes connected with key1
	list<int>* node1_list=bfs_nodes(key1);
	
    // if key2 can be reached from key1 then no action required	
	if(find(key2,node1_list))
	{
		return;
		
	}
	else
	{
		// get all the nodes connected with key1
		list<int>* node2_list=bfs_nodes(key2);
		map<int,bool> visited;
		
		queue<int> q;
		q.push(key1);
		visited[key1]=true;
		
		// do bfs traversal from key1 and add all the nodes can be reached
		
		while(!q.empty())
		{
			int key=q.front();
			q.pop();
			
			
			
			
				graph_node* node;
				node=g[key];
				
				path_availble[key].erase(path_availble[key].begin(),path_availble[key].end());
			    for(list<int> ::iterator it=node1_list->begin();it!=node1_list->end();it++)
				{	
					if(*it != key)
					path_availble[key].push_back(*it);
					
				}
				for(list<int>::iterator it=node->edge.begin();it!=node->edge.end();it++)
				{	map<int,bool>::iterator j=visited.find(*it);
					if(j==visited.end())
					{
						visited[*it]=true;
						q.push(*it);
					}
			
				
				}
			
		}
		map<int,bool> visited2;
		
		queue<int> q2;
		q2.push(key2);
		visited2[key2]=true;
		
		// do bfs traversal from key2 and add all the nodes can be reached
		while(!q2.empty())
		{
			int key=q2.front();
			q2.pop();
			
			
			
			
				graph_node* node;
				node=g[key];
				
				path_availble[key].erase(path_availble[key].begin(),path_availble[key].end());
			    for(list<int> ::iterator it=node2_list->begin();it!=node2_list->end();it++)
				{	
					if(*it != key)
					path_availble[key].push_back(*it);
					
				}
				for(list<int>::iterator it=node->edge.begin();it!=node->edge.end();it++)
				{	map<int,bool>::iterator j=visited2.find(*it);
					if(j==visited2.end())
					{
						visited2[*it]=true;
						q2.push(*it);
					}
			
				
				}
			
		}
		delete node2_list;
	}
	delete node1_list;
	
 	
}
list<int>* graph::bfs_nodes(int key)
{
	map<int,bool> visited;
	list<int>* vertex=new list<int>;
	queue<int> q;
	q.push(key);
	visited[key]=true;
	
		while(!q.empty())
		{
			int key=q.front();
			q.pop();
			vertex->push_back(key);
			
			
			
				graph_node* node;
				node=g[key];
			
				for(list<int>::iterator it=node->edge.begin();it!=node->edge.end();it++)
				{	map<int,bool>::iterator j=visited.find(*it);
					if(j==visited.end())
					{
						visited[*it]=true;
						q.push(*it);
					}
			
				
				}
			
		}
		
	//cout<<node->key<<" ";
	return vertex;
}
void graph::bfs_print(int key1)
{
	
	
	map<int,bool> visited;
	queue<int> q;
	q.push(key1);
	visited[key1]=true;
	
		while(!q.empty())
		{
			int key=q.front();
			q.pop();
			cout<<key<<" ";
			
			
			
				graph_node* node;
				node=g[key];
			
				for(list<int>::iterator it=node->edge.begin();it!=node->edge.end();it++)
				{	map<int,bool>::iterator j=visited.find(*it);
					if(j==visited.end())
					{
						visited[*it]=true;
						q.push(*it);
					}
			
				
				}
			
		}
	//cout<<node->key<<" ";
	cout<<endl;
	
}
void graph::dfs_print(int key)
{
	map<int,bool> visited;
	stack<int> s;
	visited[key]=true;
	s.push(key);
	while(!s.empty())
	{
		key=s.top();
		graph_node* node;
		node=g[key];
		s.pop();
		cout<<key<<" ";
		for(list<int>::iterator it=node->edge.begin();it!=node->edge.end();it++)
				{	map<int,bool>::iterator j=visited.find(*it);
					if(j==visited.end())
					{
						visited[*it]=true;
						s.push(*it);
					}
			
				
				}
		
	}
	cout<<endl;
}
void graph::graph_print()
{
	for(map<int,graph_node*>::iterator it=g.begin();it!=g.end();it++)
	{
		cout<<it->second->key<<" ";
	}
	cout<<endl;
}	
bool graph::search_path(int key1,int key2)
{
	if(find(key2,path_availble[key1]))
		return true;
	else
		return false;
}
void graph::available_path_print(int key)
{
	cout<<"Path available from "<<key<<endl;
	for(list<int>::iterator it=path_availble[key].begin();it!=path_availble[key].end();it++)
	{
			cout<<*it<<" ";
	}
	cout<<endl;
}
void graph::print_all_path()
{
	cout<<endl<<"All the path available."<<endl;
	for( map< int, list<int> >::iterator it=path_availble.begin();it!=path_availble.end();it++)
	{
		cout<<it->first<<"-> ";
		for( list<int>::iterator i=path_availble[it->first].begin();i!=path_availble[it->first].end();i++)
			cout<<*i<<" ";
		
		cout<<endl;
	}
}
int main()
{
	graph g;
	g.add_graphnode(1);
	g.add_graphnode(2);
	g.add_graphnode(3);
	g.add_graphnode(4);
	g.add_graphnode(5);
	g.add_graphnode(6);
	g.add_graphnode(7);
	g.add_graphnode(8);
	g.add_graphnode(9);
	g.add_path(1,2);
	
	g.add_path(1,3);
	g.add_path(1,5);
	g.add_path(2,4);
	g.add_path(3,6);
	
	g.add_path(7,8);
	
	g.add_path(5,9);
	g.print_all_path();
	g.delete_path(5,9);
	g.print_all_path();
	
	bool find=g.search_path(1,4);
	cout<<"find="<<find<<endl;
}
