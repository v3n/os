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
		bool isFree;
	} RAMStruct;

public: 
    RAM();
    ~RAM();

	WORD * currentPtr;	
    WORD * allocate(std::size_t size);
    void deallocate(void *);
};
