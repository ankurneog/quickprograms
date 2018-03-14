/*
 * MinStepsToEnd.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: ankurneog
 */

#include <iostream>
using namespace std;

int Min(int a, int b)
{
    return (a<b)?a:b;
}

int MinSteps(int arr[],int arraySize)
{
	if(0==arraySize)
	{
		return 0;
	}
	if(1==arraySize)
	{
		return 0;
	}
	int *minSteps = new int[arraySize];
	for(int k=0;k<arraySize;++k)
	{
		minSteps[k]=255;
	}

	minSteps[0]=0;

	for(int i =1;i<arraySize;i++)
	{

		for(int j =0; j<i;j++)
		{
			if(arr[j]>=(i-j))
			{
				minSteps[i] = Min((minSteps[j]+1),minSteps[i]);

				cout<<"Min Steps : minSteps["<<i<<"] : "<< minSteps[i]<<endl;
			}
		}
	}

	int minsteps = minSteps[arraySize-1];
	cout<<"<====FINAL MIN STEPS : "<<minsteps<<" =====>"<<endl;


	return 0;
}


