/******************************************************
 * cpu.h - cpu class header
 * created 150223 jonathan howard (j@hovverd.com)
 ******************************************************/
#pragma once
#include "utils.h"
#include <iostream>
#include <cstring>

typedef struct CPUState
{
    WORD instruction;
    WORD program_counter;
    WORD registers[16];
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
    PROCESS_WAITING     = 2,
    PROCESS_NEW         = 3,
	PROCESS_FINISHED	= 4
};

typedef struct PCB
{
	ProcessStatus state;
	CPUState cpuState;
	unsigned int jobPriority;
	unsigned int jobID;
	unsigned int inputBufferSize;
	unsigned int outputBufferSize;
	WORD startAddress, endAddress, program_counter;	
	WORD inputBufferBegin, outputBufferBegin;
	WORD programSize;
} PCB;
