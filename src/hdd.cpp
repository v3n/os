/******************************************************
 * disk.cpp - Disk module implementation
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "hdd.h"

HDD::HDD()
{
	/* use c++-style memory allocation */
	buffer = new WORD[1024]();
}

HDD::~HDD()
{
	delete[] buffer;
}

