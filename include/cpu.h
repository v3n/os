/******************************************************
 * cpu.h - cpu class header
 * created 150202 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"
#include "pcb.h"

#include <boost/thread.hpp>

#pragma once

enum CPU_STATE {
    CPU_WORKING,
    CPU_IDLE,
    CPU_IO
};

class CPU
{
private:
    void idle();

    /* boost::thread requires a callable object */
    void runloop();

public:
    /* register memory in hardware, simluating hardware cache */ 
    CPUState state;
    
    CPU_STATE ReadyState;

    boost::thread thread;
    boost::mutex mutex;
    boost::condition_variable cv;
    boost::unique_lock<boost::mutex> lock;

    CPU();
    ~CPU();

    explicit operator WORD*() const;

    void fetch(const WORD *);
    void * decode();
};
