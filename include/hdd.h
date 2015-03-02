/******************************************************
 * disk.h - disk module definition
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdio>

#include "utils.h"

 /* O(n) traversal */
 typedef struct FileSystem
 {
     unsigned int id;
     size_t size;
 } FileSystem;
 

class HDD
{
private:
	WORD * buffer;

public:	
	HDD();
	~HDD();

    /* Allocate zero'd file */
    void * newFile(size_t);
    /* Allocate new file and copy data to it */
    void * newFile(unsigned int, void *, size_t);

    /* return pointer to file */
    FileSystem * findFile(unsigned int);
};

