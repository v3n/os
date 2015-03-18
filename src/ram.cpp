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
    /* 2^9 (512) word base allocation */
    ((BlockTag *)buffer)->order = 9;
    ((BlockTag *)(buffer + blockSize(9)))->order = 9;

    ((BlockTag *)buffer)->isFree = true;
    ((BlockTag *)(buffer + blockSize(9)))->isFree = true;
}

RAM::~RAM()
{
    delete[] buffer;
}

WORD * RAM::allocate(std::size_t size)
{
	BlockTag * bestBlock = nullptr;

    /* calculate order for best fit, this is ceil(log2(size))  */
    unsigned int order = 1;
    for (order = 0; blockSize( order ) < size; order++);

    
    /* find */
	for (BlockTag * p = (BlockTag *)buffer; p != (BlockTag *)(buffer + 1024); p += blockSize(p->order))
	{
		if (p->isFree)
		{
			if ( order <= p->order )
			{
                /* select block if we don't have one otherwise best fit */
                if ( bestBlock == nullptr || p->order < bestBlock->order )
                {
				    bestBlock = p;
                }
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
        DLOG("[RAM] allocating %lu words at address %p", size, (void*)((WORD *)((char *)bestBlock + sizeof(BlockTag)) - (WORD *)buffer));
		return (WORD *)((char *)bestBlock + sizeof(BlockTag));
	}

	return nullptr;
}

void RAM::deallocate(void * memory)
{
    WORD * block = (WORD *)((char *)memory - sizeof(BlockTag));
    WORD * buddy = (WORD *)((intptr_t)block ^ blockSize( ((BlockTag *)block)->order) );

}

#undef BUFFER_SIZE
