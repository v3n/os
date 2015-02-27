/******************************************************
 * ram.cpp - RAM module implementation
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <new>

#include "utils.h"
#include "ram.h"

#define BUFFER_SIZE (1024 * sizeof(WORD))

RAM::RAM()
{
    buffer = new WORD[1024];

    allocatedPtr = buffer;
}

RAM::~RAM()
{
    delete[] buffer;
}

void * RAM::malloc(size_t size)
{
    void * ReturnPtr = allocatedPtr;
    allocatedPtr += size * sizeof(WORD);

    if ( allocatedPtr > (buffer + BUFFER_SIZE) )
        throw std::bad_alloc();
    return ReturnPtr;
}

void * RAM::calloc(size_t number, size_t size)
{
    void * ReturnPtr = allocatedPtr;
    allocatedPtr += (size * number) * sizeof(WORD);
    if ( allocatedPtr > (buffer + BUFFER_SIZE) )
        throw std::bad_alloc();
    return ReturnPtr;
}

void * RAM::realloc(void * memory, size_t size)
{
    this->free(memory);
    return this->malloc(size);
}

void RAM::free(void * memory)
{

}

#undef BUFFER_SIZE
