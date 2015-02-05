#pragma once
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Loader
{
public:
	Loader();
	struct JobBlock{
		unsigned long id;
		unsigned long priority;
		unsigned long wordSize;
	}*pt_JB;
	struct JobDataBlock{
		unsigned long inputBufferSize;
		unsigned long outputBufferSize;
		unsigned long tempBufferSize;
	}*pt_JDB;
	std::vector<JobBlock> jobOrder_v();
	std::string loadTextFile(const std::string &fileName);
	std::vector<std::string> parseString_v(std::string &fullString, std::string const &token);
	std::vector<Loader::JobBlock> loadJobBlock(const std::vector<std::string> &str);
	std::vector<Loader::JobDataBlock> loadJobDataBlock(const std::vector<std::string> &str);
	~Loader();
};
