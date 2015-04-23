/******************************************************
 * scheduler.h - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#pragma once
#include <map>
#include <vector>
#include "utils.h"
#include "pcb.h"
#include "ram.h"
#include "hdd.h"

#define JOB_LIM 30	//max # of jobs in program file

class Scheduler
{
private:
	RAM *buffer;	
	HDD *drive;
	unsigned int next_job;
	std::vector<PCB> readyQueue;	
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> &toSort, int left, int right);	
	void LoadToRAM(PCB toLoad);		
	void LoadJobs();

public:
	std::map<int, PCB> jobs;
	void Enqueue(PCB next);
	PCB *Peek();	
	PCB Dequeue();	
	Scheduler();
	Scheduler(int numCores);
	~Scheduler();
};

