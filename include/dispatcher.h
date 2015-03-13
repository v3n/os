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
	Scheduler *scheduler;

	WORD * GetInstruction(PCB nextInstr, WORD pc);
	void SetCPUParameters(PCB instr);

private:
	PCB GetProcessState(PCB proc);
	void GetNextProcess();
	void SetProcessState(PCB proc, PCB toCopy);
};

