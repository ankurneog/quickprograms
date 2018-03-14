/*
 * InsertionSort.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: ankurneog
 */

#include <iostream>
using namespace std;
void InsertionSort(int arr[], int n)
{
	cout<<"Before Sorting...."<<endl;
	for(int i=0 ;i<n;i++)
	{
		cout<<arr[i]<<endl;
	}
	for(int i=1;i<(n-1);i++)
	{
		int j=i;
		int element = arr[i];
		while(j>0 && arr[j-1]>element)
		{
			arr[j]   =arr[j-1];
			arr[j-1] =element;

			j=j-1;
		}
	}
	cout<<"After Sorting ... "<<endl;

	for(int i=0 ;i<n;i++)
	{
		cout<<arr[i]<<endl;
	}
}

