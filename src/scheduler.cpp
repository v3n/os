#include "scheduler.h"

scheduler::scheduler()
{
	
}
scheduler::~scheduler()
{
}
void scheduler::Push(PCB next)
{
	jobQueue.push_back(next);
	SortQueue(jobQueue, 0, jobQueue.size() - 1);
}
PCB scheduler::Peek()
{
	return jobQueue.front();
}
PCB scheduler::Pop()
{
	PCB result = jobQueue.front();
	jobQueue.erase(jobQueue.begin());
	SortQueue(jobQueue, 0, jobQueue.size() - 1);
	return result;
}

void scheduler::Swap(PCB x, PCB y)
{
	PCB tmp = x;
	x = y;
	y = tmp;
}

void scheduler::SortQueue(std::vector<PCB> toSort, int left, int right)
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


