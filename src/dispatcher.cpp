#include "dispatcher.h"


Dispatcher::Dispatcher()
{
	//next_process = nullptr;
}

Dispatcher::Dispatcher(Scheduler *s)
{
	long_term = s;
}

Dispatcher::~Dispatcher()
{
    
}

PCB Dispatcher::GetProcessInfo(int pID)	//returns PCB info based on given job ID
{
	return long_term->jobs[pID];
}

WORD * Dispatcher::GetInstruction(PCB nextInst)		//returns the instruction pointed by the given job's current PC value
{	
	WORD *toReturn;
	toReturn = (WORD*)nextInst.startAddress + (nextInst.program_counter * sizeof(WORD));
	nextInst.program_counter++;
	return toReturn;
}

void Dispatcher::GetNextProcess()		//returns the next process in the readyQueue
{
	next_process = long_term->Dequeue();
}

void Dispatcher::SetCPUParameters(PCB instr)		//ideally, sets CPU info before process begins
{
	// memcpy(CPU.state, PCB.CPUState, sizeof(CPUState));
}

