#pragma once
#include "utils.h"
#include "pcb.h"
#include "scheduler.h"

class Dispatcher
{
public:
	Dispatcher();
	~Dispatcher();

	WORD * GetInstruction(PCB nextInstr);
	void SetCPUParameters(PCB instr);

private:
	PCB  GetProcessState(PCB proc);
	void SetProcessState(PCB proc);
};

