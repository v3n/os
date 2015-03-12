/******************************************************
 * disk.h - disk module definition
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdio>
#include <vector>

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
    std::vector<File *> files;

public:	
	HDD();
	~HDD();

    /* Allocate zero'd file */
    void * newFile(size_t);
    /* Allocate new file and copy data to it */
    void * newFile(size_t, void *, size_t);

    /* return pointer to file */
    File * findFile(unsigned int);
};

