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

class Scheduler
{
private:
	RAM *buffer;
	std::map<int, PCB> jobs;
	std::vector<PCB> readyQueue;	
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> &toSort, int left, int right);	
	void LoadToRAM(PCB toLoad);	
	int GetShortestQueue();

public:
	void Enqueue(PCB next);
	PCB *Peek();	
	PCB Dequeue();	
	Scheduler();
	Scheduler(int numCores);
	~Scheduler();
};

