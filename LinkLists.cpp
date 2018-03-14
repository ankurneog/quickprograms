//============================================================================
// Name        : LinkLists.cpp
// Author      : Ankur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
struct Node {
	int data;
	struct Node *next;
	Node(int d)
	{
		data=d;
		next=NULL;
	}
};
class LinkList {
public :

	void AddNode(int data);
	void MakeList(int a[],int maxSize);
	void DeleteNode(int data);
	void ReverseList();
	void PrintList();
	void DeleteList();
	inline bool IsEmpty()
	{
		return head==NULL;
	}
	Node *GetHead();
	LinkList()
	{
		head=NULL;
		tail=NULL;
		numNodes=0;
	}
	~LinkList()
	{
		DeleteList();
	}
	Node* head;
private:

	Node* tail;
	int numNodes;
};
void LinkList::MakeList(int a[],int maxSize)
{
	for(int i=0;i<maxSize;++i)
	{
		AddNode(a[i]);
	}
}
void LinkList::AddNode(int data)

{
	Node *temp = new Node(data);
	numNodes++;

	if(NULL==head)
	{
		cout<<" Inserting First Element into the list "<<endl;
		head=temp;
		tail=temp;
		return;
	}
	cout<<" Inserting Element : "<<numNodes<<endl;

	Node *p =head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=temp;
	tail=p;

}
void LinkList::DeleteNode(int info)
{
	if(NULL==head)
	{
		cout<<"Empty List, Nothing to Delete "<<endl;
		return;
	}
	Node *p=head;
	Node *q=NULL;
	while(p->data!=info&&p!=NULL)
	{
		q=p;
		p=p->next;
	}
	if(p->data==info)
	{
		if(p==tail)
		{
			tail=q;
		}
		q->next=p->next;
		p->next=NULL;
		if(p!=NULL)
	        delete p;
		numNodes--;

	}
	else
	{
		cout<<"Data : "<<info<<" Not found in List ... "<<endl;
		return;
	}
}

void LinkList::PrintList()
{
	if(NULL==head)
	{
		cout<<"List is Empty "<<endl;
		return;
	}
	cout<<"Printing Contents of Link List - Total Elements :  "<<numNodes<<endl;

	Node *p=head;
	while(p!=NULL)
	{
		cout<<p->data<<endl;
		p=p->next;
	}
}
void LinkList::DeleteList()
{

	while(head!=NULL)
	{
		Node *p=head;
		head=head->next;
		if(p!=NULL)
		   delete p;
	}

}
void LinkList::ReverseList()
{
	if(NULL==head)
	{
		cout<<"List is Empty..."<<endl;
		return;
	}
	Node *p=head;
    Node *q=p->next;
    Node *r;
    p->next=NULL;
    while(q!=NULL)
    {
    	    r=q->next;
    	    q->next =p;
    	    p=q;
    	    q=r;
    }
    tail=head;
    head=p;
}

void MergeList(LinkList &ll1,LinkList &ll2, LinkList &mergedList)
{
	if(ll1.IsEmpty()&&ll2.IsEmpty())
	{
	   cout<<"Nothing to Merge, Both lists are empty "<<endl;
	   return;
	}
	if(ll1.IsEmpty())
	{
		mergedList=ll1;
		return;
	}
	if(ll2.IsEmpty())
	{
		mergedList=ll1;
		return;
	}
	Node *pLL1=ll1.head;
	Node *pLL2=ll2.head;

	if(pLL1->data<pLL2->data)
	{
		mergedList.head=ll1.head;
		pLL1=pLL1->next;
	}
	else
	{
		mergedList.head=ll2.head;
		pLL2=pLL2->next;

	}
	Node *pLLMerged = mergedList.head;


	while(pLL1!=NULL&&pLL2!=NULL)
	{
		if(pLL1->data<pLL2->data)
		{
			pLLMerged->next=pLL1;
			pLL1=pLL1->next;
			pLLMerged=pLLMerged->next;

		}
		else
		{
			pLLMerged->next=pLL2;
			pLL2=pLL2->next;
			pLLMerged=pLLMerged->next;
		}
	}
	while(pLL1!=NULL)
	{
		pLLMerged->next=pLL1;
		pLL1=pLL1->next;
		pLLMerged=pLLMerged->next;
	}
	while(pLL2!=NULL)
	{
		pLLMerged->next=pLL2;
		pLL2=pLL2->next;
		pLLMerged=pLLMerged->next;
	}
	ll1.head=NULL;
	ll2.head=NULL;

}

bool CompareNodes(Node *a,Node *b)
{
	if(a==NULL&&b==NULL)
	{
		return true;
	}

	if(a->data==b->data)
	{
		return CompareNodes(a->next,b->next);
	}
	return false;
}

void CompareLinkLists(LinkList &ll1,LinkList &ll2)
{
	Node *a=ll1.head;
	Node *b=ll2.head;

	if(CompareNodes(a,b))
	{
		cout<<"Link Lists are Equal.. "<<endl;
	}
	else
	{
		cout<<"Link Lists are Not Equal... "<<endl;
	}

}



int main() {

	cout << "Link List Program" << endl; // prints Link List

	LinkList ll1,ll2;

	int a1[]={0,20,40,60,80};
	int a2[]={0,20,40,60,80};

	ll1.MakeList(a1,sizeof(a1)/sizeof(a1[0]));
	ll2.MakeList(a2,sizeof(a2)/sizeof(a2[0]));

	ll1.PrintList();
	ll2.PrintList();

	LinkList mergedList;

	//MergeList(ll1,ll2,mergedList);
	//mergedList.PrintList();
	//ll1.PrintList();
	//ll2.PrintList();

	 CompareLinkLists(ll1,ll2);




	return 0;
}
