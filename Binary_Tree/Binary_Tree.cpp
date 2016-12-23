// Rahul Parikh
// Binary Tree implemntation


#include<iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

class treenode
{	
	public:

	int data;
	treenode *left,*right;
	public:
	treenode(int key);
	~treenode();
};
treenode::treenode(int key)
{
	data=key;
	left=NULL;
	right=NULL;
}

treenode::~treenode()
{
	
}
class binary_tree
{
	treenode *root;
	public:
	binary_tree();
	binary_tree(const binary_tree& tree);
	~binary_tree();
	treenode* get_root();
	void inorder(treenode* root)const;
	void postorder(treenode* root)const;
	void preorder(treenode* root)const;
	void inorder_iterative()const;
	void preorder_iterative()const;
	void postorder_iterative()const;
	void delete_tree();
	void copy_tree(treenode **node,treenode *node1);
	void destroy_tree(treenode *root );
	
};
binary_tree::binary_tree()
{
	root=new treenode(10);
	root->left=new treenode(2);
	root->right=new treenode(50);
	root->left->right=new treenode(11);
	root->left->left=new treenode(15);
	root->left->left->right=new treenode(18);
	root->left->left->left=new treenode(19);
	root->right->left=new treenode(9);
	root->right->right=new treenode(30);
	root->right->left->right=new treenode(6);
}
binary_tree::binary_tree(const binary_tree& tree)
{
	copy_tree(&root,tree.root);
}
void binary_tree::copy_tree(treenode **node,treenode *node1)
{
	
	if(node1!=NULL)
	{ 
		if(node!=NULL)
		*node=new treenode(node1->data);
		copy_tree(&(*node)->left,node1->left);
	    copy_tree(&(*node)->right,node1->right);
	}
	
}
binary_tree::~binary_tree()
{
	destroy_tree(root);
	
}
void binary_tree::destroy_tree(treenode *root )
{
	if(root!=NULL)
	{
		destroy_tree(root->left);
		destroy_tree(root->right);
		delete root;
	}
}
void binary_tree::inorder(treenode* root)const
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout<<root->data<<" ";
		inorder(root->right);
	}
}
void binary_tree::postorder(treenode* root)const
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->data<<" ";
		
	}
}
void binary_tree::preorder(treenode* root)const
{
	if(root!=NULL)
	{
		cout<<root->data<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}
treenode* binary_tree::get_root()
{
	return root;
}
void binary_tree::inorder_iterative()const
{
	stack<treenode*> s;
	treenode* current=root;
	
	while(true)
	{
		if(current!=NULL)
		{
			s.push(current);
			current=current->left;
		}
		else{
			if(!s.empty())
			{
			current=s.top();
			s.pop();
			cout<<current->data<<" ";
			current=current->right;
			}
			else
			{
				break;
			}
		}
	}
}
void binary_tree::preorder_iterative()const
{
	stack<treenode*> s;
	treenode* current=root;
	
	while(true)
	{
		if(current!=NULL)
		{
			cout<<current->data<<" ";
			s.push(current);
			current=current->left;
		}
		else{
			if(!s.empty())
			{
			current=s.top();
			s.pop();
			
			current=current->right;
			}
			else
			{
				break;
			}
		}
	}
}
void binary_tree::postorder_iterative()const
{
	stack<treenode*> s,s1;
	treenode* current=root;
	s.push(current);
	while(!s.empty())
	{
		current=s.top();
		s.pop();
		s1.push(current);
		if(current->left!=NULL)
			s.push(current->left);
		if(current->right!=NULL)
			s.push(current->right);
	}
	while(!s1.empty())
	{
		cout<<s1.top()->data<<" ";
		s1.pop();
	}
}
void print_left_view(treenode* root,int nextlevel)
{
	static int curr_level=0;
	if(root==NULL)return;
	if(curr_level<nextlevel)
	{
		cout<<root->data<<" ";
		curr_level=nextlevel;
	}
	print_left_view(root->left,nextlevel+1);
	print_left_view(root->right,nextlevel+1);
		
	
} 
int main()
{
	binary_tree tree1;
	tree1.inorder_iterative();
	binary_tree tree2(tree1);
	
	tree2.inorder_iterative();
}