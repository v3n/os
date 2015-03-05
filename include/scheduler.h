#pragma once
#include <map>
#include <vector>
#include "include\utils.h"
#include "pcb.h"

class scheduler
{
private:
	std::vector<PCB> jobQueue;
	void Swap(PCB x, PCB y);
	void SortQueue(std::vector<PCB> toSort, int left, int right);	

public:
	void Push(PCB next);
	PCB Peek();
	PCB Pop();
	scheduler();
	~scheduler();
};

