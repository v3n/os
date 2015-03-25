#pragma once

#include <fstream>

#include "utils.h"
#include "hdd.h"

class Loader
{
private:
	void ReadtoPCB(File toRead);
public:
	Loader(std::string, HDD *);
};
