/******************************************************
 * ram.h - RAM module definition
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"

#pragma once

class RAM
{
private:
    WORD * buffer;

    WORD * allocatedPtr;

public: 
    RAM();
    ~RAM();

    void * malloc(size_t);
    void * calloc(size_t, size_t);
    void * realloc(void *, size_t);
    void free(void *);
};
