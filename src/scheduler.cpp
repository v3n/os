/******************************************************
 * scheduler.cpp - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#include <map>

#include "scheduler.h"

Scheduler::Scheduler(SchedulerMode mode)
{
	scheduler_mode = mode;
	next_job = 0;

	readyQueue = new std::vector<PCB>();
}
Scheduler::Scheduler(PageTable *p, HDD *h)
{
	p_table = p;
	drive = h;
	scheduler_mode = POLICY_FIFO;

	readyQueue = new std::vector<PCB>();
}

Scheduler::~Scheduler()
{
}

void Scheduler::Enqueue(PCB next)	//insert a job into the readyQueue and re-sort based on scheduling policy
{
	readyQueue->push_back(next);
	switch (scheduler_mode)
	{
	case POLICY_Priority:
		SortQueue(*readyQueue, 0, readyQueue->size() - 1);
		break;
	case POLICY_SJF:
		SJFSortQueue(*readyQueue, 0, readyQueue->size() - 1);
		break;
	case POLICY_FIFO:
		FIFOSortQueue(*readyQueue);
		break;
	}
	
}

PCB * Scheduler::Peek()			//return the job at the front of the readyQueue
{	
	if ( readyQueue->size() == 0 )
		return nullptr;
	return &readyQueue->back();
}

void Scheduler::Dequeue()		//remove and return the job at the front of the readyQueue
{	
	if ( readyQueue->size() == 0)
		return;

	PCB result = readyQueue->back();
	readyQueue->pop_back();
	switch (scheduler_mode)
	{
	case POLICY_Priority:
		SortQueue(*readyQueue, 0, readyQueue->size() - 1);
		break;
	case POLICY_SJF:
		SJFSortQueue(*readyQueue, 0, readyQueue->size() - 1);
		break;
	case POLICY_FIFO:
		FIFOSortQueue(*readyQueue);
		break;
	}
}

void Scheduler::SetSchedulingMode(SchedulerMode mode)
{
	scheduler_mode = mode;
}

void Scheduler::LoadToRAM(PCB toLoad)	//copies job to RAM and stores addressing information in that job's PCB
{		
	// p_table->AssignPage(toLoad);	//handles the ram allocation logic

	Enqueue(toLoad);
}

void Scheduler::LoadJobs()	//general method to call LoadToRAM until RAM is full or all jobs are loaded
{		
	for (size_t i = 0; i < drive->files.size(); i++)
	{
		File *next_file = drive->findFile(i);
		PCB next_proc = PCB();

		next_proc.jobID = next_file->id;
		next_proc.jobSize = next_file->programSize;
		next_proc.jobPriority = next_file->priority;

		LoadToRAM(next_proc);
		jobs[next_proc.jobID] = next_proc;			//save PCB info in internal map
		
	}
}

void Scheduler::Swap(PCB x, PCB y)	//utility method to swap two items
{
	PCB tmp = x;
	x = y;
	y = tmp;
}

void Scheduler::SortQueue(std::vector<PCB> & toSort, int left, int right)	//sorts readyQueue by jobPriority - uses in-place quicksort
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

void Scheduler::SJFSortQueue(std::vector<PCB> & toSort, int left, int right)		//essentially identical to SortQueue, but based on job size instead...
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

void Scheduler::FIFOSortQueue(std::vector<PCB> &)
{
	//does this, strictly speaking, need to do anything?
}
