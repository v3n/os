#include "scheduler.h"

Scheduler::Scheduler()
{
	
}
Scheduler::~Scheduler()
{
}
void Scheduler::Push(PCB next)
{
	jobQueue.push_back(next);
	SortQueue(jobQueue, 0, jobQueue.size() - 1);
}
PCB Scheduler::Peek()
{
	return jobQueue.back();
}
PCB Scheduler::Pop()
{
	PCB result = jobQueue.back();
	jobQueue.erase(jobQueue.end());
	SortQueue(jobQueue, 0, jobQueue.size() - 1);
	return result;
}

void Scheduler::LoadtoRAM(PCB toLoad)
{
	currentIndex = GetNextFree();
	toLoad.memAddress = *currentIndex;
	AllocateMemory(toLoad.diskAddress, toLoad.memAddress, toLoad.jobLength, RAM_buffer, HDD_buffer);	//stubbed arguments until PCB class is available
	toLoad.endAddress = *currentIndex;
	toLoad.currentState = JobState.WAITING;
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
		while (toSort[i].priority < toSort[pivot].priority)
		{
			i++;
		}
		while (toSort[j].priority > toSort[pivot].priority)
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


