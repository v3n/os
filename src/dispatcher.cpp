#include "dispatcher.h"


Dispatcher::Dispatcher()
{
	next_process = nullptr;
}
Dispatcher::~Dispatcher()
{
}

WORD * Dispatcher::GetInstruction(PCB nextInst, WORD pc)
{	
	WORD *toReturn;
	nextInst.program_counter += pc;	//pass in CPU's program_counter value to get current instruction
	toReturn = (WORD*)&nextInst.program_counter;
	return toReturn;
}

void Dispatcher::GetNextProcess()
{
	next_process = scheduler->Peek();
}

void Dispatcher::SetCPUParameters(PCB instr)
{

}

PCB Dispatcher::GetProcessState(PCB proc)
{
	return proc;
}

void Dispatcher::SetProcessState(PCB proc, PCB toCopy)
{

}
