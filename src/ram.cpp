/******************************************************
 * ram.cpp - RAM module implementation
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <new>

#include "ram.h"

#define BUFFER_SIZE (1024 * sizeof(WORD))

RAM::RAM()
{
    buffer = new WORD[1024]();

    allocatedPtr = buffer;
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

WORD RAM::EffectiveAddress(WORD logAddress, int baseRegister)
{
	return logAddress + baseRegister;

	/*std::string logAddDec = BaseConverter::baseConvert(logAddHex, 16, 10);
	WORD computedLogAdd = std::stoul(logAddDec);
	WORD effAdd = computedLogAdd + baseReg;
	std::string effAddStr = std::to_string(effAdd);
	std::string result = BaseConverter::baseConvert(effAddStr, 10, 16);
	return result;*/
}

void RAM::free(void * memory)
{

}

#undef BUFFER_SIZE
