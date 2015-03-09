/******************************************************
 * scheduler.h - long term scheduler
 * created 150305 will owens ()
 ******************************************************/

#pragma once

#include <vector>

#include "pcb.h"
#include "ram.h"

class Scheduler
{
private:
	RAM buffer;
	std::vector<PCB> jobQueue;
	
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> &toSort, int left, int right);	
	void LoadToRAM(PCB toLoad);	

public:
	Scheduler();
	~Scheduler();
	
	void Enqueue(PCB next);
	PCB Peek();
	PCB Dequeue();
};

