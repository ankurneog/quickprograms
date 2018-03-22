//============================================================================
// Name        : MemoryManager.cpp
// Author      : Ankur
// Version     :
// Copyright   : Your copyright notice
// Description : Memory Allocator, Allocating and Reserving at Program Brk / Heap Area
//============================================================================

#include <iostream>
#include <unistd.h>
using namespace std;

struct MemoryControlBlock {
	bool isAvailable;
	int  blockSize;
};

bool isInitialized=false;
void *managedMemoryStart=NULL;
void *managedMemoryEnd = NULL;

void PrintAllocations()
{
	if(managedMemoryStart==managedMemoryEnd)
	{
		cout<<"Allocations Not Done Yet..."<<endl;
		return;
	}
	char *currentLoc=(char *)managedMemoryStart;

	struct MemoryControlBlock *mcb;
	while(currentLoc!=managedMemoryEnd)
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

void InitManagedMemory()
{
	// Grab the last Valid Address from OS
	managedMemoryStart=sbrk(0);
	managedMemoryEnd = managedMemoryStart;
	cout<<"Initializing , managedMemoryStart: "<<managedMemoryStart
			           <<", managedMemoryEnd : " <<managedMemoryEnd<<endl;
	isInitialized=true;
}

void *Allocate(long numBytes)
{
	void* currentLoc;
	void* foundBlockLoc=NULL;

	struct MemoryControlBlock *currentMCB;
	if(!isInitialized)
	{
		InitManagedMemory();
	}
	//Memory Allocated is NumBytes + Control Info
	numBytes = numBytes + sizeof(struct MemoryControlBlock);
	cout<<dec<<" EffectiveNumBytes : "<<numBytes<<endl;
	currentLoc = managedMemoryStart;


	while(currentLoc!=managedMemoryEnd)
	{
		currentMCB = (struct MemoryControlBlock *)currentLoc;
		cout<<hex<<"currentLoc : "<<(void *)currentLoc<<endl;

		if(currentMCB->isAvailable)
		{
			if(currentMCB->blockSize>=numBytes)
			{
				//Got block in existing Heap Segment
				currentMCB->isAvailable=false;//its no longer available
				foundBlockLoc=currentLoc;
				break;
			}
		}
		currentLoc=(char *)currentLoc + currentMCB->blockSize;
	}

	if(NULL==foundBlockLoc)// We did not find mem in Heap Segment
	{
		//expand heap
		cout<<"sbrk(0) before : "<<hex<<(void * )sbrk(0)<<endl;
		sbrk(numBytes);
		foundBlockLoc = managedMemoryEnd; // new block in the end
		//update managedMemoryEnd to new sbrk()
		managedMemoryEnd=sbrk(0); //or managedMemory+effectiveNumBytes;
		cout<<"sbrk(0) after : "<<hex<<(void * )sbrk(0)<<endl;
		//UPdate the currentLoc the memory from Cuurent Location to
		//the updated Memory End
		currentMCB = (struct MemoryControlBlock *)foundBlockLoc;
		currentMCB->isAvailable=false;
		currentMCB->blockSize       =numBytes;

	}
	cout<<"Updated ,managedMemoryStart: "<<managedMemoryStart
	           <<", managedMemoryEnd : " <<managedMemoryEnd<<endl;
	return (char *)foundBlockLoc + sizeof(struct MemoryControlBlock);
}

void DeAllocate(void *pointer)
{
	struct MemoryControlBlock *mcb;
	char *firstByte = (char * )pointer;
	mcb = (struct MemoryControlBlock *)(firstByte - sizeof(struct MemoryControlBlock));
	mcb->isAvailable=true;
	return;
}

int main() {
	cout << "Memory Manager" << endl; // prints Memory Manager

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
}
