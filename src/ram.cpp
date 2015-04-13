/******************************************************
 * ram.cpp - RAM module implementation
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <new>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <functional>

#include <iostream>

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
    for (order = 0; blockSize( order ) - sizeof(BlockTag) < size; order++);

    /* find best fit block to allocate in */
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
        /* subdividing block */
        while(bestBlock->order != order)
        { 
            bestBlock->order--;
            BlockTag * friendBlock = (BlockTag *)((char *)bestBlock + blockSize( bestBlock->order ) * sizeof(WORD));
            
            friendBlock->order = bestBlock->order;
            friendBlock->isFree = true;

            DLOG("[RAM] splitting block of order %i at relative address %p", bestBlock->order, (void*)((WORD *)((char *)bestBlock + sizeof(BlockTag)) - (WORD *)buffer));

            /* push smaller allocations to end */
            bestBlock = friendBlock;
        }

        bestBlock->isFree = false;
        DLOG("[RAM] allocating %lu words at relative address %p", size, (void*)((WORD *)((char *)bestBlock + sizeof(BlockTag)) - (WORD *)buffer));
        return (WORD *)((char *)bestBlock + sizeof(BlockTag));
    }

	return nullptr;
}

void RAM::deallocate(void * memory)
{
    if ( memory == nullptr )
    {
        return;
    }

    BlockTag * block = (BlockTag *)((char *)memory - sizeof(BlockTag));
    BlockTag * buddy = (BlockTag *)((intptr_t)block ^ blockSize( ((BlockTag *)block)->order) );

    uint8_t freeingOrder = block->order;

    /* combining blocks */
    if ( buddy->isFree ) 
    {
        freeingOrder++;

        BlockTag * firstBlock;

        std::less<void *> lss;

        if ( lss(buddy, block) ) // | buddy | block |
        {
            firstBlock = (BlockTag *)buddy;
        }
        else // | block | buddy |
        {
            firstBlock = (BlockTag *)block;
        }
        /* Zero both blocks simultaneously */
        memset(firstBlock, 0, blockSize( freeingOrder ) * sizeof(WORD));

        firstBlock->isFree = true;
        firstBlock->order = freeingOrder;

        DLOG("[RAM] deallocating %i words by combining blocks at relative addresses %p and %p", blockSize(freeingOrder), block, buddy);
    }
    else /* freeing a single block */
    {
        memset(block, 0, blockSize( freeingOrder ) * sizeof(WORD));
        block->isFree = true;
        block->order  = freeingOrder;

        DLOG("[RAM] deallocating %i words in single block at %p", blockSize( freeingOrder ), block);
    }

    std::cout << buffer << std::endl << block << std::endl << buddy << std::endl << block - buddy << std::endl;
}   

#undef BUFFER_SIZE
