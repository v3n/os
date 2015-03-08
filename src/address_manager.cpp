/******************************************************
 * address_manager.cpp - ram address calculation
 * created 140208 will owens ()
 ******************************************************/

#include <stdlib.h>
#include <iostream>

#include "address_manager.h"

AddressMgr::AddressMgr()
{	
}

WORD AddressMgr::GetNextFree()
{
	WORD * free = buffer;
	while (*free == NULL)
	{
		free++;
	}
	return free;
}

std::string AddressMgr::GetEffectiveAddress(std::string logAddHex, int baseReg)
{
	//Convert HEX address to DEC
	std::string logAddDec = BaseConverter::baseConvert(logAddHex, 16, 10);
	WORD computedLogAdd = std::stoul(logAddDec);
	//Compute Effective Address
	WORD effAdd = computedLogAdd + baseReg;
	std::string effAddStr = std::to_string(effAdd);
	//Convert from DEX to HEX and return
	std::string result = BaseConverter::baseConvert(effAddStr, 10, 16);
	return result;
}

void AddressMgr::AllocateMemory(WORD diskStart, int size, WORD *buffer, WORD *disk)
{	
	//Assumes word addressibility of RAM/Disk		
	if (memStart + size > 1024)
	{
		std::cout << "Insufficient RAM space to store process" << std::endl;
	}
	else if (memStart < 0 || diskStart < 0)
	{
		std::cout << "Invalid RAM/Disk address" << std::endl;
	}
	else
	{
		//Copy contents of Disk to appropriate location in RAM
		for (int i = memStart; i < memStart + size; i++)
		{
			buffer[i] = disk[i];			
		}		
	}
}

//void AddressMgr::DeallocateMemory(WORD memStart, int size, WORD *buffer)
//{	
//	for (int i = memStart; i < memStart + size; i++)
//	{
//		delete(buffer[i]);
//	}
//}


AddressMgr::~AddressMgr()
{
}
