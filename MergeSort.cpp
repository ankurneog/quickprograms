/*
 * MergeSort.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: ankurneog
 */


#include <iostream>
using namespace std;

void Merge(int a[],int start, int mid, int end)
{
	int i=0;
	int j=0;
	int k=start;// start index of the merged array - Destination a[]


	int maxL= mid - start +1;
	int maxR= end - (mid+1) +1;

	int aL[maxL];
	int aR[maxR];
	//Fill aL and aR with the contents of a[] accordingly

	for(int x=0;x<maxL;++x)
	{
		aL[x]=a[start+x];
	}
	for(int x=0;x<maxR;++x)
	{
		aR[x]=a[mid+1+x];
	}

	//Merge
	while(i<maxL&&j<maxR)
	{
		if(aL[i]<aR[j])
		{
			a[k++]=aL[i++];
		}
		else
		{
			a[k++]=aR[j++];
		}
	}
	while(i<maxL)
	{
		a[k++]= aL[i++];
	}
	while(j>maxR)
	{
		a[k++]=aR[j++];
	}


}

void MergeSort(int a[],int start, int end)
{
	static int iter=0;
	cout<<"Iter : "<<++iter<<endl;
	if(start>=end)
	{
		//start==end implies we have just 1 element in our subarray, and we should exit from the recurssion
		return;
	}
	int mid = (start+end)/2;

	cout<<"Mid : "<<mid<<endl;

	MergeSort(a,start,mid);
	MergeSort(a,mid+1,end);

	Merge(a,start,mid,end);

}

