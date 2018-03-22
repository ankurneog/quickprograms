//============================================================================
// Name        : Trees.cpp
// Author      : Ankur
// Version     :
// Copyright   : Your copyright notice
// Description : Binary Search Tree in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
	int data;
	struct TreeNode *parent;
	struct TreeNode *left;
	struct TreeNode *right;

	TreeNode(int rData)
	{
		data=rData;
		parent = NULL;
		left=NULL;
		right=NULL;
	}
	};



class TreeNodeQueue {
public :
	TreeNodeQueue()
{
		head=NULL;
}
	struct Element {
		TreeNode *data;
		struct Element* next;
		Element(TreeNode *newData)
		{
			data =newData;
			next =NULL;
		}
		Element()
		{
			data=NULL;
			next=NULL;
		}
	};
	void PrintQueue()
	{
		if(head==NULL)
		{
			cout<<"Queue Is Empty "<<endl;
			return;
		}
		Element *p=head;
		cout<<" [ ";
		while(p!=NULL)
		{
			cout<<p->data->data<<" : ";
			p=p->next;
		}
		cout<<" ]"<<endl;

	}
	TreeNode * DeQueue(void){

	//	cout<<"Dequeing .. "<<endl;

		if(head==NULL)
		{
			return NULL;
		}
	    Element *p = head;
	    Element *q;
	    while (p->next!=NULL)
	    {
	    	   q=p;
	    	   p=p->next;
	    }
	    TreeNode *node = p->data;
	    cout<<"Dequeued : "<<node->data<<endl;
	    if(p!=NULL)
	    {
	       delete p;
	       p=NULL;
	    }
	    q->next=NULL;
	    PrintQueue();
	    return node;

	}
	void EnQueue(TreeNode *node)
	{
		Element * newElement = new Element(node);
		cout<<" Enqueing : "<<newElement->data->data<<endl;
		if(NULL==head)
		{
			//cout<<"Inserting First Element in Queue... "<<endl;
			head=newElement;
			return;
		}
		Element *p=head;
		while(p->next!=NULL)
		{
			p=p->next;
		}
		p->next=newElement;
		cout<<"Queue Contents : "<<endl;
		PrintQueue();
	}



	bool IsQueueEmpty()
	{
		return NULL==head;
	}

private:
	Element* head;

};

class BinarySearchTree {
public :
	BinarySearchTree();
	~BinarySearchTree();
	void Insert(TreeNode** root,TreeNode *parent,int data);

	void Insert(int a[],int sizeofarray);

	void Delete(int data);

	TreeNode * FindNode(TreeNode *node,int data);

	void DeleteTree(TreeNode **pRoot);

	void Balace();

	void PrintPreOrder(TreeNode *root);

	void PrintInOrder(TreeNode *root);

	void PrintPostOrder(TreeNode *root);

	void PrintLevelOrder(TreeNode *root);

	TreeNode* LowestCommonAncestor(TreeNode *root,int m,int n);

	inline TreeNode * GetTreeRoot() const
	{
		return pRoot;
	}


	int ComputeHeight(TreeNode *root);

	int ComputeSize(TreeNode *root);

	TreeNode * FindMax(TreeNode *root);

	TreeNode * FindMin(TreeNode *root);


private :
	TreeNode *pRoot;
	int heightOfTree;
	int sizeOfTree;
};

BinarySearchTree::BinarySearchTree()
{
	pRoot=NULL;
	heightOfTree=0;
	sizeOfTree=0;
}
BinarySearchTree::~BinarySearchTree()
{
	if(pRoot!=NULL)
	{

	}
}
void BinarySearchTree::Insert(TreeNode ** root,TreeNode *parent,int data){

	if(*root==NULL)
	{
		TreeNode *newNode = new TreeNode(data);
		*root=newNode;
		newNode->parent=parent;
		return;
	}
	if(data<(*root)->data)
	{

		Insert(&((*root)->left),*root,data);

	}
	else // data>= pRoot->data
	{
		Insert(&((*root)->right),*root,data);
	}

}

void BinarySearchTree::Insert(int a[],int sizeofarray){

	for(int i=0;i<sizeofarray;++i)
	{
		Insert(&pRoot,pRoot,a[i]);
	}

}

void BinarySearchTree::Delete(int data){

	cout<<"Deleting : "<<data<<endl;
	TreeNode *root = GetTreeRoot();
	TreeNode* node=FindNode(root,data);
	if(NULL==node)
	{
		cout<<"Data <<"<<data<<" Not found in BST"<<endl;
		return;
	}
	cout<<"Node  :"<<(node)<< " Data : "<<node->data<<endl;
	cout<<"Parent  :"<<node->parent<< " Data : "<<node->parent->data<<endl;

	TreeNode *left = node->left;
	TreeNode *right= node->right;
	TreeNode *parent= node->parent;

	if(left!=NULL)
	    cout<<" Node Left : "<<left<<" Data : "<<left->data<<endl;
	if(right!=NULL)
		 cout<<" Node Left : "<<right<<" Data : "<<right->data<<endl;

	//TreeNode **parentLink = ((*node)==parent->left)?&(parent->left):&(parent->right);
	if(left==NULL||right==NULL)
	{
		if(left!=NULL&&right==NULL)
		{
			if(node==parent->right)
				parent->right=left;
			else
				parent->left =left;

		}
		if(right!=NULL&&left==NULL)
		{
			if(node==parent->right)
			    parent->right=right;
			else
				parent->left =right;
		}
		delete node;
		node=NULL;
		PrintLevelOrder(GetTreeRoot());
		cout<<"Data : "<<data<<" Deleted From Tree "<<endl;
		return;

	}

	if(left!=NULL && right!=NULL)
	{
	     TreeNode * p    = FindMin(node->right);
	     node->data      = p->data;
	     node->right     = p->right;
	     //

	     delete p;
	     p=NULL;
	     PrintLevelOrder(GetTreeRoot());
	     cout<<"Data : "<<data<<" Deleted From Tree "<<endl;
	}


}

