/*
 * QuickSort.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: ankurneog
 */
#include <iostream>
using namespace std;
void Swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a  = *b;
	*b  = tmp;
}
int Partition(int arr[],int start,int end)
{
    int j=0;
    int i=j-1;

    int pivot= end;
    cout<<" Pivot Value: " << arr[pivot]<<endl;

    while(j!=pivot&&j!=pivot)
    {
    	if(arr[j]<arr[pivot])
    	{
    		i++;
    		Swap(&arr[i],&arr[j]);

    	}
    	j++;
    }
    i++;
    Swap(&arr[i],&arr[pivot]);
    cout<<" Pivot Old Position : "<< pivot <<" New Position : "<<i <<endl;
    //PrintArray(arr,10);

	return i;
}

void QuickSort(int arr[],int start, int end) // 0-based
{
	cout<<"Quick Sort start : "<<start<<" end : "<<end<<endl;
	if(start>=end)
	{
		return;
	}

	int pivot_index = Partition(arr,start,end);

	QuickSort(arr,start,pivot_index-1);
	QuickSort(arr,(pivot_index+1),end);

}

