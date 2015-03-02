/******************************************************
 * disk.cpp - Disk module implementation
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "hdd.h"
#include <cstring>
#include <stdexcept>

#define BUFFER_SIZE (2048 * sizeof(WORD))

HDD::HDD()
{
	/* use c-style array memory allocation */
	buffer = new WORD[2048]();
}

HDD::~HDD()
{
	delete[] buffer;
}

void * HDD::newFile(unsigned int id, void * data, size_t size)
{
#if DEBUG
    if (id == 0)
        throw std::invalid_argument("id must not equal 0");
#endif
    FileSystem * fs;
    for (fs = (FileSystem *)buffer; fs->id == 0; fs += sizeof(FileSystem) + fs->size);
    fs->id = id;
    fs->size = size;
    std::memcpy(fs + sizeof(FileSystem), data, size);

    return fs;
}

FileSystem * HDD::findFile(unsigned int id)
{
    for (FileSystem * fs = (FileSystem *)buffer; fs->id == 0; fs += sizeof(FileSystem) + fs->size)
    {
        if (fs->id == id)
        {
            return fs;
        }
    }
    return nullptr;
}
