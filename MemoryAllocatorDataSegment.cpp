//============================================================================
// Name        : MemoryAllocatorDataSegment.cpp
// Author      : Ankur
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define MAXSIZE 1000

static char MemoryBlock[MAXSIZE];

struct MemoryControlBlock {
	int blockSize;
	bool isAvailable;
};
char *memStart;
char *memEnd;
char *highLimit;
bool memInitialized=false;

void PrintAllocations()
{
	if(memStart==memEnd)
	{
		cout<<"Allocations Not Done Yet..."<<endl;
		return;
	}
	char *currentLoc=(char *)memStart;

	struct MemoryControlBlock *mcb;
	while(currentLoc!=memEnd)
	{

		mcb = (struct MemoryControlBlock *)currentLoc;
		string availble = (mcb->isAvailable)?"YES":"NO";
		cout<<"Address : "<<hex<<(void *)currentLoc
			<<dec<<" | Allocated : "<<(mcb->blockSize - sizeof(struct MemoryControlBlock))
		    <<" | Effective Size : "<<mcb->blockSize
			<<" | AVAILABLE : "<<availble<<endl;

		currentLoc= currentLoc + mcb->blockSize;
	}
	cout<<"-----------------------------------------------------------------------------"<<endl;
}


void InitMem()
{
	memStart=MemoryBlock;
	memEnd = memStart;
	highLimit = &MemoryBlock[MAXSIZE-1];
	memInitialized=true;
}

void *Allocate(long numBytes)
{
	if(!memInitialized)
	{
		InitMem();
	}
	char* currentLoc=NULL;
	char* availableBlock=NULL;
	struct MemoryControlBlock *mcb;
	//Effective Memory Needed is numBytes + the control block
	numBytes = numBytes + sizeof(struct MemoryControlBlock);
	currentLoc = memStart;
	cout<<" Memstart : "<<hex<<(void *)memStart;
	while(currentLoc!=memEnd)
	{
		mcb= (struct MemoryControlBlock *)currentLoc;
		if(mcb->blockSize>=numBytes)
		{
			if(mcb->isAvailable)
			{
				availableBlock=currentLoc;
				mcb->isAvailable=false;
				break;
			}
		}
		currentLoc = currentLoc + mcb->blockSize;

	}
	if(NULL==availableBlock)
	{
		//We were not able to allocated any memory
		availableBlock=memEnd;
		memEnd = memEnd + numBytes;
		if(memEnd>=highLimit)
		{
			cout<<"Allocate Failed - Out of Memory "<<endl;
			return NULL;
		}
		mcb = (struct MemoryControlBlock *)availableBlock;
		mcb->isAvailable=false;
		mcb->blockSize  = numBytes;

	}
	return availableBlock + sizeof(struct MemoryControlBlock);
}

void DeAllocate(void *p)
{
	struct MemoryControlBlock *mcb;
	char *firstByte = (char *)p;
	mcb = (struct MemoryControlBlock *)(firstByte - sizeof(struct MemoryControlBlock));
	mcb->isAvailable=true;
}

int main() {
	cout << "Memory Manager - Data Segment" << endl; // prints Memory Manager - Data Segment
	cout<< "Size of Memory Control Block : "<<sizeof(struct MemoryControlBlock)<<endl;

	PrintAllocations();

	cout<<"Allocation 1 "<<endl;
	char *p = (char *)Allocate(1);;
	cout<<"Allocation 2 "<<endl;
	int *i  = (int *)Allocate(4);



	PrintAllocations();

	DeAllocate(p);

	PrintAllocations();

	DeAllocate(i);

	PrintAllocations();

	return 0;
	return 0;
}
