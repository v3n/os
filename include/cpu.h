/******************************************************
 * cpu.h - cpu class header
 * created 150202 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"
#include "pcb.h"

class CPU
{
private:
    /* register memory in hardware, simluating hardware cache */ 
    CPUState state;

public:
    CPU();
    ~CPU();

    explicit operator WORD*() const;

    void fetch(const WORD *);
    void * decode();
};
