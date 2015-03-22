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

void Scheduler::Enqueue(PCB next)
{
	readyQueue.push_back(next);
	SortQueue(readyQueue, 0, readyQueue.size() - 1);
}

PCB *Scheduler::Peek()
{
	int nextQueue = GetShortestQueue();
	return &readyQueue.back();
}

PCB Scheduler::Dequeue()
{
	int nextQueue = GetShortestQueue();
	PCB result = readyQueue.back();
	readyQueue.erase(readyQueue.end());
	SortQueue(readyQueue, 0, readyQueue.size() - 1);
	return result;
}


void Scheduler::LoadToRAM(PCB toLoad)
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

	Enqueue(toLoad);
}

void Scheduler::Swap(PCB x, PCB y)
{
	PCB tmp = x;
	x = y;
	y = tmp;
}

//int Scheduler::GetShortestQueue()
//{
//	int shortest_index = 0;
//	int shortest = readyQueues[0].size();
//	for (int i = 0; i < readyQueues.size(); i++)
//	{
//		if (readyQueues[i].size() < shortest)
//		{
//			shortest = readyQueues[i].size();
//			shortest_index = i;
//		}
//	}
//	return shortest_index;
//}

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
