#pragma once
#include <map>
#include <vector>
#include "utils.h"
#include "pcb.h"

class Scheduler
{
private:
	std::vector<PCB> jobQueue;
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> toSort, int left, int right);	

public:
	void Push(PCB next);
	PCB Peek();
	PCB Pop();
	Scheduler();
	~Scheduler();
};

