/******************************************************
 * cpu.h - cpu class header
 * created 150202 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"
#include "pcb.h"

#include <boost/thread.hpp>

enum CPU_STATE {
    CPU_WORKING,
    CPU_IDLE,
    CPU_IO
};

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
