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


void * const HDD::newFile(unsigned int id)
{
    File * fs;
    for (fs = (File *)buffer; fs->id == 0; fs += sizeof(File) + fs->size);

    return fs;
}

void * const HDD::newFile(unsigned int id, void * data, size_t size)
{
#if DEBUG
    if (id == 0)
        throw std::invalid_argument("id must not equal 0");
#endif
    File * fs;
    for (fs = (File *)buffer; fs->id == 0; fs += sizeof(File) + fs->size);
    fs->id = id;
    fs->size = size;
    std::memcpy(fs + sizeof(File), data, size);

    return fs;
}

File * HDD::findFile(unsigned int id)
{
    for (File * fs = (File *)buffer; fs->id == 0; fs += sizeof(File) + fs->size)
    {
        if (fs->id == id)
        {
            return fs;
        }
    }
    return nullptr;
}
