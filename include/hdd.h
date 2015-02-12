/******************************************************
 * disk.h - disk module definition
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"

#pragma once

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
    void * newFile(void *, size_t);
};

