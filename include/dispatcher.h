#pragma once
#include "utils.h"
#include "pcb.h"
#include "cpu.h"
#include "scheduler.h"

class Dispatcher
{
public:
	Dispatcher();
	Dispatcher(Scheduler *s);
	~Dispatcher();
	PCB *next_process;
	Scheduler *long_term;

	WORD * GetInstruction(PCB nextInstr);
	void SetCPUParameters(PCB instr);
	PCB GetProcessInfo(int pID);	
	void GetNextProcess();
};

