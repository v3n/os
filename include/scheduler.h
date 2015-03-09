#pragma once
#include <map>
#include <vector>
#include "utils.h"
#include "pcb.h"
#include "ram.h"

class Scheduler
{
private:
	std::vector<PCB> jobQueue;
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> &toSort, int left, int right);	
	void LoadToRAM(PCB toLoad);	

public:
	void Enqueue(PCB next);
	PCB Peek();
	PCB Dequeue();
	Scheduler();
	~Scheduler();
};

