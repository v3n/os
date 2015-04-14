#include "dispatcher.h"


Dispatcher::Dispatcher()
{
	//next_process = nullptr;
}
Dispatcher::~Dispatcher()
{
}

PCB Dispatcher::GetProcessInfo(int pID)
{
	//return Scheduler::jobs[pID];
	PCB tmp;	//stubbed in to fix build
	return tmp;
}

WORD * Dispatcher::GetInstruction(PCB nextInst)
{	
	WORD *toReturn;
	toReturn = (WORD*)nextInst.startAddress + (nextInst.program_counter * sizeof(WORD));
	nextInst.program_counter++;
	return toReturn;
}

void Dispatcher::GetNextProcess()
{
	//next_process = scheduler->Peek();
}

void Dispatcher::SetCPUParameters(PCB instr)
{
	// memcpy(CPU.state, PCB.CPUState, sizeof(CPUState));
}

