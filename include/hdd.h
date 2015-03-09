/******************************************************
 * disk.h - disk module definition
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdio>

#include "utils.h"

/* O(n) traversal */
typedef struct File
{
    unsigned int id;
    size_t programSize;
    unsigned int priority;
    size_t inputBufferSize;
    size_t outputBufferSize;
    size_t tempBufferSize;
} File;

 class HDD
{
private:
	WORD * buffer;

public:	
	HDD();
	~HDD();

    /* Allocate zero'd file */
    void * const newFile(size_t);
    /* Allocate new file and copy data to it */
    void * const newFile(unsigned int, void *, size_t);

    /* return pointer to file */
    File * findFile(unsigned int);
};

