#include "dispatcher.h"


Dispatcher::Dispatcher()
{
}
Dispatcher::~Dispatcher()
{
}

WORD * Dispatcher::GetInstruction(PCB nextInst)
{	
	WORD *toReturn;
	toReturn = (WORD*)&nextInst.execAddress;
	return toReturn;
}

void Dispatcher::SetCPUParameters(PCB instr)
{

}

PCB Dispatcher::GetProcessState(PCB proc)
{
	return proc;
}

void Dispatcher::SetProcessState(PCB proc)
{

}
