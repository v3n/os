#pragma once
#include "utils.h"
#include "ram.h"
#include "baseconverter.h"

class AddressMgr
{
private:
	WORD *currentIndex;
	WORD *GetNextFree();

public:
	AddressMgr();

	std::string GetEffectiveAddress(std::string logAddHex, int baseReg);
    #if 0 
	void AllocateMemory(WORD diskStart, WORD memStart, int size, WORD *buffer, WORD *disk);
	void DeallocateMemory(WORD memStart, int size, WORD *buffer);
    #endif
	~AddressMgr();
};

