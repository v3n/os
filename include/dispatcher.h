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
	//static PCB *next_process;
	//static Scheduler *scheduler;

	WORD * GetInstruction(PCB nextInstr);
	void SetCPUParameters(PCB instr);
	PCB GetProcessInfo(int pID);	
	static void GetNextProcess();
};

