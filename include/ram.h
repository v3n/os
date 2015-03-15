/******************************************************
 * ram.h - RAM module definition
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"

#pragma once

class RAM
{
private:
    WORD * buffer;
    WORD * allocatedPtr;
	WORD * effectiveAddress(WORD * logAddress, int baseRegister);

	typedef struct RAMStruct
	{
		uint8_t size;
		WORD * next;
	} RAMStruct;

public: 
    RAM();
    ~RAM();

	WORD * currentPtr;	
    void * malloc(std::size_t);
    void * calloc(std::size_t, std::size_t);
    void * realloc(void *, std::size_t);
    void free(void *);
	void * alloc();
};
