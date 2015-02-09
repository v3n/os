#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "disk.h"
class Loader
{
public:
	Loader(Disk &diskName);
	struct JobBlock{
		unsigned long id;
		unsigned long priority;
		unsigned long wordSize;
	};
	struct JobDataBlock{
		unsigned long inputBufferSize;
		unsigned long outputBufferSize;
		unsigned long tempBufferSize;
	};
	std::vector<Loader::JobBlock> jobOrder_v();
	std::string loadTextFile(const std::string &fileName);
	std::vector<std::string> parseString_v(std::string &fullString, std::string const &token);
	std::vector<Loader::JobBlock> loadJobBlock(const std::vector<std::string> &str);
	std::vector<Loader::JobDataBlock> loadJobDataBlock(const std::vector<std::string> &str);
};