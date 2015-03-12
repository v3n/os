/******************************************************
 * disk.cpp - Disk module implementation
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "hdd.h"
#include <cstring>
#include <cstdlib>
#include <stdexcept>

#define BUFFER_SIZE (2048 * sizeof(WORD))
#define FILE_SIZE(x) (x.programSize + x.inputBufferSize + x.outputBufferSize + x.tempBufferSize)

HDD::HDD()
{
	/* use c-style array memory allocation */
	buffer = new WORD[2048]();
}

HDD::~HDD()
{
	delete[] buffer;
}


void * HDD::newFile(size_t size)
{
    DLOG("[HDD] creating file with size %lu", size);

    files.push_back((File *)std::malloc(size));

    return files.back();
}

void * HDD::newFile(size_t id, void * data, size_t size)
{
#if 0
#if DEBUG
    if (id == 0)
        throw std::invalid_argument("id must not equal 0");
#endif
    File * fs;
    for (fs = (File *)buffer; fs->id == 0; fs += sizeof(File) + (FILE_SIZE((*fs)) * sizeof(WORD)));
    fs->id = id;
    fs->programSize = size;
    std::memcpy(fs + sizeof(File), data, size);

    return fs;
#endif
    return nullptr;
}

File * HDD::findFile(unsigned int id)
{
    return files[id];
}
