/******************************************************
 * scheduler.h - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#pragma once
#include <map>
#include <vector>
#include "utils.h"
#include "pageTable.h"
#include "pcb.h"
#include "ram.h"
#include "hdd.h"

#define JOB_LIM 30	//max # of jobs in program file

class Scheduler
{
private:
	Ram *ram;	
	HDD *drive;
	PageTable *p_table;

	unsigned int next_job;
	std::vector<PCB> readyQueue;		
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> &toSort, int left, int right);	
	void SJFSortQueue(std::vector<PCB> &toSort, int left, int right);
	void FIFOSortQueue(std::vector<PCB> &toSort);
	void LoadToRAM(PCB toLoad);		
	void LoadJobs();

public:
	enum SchedulerMode {Priority, SJF, FIFO};
	SchedulerMode scheduler_mode;
	std::map<int, PCB> jobs;
	void Enqueue(PCB next);
	PCB *Peek();	
	PCB Dequeue();	
	Scheduler(SchedulerMode mode);
	Scheduler(int numCores);
	~Scheduler();
};