TreeNode* BinarySearchTree::FindNode(TreeNode* node,int data)
{
	cout<<"find node :::: "<<node->data<<endl;
	if(NULL==node)
	{
		cout<<__FUNCTION__<<" node is NULL "<<endl;
		return NULL;
	}
	if(node->data==data)
	{
		cout<<__FUNCTION__<<" Node found  "<<node->data<<endl;
		return node;
	}
	if(data<node->data)
	{
		return FindNode(node->left,data);
	}
	else
	{
		return FindNode(node->right,data);
	}

}

void BinarySearchTree::DeleteTree(TreeNode **pRoot){

}

void BinarySearchTree::Balace(){

}

void BinarySearchTree::PrintPreOrder(TreeNode *root){
	static bool printflag=false;
	if(root==NULL)
	{
		if(!printflag)
		{
			cout<<" PrintPreOrder..."<<endl;
			printflag=true;
		}
		return;
	}
	cout<<" : "<<root->data<<endl;
	PrintPreOrder(root->left);
	PrintPreOrder(root->right);

}

void BinarySearchTree::PrintInOrder(TreeNode *root){
	static bool printflag=false;

	if(root==NULL)
	{
		if(!printflag)
		{
			cout<<" PrintInOrder..."<<endl;
			printflag=true;
		}
		return;
	}
	PrintInOrder(root->left);
	cout<<" : "<<root->data<<endl;
	PrintInOrder(root->right);

}

void BinarySearchTree::PrintPostOrder(TreeNode *root){
	static bool printflag=false;
	if(NULL==root)
	{
		if(!printflag)
		{
			cout<<" PrintPostOrder..."<<endl;
			printflag=true;
		}
		return;
	}
	PrintPostOrder(root->left);
	PrintPostOrder(root->right);
	cout<<" : "<<root->data<<endl;


}


void BinarySearchTree::PrintLevelOrder(TreeNode *p){

	cout<<"Level Order Printing ..."<<endl;

	if(NULL==p)
	{
		cout<<" Root Node is NULL, Nothing to print ... "<<endl;
		return;
	}
	//TreeNodeQueue tq;
	//tq.EnQueue(p);
	vector<TreeNode *> tnv;
	tnv.push_back(p);

	while(tnv.size()!=0)
	{
		std::vector<TreeNode * >::iterator it = tnv.begin();
		TreeNode *p = *it;
		tnv.erase(it);
		cout<< ">> "<<p->data<<endl;
		if(NULL!=p->left)
		{
			tnv.push_back(p->left);
		}
		if(NULL!=p->right)
		{
			tnv.push_back(p->right);
		}
	}

}

int BinarySearchTree::ComputeHeight(TreeNode *p){

	if(NULL==p)
	{
		return 0;
	}
	int left = ComputeHeight(p->left);
	int right= ComputeHeight(p->right);
    int height = left>right?left:right;
    return height+1;

}

int BinarySearchTree::ComputeSize(TreeNode *p){

	if(NULL==p)
	{
		return 0;
	}
    int left = ComputeSize(p->left);
    int right= ComputeSize(p->right);
    return left+right+1;

}

TreeNode* BinarySearchTree::FindMin(TreeNode* node)
{
	if(NULL==node)
	   return NULL;

	while(node->left!=NULL)
	{
		node=node->left;
	}
	return node;
}
TreeNode* BinarySearchTree::FindMax(TreeNode* node)
{
	if(NULL==node)
	   return NULL;

	while(node->right!=NULL)
	{
		node=node->right;
	}
	return node;
}
//Lowest common Ancestor between two nodes m and n
TreeNode* BinarySearchTree::LowestCommonAncestor(TreeNode *root,int m,int n)
{
	if(NULL==root)
		return NULL;

	if(root->data==m||root->data==n)
	{
		return root;
	}

	TreeNode* left = LowestCommonAncestor(root->left,m,n);
	TreeNode* right= LowestCommonAncestor(root->right,m,n);

	if(left!=NULL&&right!=NULL)
	{
		//We found the ancestor
		return root;
	}
	if(left==NULL && right==NULL)
	{
		return NULL;

	}
	if(left==NULL&&right!=NULL)
	{
		return right;
	}
	if(right==NULL && left!=NULL)
	{
		return left;
	}



	return NULL;

}

int main() {
	cout << "Binary Search Trees" << endl;
	int a[]= {13,5,6,4,2,7,8,3,20};
	BinarySearchTree bst;
	bst.Insert(a,sizeof(a)/sizeof(a[0]));
	bst.PrintInOrder(bst.GetTreeRoot());
	cout<<" Height Of Tree : "<<bst.ComputeHeight(bst.GetTreeRoot())<<endl;
	cout<<" Size Of Tree : "<<bst.ComputeSize(bst.GetTreeRoot())<<endl;
	cout<<" Min Element : "<<bst.FindMin(bst.GetTreeRoot())->data<<endl;
	cout<<" Max Element : "<<bst.FindMax(bst.GetTreeRoot())->data<<endl;
	bst.PrintLevelOrder(bst.GetTreeRoot());
	bst.Delete(5);
	TreeNode *p =bst.LowestCommonAncestor(bst.GetTreeRoot(),4,2);
	cout<<"Lowest Common Ancestor of 4 and 2 is : "<<p->data<<endl;

	return 0;
}
