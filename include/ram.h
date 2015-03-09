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
	WORD EffectiveAddress(WORD logAddress, int baseRegister);


public: 
    RAM();
    ~RAM();

    void * malloc(std::size_t);
    void * calloc(std::size_t, std::size_t);
    void * realloc(void *, std::size_t);
    void free(void *);
};
