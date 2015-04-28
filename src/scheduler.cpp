/******************************************************
 * scheduler.cpp - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#include <map>

#include "scheduler.h"

Scheduler::Scheduler(SchedulerMode mode)
{
	std::vector<PCB> nextQueue;
	scheduler_mode = mode;
	next_job = 0;
	//readyQueue.push_back(nextQueue);
}

Scheduler::~Scheduler()
{
}

void Scheduler::Enqueue(PCB next)	//insert a job into the readyQueue and re-sort based on scheduling policy
{
	readyQueue.push_back(next);
	switch (scheduler_mode)
	{
	case Priority:
		SortQueue(readyQueue, 0, readyQueue.size() - 1);
		break;
	case SJF:
		SJFSortQueue(readyQueue, 0, readyQueue.size() - 1);
		break;
	case FIFO:
		FIFOSortQueue(readyQueue);
		break;
	}
	
}

PCB *Scheduler::Peek()			//return the job at the front of the readyQueue
{	
	return &readyQueue.back();
}

PCB Scheduler::Dequeue()		//remove and return the job at the front of the readyQueue
{	
	PCB result = readyQueue.back();
	readyQueue.erase(readyQueue.end());
	SortQueue(readyQueue, 0, readyQueue.size() - 1);
	return result;
}


void Scheduler::LoadToRAM(PCB toLoad)	//copies job to RAM and stores addressing information in that job's PCB
{	
	WORD *ptrToJob;
	ptrToJob = (WORD*)ram->allocate(4, true);
	ptrToJob = &toLoad.startAddress;
	toLoad.program_counter = toLoad.startAddress;

	//toLoad.startAddress = *buffer->currentPtr;
	//toLoad.program_counter = toLoad.startAddress;
	WORD *ptrToProgramSize;
	ptrToProgramSize = (WORD*)ram->allocate(4, true);
	ptrToProgramSize = &toLoad.programSize;
	//buffer->allocate(toLoad.programSize);
	//toLoad.startAddress = *buffer->currentPtr;		
	//toLoad.program_counter = toLoad.startAddress;	
	//buffer->allocate(toLoad.programSize);
	//toLoad.endAddress = *buffer->currentPtr;
	//toLoad.state = PROCESS_NEW;

	//toLoad.endAddress = *buffer->currentPtr;
	toLoad.state = PROCESS_NEW;
	toLoad.inputBufferBegin = *(ptrToJob);
	WORD *ptrInputBufferSize;
	ptrInputBufferSize = (WORD*)ram->allocate(4, true);
	ptrInputBufferSize = &toLoad.inputBufferSize;
	//buffer->allocate(toLoad.inputBufferSize);
	WORD *ptrOutputBufferSize;
	ptrOutputBufferSize = (WORD*)ram->allocate(4, true);
	ptrOutputBufferSize = &toLoad.outputBufferSize;
	//toLoad.outputBufferBegin = *(buffer->currentPtr + sizeof(WORD));
	WORD *ptrOutputBufferBegin;
	ptrOutputBufferBegin = (WORD*)ram->allocate(4, true);
	ptrOutputBufferBegin = &toLoad.outputBufferBegin;
	//buffer->allocate(toLoad.outputBufferSize);
	//jobs[toLoad.jobID] = toLoad;
	p_table->AssignPage(toLoad);	//maybe move all the above logic into the PageTable class?

	Enqueue(toLoad);
}

void Scheduler::LoadJobs()	//general method to call LoadToRAM until RAM is full or all jobs are loaded
{
	#define RAM_SIZE 256		//stubbed in until RAM is re-vamped, then can be changed...
	//while (buffer->currentPtr < (WORD*)RAM_SIZE && next_job < JOB_LIM)
	//{
	//	File* next = drive->findFile(next_job);
	//	//LoadToRAM((PCB)next);		//this won't work for the time being, but that's the general idea...
	//	next_job++;
	//}
}

void Scheduler::Swap(PCB x, PCB y)	//utility method to swap two items
{
	PCB tmp = x;
	x = y;
	y = tmp;
}

void Scheduler::SortQueue(std::vector<PCB> &toSort, int left, int right)	//sorts readyQueue by jobPriority - uses in-place quicksort
{		
	int i = left;
	int j = right;
	int pivot = ((left + right) / 2);

	while (i <= j)
	{
		while (toSort[i].jobPriority < toSort[pivot].jobPriority)
		{
			i++;
		}
		while (toSort[j].jobPriority > toSort[pivot].jobPriority)
		{
			j--;
		}
		if (i <= j)
		{
			Swap(toSort[i], toSort[j]);
			i++;
			j--;
		}
	}
	if (left < j)
	{
		SortQueue(toSort, left, j);
	}
	if (i > right)
	{
		SortQueue(toSort, i, right);
	}
}

void Scheduler::SJFSortQueue(std::vector<PCB> &toSort, int left, int right)		//essentially identical to SortQueue, but based on job size instead...
{
	int i = left;
	int j = right;
	int pivot = ((left + right) / 2);

	while (i <= j)
	{
		while (toSort[i].jobSize < toSort[pivot].jobSize)
		{
			i++;
		}
		while (toSort[j].jobSize > toSort[pivot].jobSize)
		{
			j--;
		}
		if (i <= j)
		{
			Swap(toSort[i], toSort[j]);
			i++;
			j--;
		}
	}
	if (left < j)
	{
		SJFSortQueue(toSort, left, j);
	}
	if (i > right)
	{
		SJFSortQueue(toSort, i, right);
	}
}

void Scheduler::FIFOSortQueue(std::vector<PCB> &toSort)
{
	//does this, strictly speaking, need to do anything?
}
