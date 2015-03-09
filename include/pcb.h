/******************************************************
 * cpu.h - cpu class header
 * created 140223 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"
#include <iostream>
#include <cstring>

#if 0
class PCB{

public:
	int burstTime; //time to finish a process execution
	int processID; //unique identifier of a process
	String state; //either 'waiting', 'ready', or 'running'

public:
	PCB()//Constructor to initialize PCB contents
	{
		state = "Ready";
		burstTime = 5;
	}

	void addProcess(int PID)
	{
		std::cout << "Enter Burst Time ";
		cin >> burstTime;
		processID = PID;
	}

	void updateProcessBlock(string S)
	{
		state = S;
	}

	void executeProcess(int timeSlot)
	{
		std::cout << "Load the PCB of Process " << processID << endl;
		state = "Running";

		std::cout << "Process ID= " << processID << endl;
		std::cout << "State " << state << endl;
		std::cout << "Burstime " << burstTime << endl;

		if ((burstTime - timeSlot) > 0)
		{
			std::cout << "Remaining Time to finish " << (burstTime - timeSlot) << endl;
		}
		else
		{
			state = "Done";
			std::cout << "Process " << processID << " has finished and exited." << endl;
		}
	}
}
#endif

typedef struct CPUState
{
    WORD instruction;
    WORD program_counter;
    WORD registers;
} CPUState;

typedef struct SchedulerState
{

} SchedulerState;

typedef struct MemoryState
{

} MemoryState;

typedef struct Progeny
{

} Progeny;

typedef struct ProcessResources
{

} ProcessResources;

enum ProcessStatus
{
    PROCESS_RUNNING     = 0,
    PROCESS_READY       = 1,
    PROCESS_BLOCKED     = 2,
    PROCESS_NEW         = 3
};

typedef struct PCB
{

} PCB;
