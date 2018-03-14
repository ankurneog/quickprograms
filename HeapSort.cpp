/*
 * HeapSort.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: ankurneog
 */

#include <iostream>
using namespace std;
//Three Procedures
//HeapSort() -> Which Actually Does the Sorting
//BuildMaxHeap()-> Iterate through the elements and Do Max Heap
//MaxHeapify()-> Do Heap Procedure, i.e Max Value at the root.

void Swap(int arr[],int src,int dest)
{
	int temp;
	temp = arr[src];
	arr[src]=arr[dest];
	arr[dest]=temp;
}
void Print(int arr[],int maxsize)
{
	cout<<endl;
	for(int i = 0;i<maxsize;++i)
	{
		cout<<arr[i]<<endl;
	}
}
int Left(int index )
{
	return 2*index;
}
int Right(int index)
{
	return 2*index +1;
}
int Parent(int index)
{
	return index/2;
}
void MaxHeapify(int arr[],int maxsize,int index)
{

	int left = Left(index);
	int right= Right(index);
	int largest=index;
	if(left<(maxsize-1) && (arr[left]>arr[largest]) )
	{
		largest=left;
	}
	if(right<(maxsize-1) && (arr[right]>arr[largest]))
	{
		largest=right;
	}
	if(largest==index)
	{
		cout<<"Largest == index, nothing to do  Index : "<< largest<<"=== value : "<<arr[largest]<<endl;
		return;
	}
	Swap(arr,index,largest);

	Print(arr,maxsize);
	cout<<"-----------"<<endl;
	MaxHeapify(arr,maxsize,largest);
}

void BuildMaxHeap(int arr[],int maxsize)
{
	if(maxsize==1)
	{
		cout<<"Nothing to Do.. "<<endl;
	}
	cout<<endl<<"Max Heap Size : "<<maxsize<<endl;
	for(int i=maxsize-1;i>=0;i--)
	{
		static int count =0;
		cout<<endl<<"----Iteration------: "<<count++<<endl;
		cout<<"BuildMaxHeap Index : "<<i<<" Value : " <<arr[i]<<endl;
		MaxHeapify(arr,maxsize,i);
	}
}
void HeapSort(int arr[],int maxsize)
{
	cout<<endl<<"Heap Sort..."<<endl;
	Print(arr,maxsize);
	BuildMaxHeap(arr,maxsize);
	Print(arr,maxsize);

}



