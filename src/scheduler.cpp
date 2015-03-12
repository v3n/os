/******************************************************
 * scheduler.cpp - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#include <map>

#include "utils.h"
#include "scheduler.h"

Scheduler::Scheduler()
{

}

Scheduler::~Scheduler()
{

}

void Scheduler::Enqueue(PCB next)
{
	readyQueue.push_back(next);
	SortQueue(readyQueue, 0, readyQueue.size() - 1);
}

PCB Scheduler::Peek()
{
	return readyQueue.back();
}

PCB Scheduler::Dequeue()
{
	PCB result = readyQueue.back();
	readyQueue.erase(readyQueue.end());
	SortQueue(readyQueue, 0, readyQueue.size() - 1);
	return result;
}

void Scheduler::LoadToRAM(PCB toLoad)
{	
	toLoad.startAddress = *buffer.currentPtr;
	toLoad.execAddress = toLoad.startAddress;	//Currently pointed instruction
	buffer.malloc(toLoad.programSize);
	toLoad.endAddress = *buffer.currentPtr;
	toLoad.state = PROCESS_NEW;

	toLoad.inputBufferBegin = *(buffer.currentPtr + sizeof(WORD));
	buffer.malloc(toLoad.inputBufferSize);
	toLoad.outputBufferBegin = *(buffer.currentPtr + sizeof(WORD));
	buffer.malloc(toLoad.outputBufferSize);

	Enqueue(toLoad);
}

void Scheduler::Swap(PCB x, PCB y)
{
	PCB tmp = x;
	x = y;
	y = tmp;
}

void Scheduler::SortQueue(std::vector<PCB> &toSort, int left, int right)
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
