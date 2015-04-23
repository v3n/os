//EMB
#pragma once
#include <malloc.h>
#include <iostream>
class Ram{
public:
	Ram(unsigned long blockNum = 64, unsigned long blockSize = 16); //total 1024
	~Ram();

	void *allocate(unsigned long size, bool useMemPool = true);
	void free(void *p);

private:
	struct LinkedList{
		struct LinkedList *prev, *next;
	};
	void *memBlock;
	LinkedList *allocatedMemBlockLL;
	LinkedList *freeMemBlockLL;
	unsigned long memPoolSize;
	unsigned long memBlockSize;
};



///******************************************************
// * ram.h - RAM module definition
// * created 150204 jonathan howard (j@hovverd.com)
// ******************************************************/
//
//#include "utils.h"
//
//#pragma once
//
//class RAM
//{
//private:
//    WORD * buffer;
//	WORD * effectiveAddress(WORD * logAddress, int baseRegister);
//
//	typedef struct BlockTag
//	{
//		uint8_t order;
//		bool isFree;
//	} BlockTag;
//
//public: 
//    RAM();
//    ~RAM();
//
//	WORD * currentPtr;	
//    WORD * allocate(std::size_t size);
//    void deallocate(void *);
//};
