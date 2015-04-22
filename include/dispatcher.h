#pragma once
#include "utils.h"
#include "pcb.h"
#include "cpu.h"
#include "scheduler.h"

class Dispatcher
{
public:
	Dispatcher();
	~Dispatcher();
	PCB *next_process;

	WORD * GetInstruction(PCB nextInstr);
	void SetCPUParameters(PCB instr);
	PCB GetProcessInfo(Scheduler next, int pID);	
	void GetNextProcess(Scheduler next);
};

