/******************************************************
 * ram.cpp - RAM module implementation
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "utils.h"
#include "ram.h"

RAM::RAM()
{
    buffer = new WORD[1024];
}

RAM::~RAM()
{
    delete[] buffer;
}

