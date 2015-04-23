/******************************************************
 * scheduler.cpp - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#include <map>

#include "utils.h"
#include "scheduler.h"

Scheduler::Scheduler()
{
	std::vector<PCB> nextQueue;
	//readyQueue.push_back(nextQueue);
}

Scheduler::~Scheduler()
{
}

void Scheduler::Enqueue(PCB next)	//insert a job into the readyQueue and re-sort
{
	readyQueue.push_back(next);
	SortQueue(readyQueue, 0, readyQueue.size() - 1);
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
	toLoad.startAddress = *buffer->currentPtr;
	toLoad.program_counter = toLoad.startAddress;	
	buffer->allocate(toLoad.programSize);
	toLoad.endAddress = *buffer->currentPtr;
	toLoad.state = PROCESS_NEW;

	toLoad.inputBufferBegin = *(buffer->currentPtr + sizeof(WORD));
	buffer->allocate(toLoad.inputBufferSize);
	toLoad.outputBufferBegin = *(buffer->currentPtr + sizeof(WORD));
	buffer->allocate(toLoad.outputBufferSize);
	//jobs[toLoad.jobID] = toLoad;

	Enqueue(toLoad);
}

void Scheduler::LoadJobs()	//general method to call LoadToRAM until RAM is full or all jobs are loaded
{
	//while room for jobs in RAM AND readyqueue not full
	//LoadToRAM(PCB of next job)
}

void Scheduler::Swap(PCB x, PCB y)	//utility method to swap two items
{
	PCB tmp = x;
	x = y;
	y = tmp;
}

void Scheduler::SortQueue(std::vector<PCB> &toSort, int left, int right)	//sorts readyQueue by priority - uses in-place quicksort
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
