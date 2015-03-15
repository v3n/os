/******************************************************
 * ram.cpp - RAM module implementation
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <new>
#include <cstdint>

#include "ram.h"

#define BUFFER_SIZE (1024 * sizeof(WORD))

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

void * RAM::malloc(std::size_t size)
{
    void * ReturnPtr = allocatedPtr;
    allocatedPtr += size * sizeof(WORD);

    DLOG("[RAM] allocating %lu words at address %p", size, (void*)((WORD *)ReturnPtr - (WORD *)buffer));

    if ( allocatedPtr > (buffer + BUFFER_SIZE) )
        throw std::bad_alloc();
    return ReturnPtr;
}

void * RAM::calloc(std::size_t number, std::size_t size)
{
    return this->malloc(number * size * sizeof(WORD));
}

void * RAM::realloc(void * memory, std::size_t size)
{
    this->free(memory);
    return this->malloc(size);
}

WORD * RAM::effectiveAddress(WORD * logAddress, int baseRegister)
{
	return logAddress + baseRegister;

	/*std::string logAddDec = BaseConverter::baseConvert(logAddHex, 16, 10);
	WORD computedLogAdd = std::stoul(logAddDec);
	WORD effAdd = computedLogAdd + baseReg;
	std::string effAddStr = std::to_string(effAdd);
	std::string result = BaseConverter::baseConvert(effAddStr, 10, 16);
	return result;*/
}

WORD * RAM::alloc(std::size_t size)
{
	//starts with 1024 words
	struct block
	{

	} block;
	//if size is <1024, then divide in half
	std::size_t newSize;
	newSize = 1024;
	while (size < newSize)
	{
		newSize = newSize / 2;
	}
	return *NULL;
	//divide in half
	//divide in half
	//first 128 words reserved for OS
	//returns pointer to location for item to be stored
}

void RAM::free(void * memory)
{

}

#undef BUFFER_SIZE
