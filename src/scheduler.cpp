#include "scheduler.h"

//#if 0
Scheduler::Scheduler()
{	
}
Scheduler::~Scheduler()
{
}
void Scheduler::Enqueue(PCB next)
{
	jobQueue.push_back(next);
	SortQueue(jobQueue, 0, jobQueue.size() - 1);
}
PCB Scheduler::Peek()
{
	return jobQueue.back();
}
PCB Scheduler::Dequeue()
{
	PCB result = jobQueue.back();
	jobQueue.erase(jobQueue.end());
	SortQueue(jobQueue, 0, jobQueue.size() - 1);
	return result;
}

void Scheduler::LoadToRAM(PCB toLoad)
{	
	/*toLoad.startAddress = *RAM::currentPtr;
	malloc(toLoad.programSize);
	toLoad.endAddress = *RAM::currentPtr;
	toLoad.state = PROCESS_NEW;

	toLoad.inputBufferBegin = *(RAM::currentPtr + sizeof(WORD));
	malloc(toLoad.inputBufferSize);
	toLoad.outputBufferBegin = *(RAM::currentPtr + sizeof(WORD));
	malloc(toLoad.outputBufferSize);*/

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
//#endif

