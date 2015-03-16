/******************************************************
 * ram.cpp - RAM module implementation
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <new>
#include <cstdint>
#include <cmath>

#include "ram.h"

#define BUFFER_SIZE (1024 * sizeof(WORD))
#define blockSize(i) (1 << i)

RAM::RAM()
{
    buffer = new WORD[1024]();

    allocatedPtr = buffer;
	currentPtr = allocatedPtr;
}

RAM::~RAM()
{
    delete[] buffer;
}

WORD * RAM::allocate(std::size_t size)
{
	RAMStruct * bestBlock = nullptr;

    /* find the best-fit order */
    unsigned int order = 1;
    while ( blockSize(order) < (size + sizeof(RAMStruct)) )
    {
        order++;
    }

	for (RAMStruct * p = (RAMStruct *)buffer; p != (RAMStruct *)(buffer + 1024); p += blockSize(p->size))
	{
		if (p->isFree)
		{
			if ((size + sizeof(RAMStruct)) < (1 << p->size) && (!bestBlock || p->size < bestBlock->size))
			{
				bestBlock = p;
			}
		}
	}

	if (!bestBlock)
	{
		throw std::bad_alloc();
	}
	else
	{
		bestBlock->isFree = true;
        DLOG("[RAM] allocating %lu words at address %p", size, (void*)((WORD *)((char *)bestBlock + sizeof(RAMStruct)) - (WORD *)buffer));
		return (WORD *)((char *)bestBlock + sizeof(RAMStruct));
	}

	return nullptr;
}

void RAM::deallocate(void * memory)
{

}

#undef BUFFER_SIZE
