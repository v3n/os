/******************************************************
 * cpu.h - cpu class header
 * created 140223 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"

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

};

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
