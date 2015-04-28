/******************************************************
 * cpu.h - cpu class header
 * created 150202 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"
#include "pcb.h"


#ifdef __APPLE__
#include <boost/thread.hpp>
#elif _WIN32
#include <boost\thread.hpp>
#endif

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
    unsigned int ReadyState;

    boost::thread thread;
    boost::condition_variable cv;
    boost::unique_lock<boost::mutex> mutex;

    void idle();

    /* boost::thread requires a callable object */
    void runloop();

public:
    CPU();
    ~CPU();

    explicit operator WORD*() const;

    void fetch(const WORD *);
    void * decode();
};
