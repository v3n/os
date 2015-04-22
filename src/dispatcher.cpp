#include "dispatcher.h"


Dispatcher::Dispatcher()
{
	next_process = nullptr;
}
Dispatcher::~Dispatcher()
{
}

PCB Dispatcher::GetProcessInfo(Scheduler next, int pID)
{
	return next.jobs[pID];
}

WORD * Dispatcher::GetInstruction(PCB nextInst)
{	
	WORD *toReturn;
	toReturn = (WORD*)nextInst.startAddress + (nextInst.program_counter * sizeof(WORD));
	nextInst.program_counter++;
	return toReturn;
}

void Dispatcher::GetNextProcess(Scheduler next)
{
	next_process = next.Peek();
}

void Dispatcher::SetCPUParameters(PCB instr)
{
	// memcpy(CPU.state, PCB.CPUState, sizeof(CPUState));
}

