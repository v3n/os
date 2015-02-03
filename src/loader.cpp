#include "loader.h"


Loader::Loader()
{
}
std::string Loader::loadTextFile(const std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	std::string output;
	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + '\n');
		}
	}
	else
	{
		std::cout << "Unable to load file: " << fileName << '\n';
	}
	return output;
}
//splits the string into individual lines and adds each line to a vector
std::vector<std::string> Loader::parseString_v(std::string &fullStr, std::string const &token){
	std::vector<std::string> result;
	std::string temp;
	std::istringstream ss(fullStr);
	while (std::getline(ss, temp)){
		if (strstr(temp.c_str(), token.c_str())){
			result.push_back(temp);
		}
	}
	return result;
}
std::vector<std::string> splitInit(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	splitInit(s, delim, elems);
	return elems;
}
std::vector<Loader::JobBlock> Loader::loadJobBlock(const std::vector<std::string> &str){
	std::vector<Loader::JobBlock> result;
	JobBlock jb;
	for (auto i : str){
		std::vector<std::string> parsedJobStats = split(i, ' ');
		unsigned long id = std::stoul(parsedJobStats[2],nullptr, 16);
		unsigned long wordSize = std::stoul(parsedJobStats[3], nullptr, 16);
		unsigned long priority = std::stoul(parsedJobStats[4], nullptr, 16);

		jb.id = id;
		jb.priority = priority;
		jb.wordSize = wordSize;
		result.push_back(jb);
	}	
	return result;
}
std::vector<Loader::JobDataBlock> Loader::loadJobDataBlock(const std::vector<std::string> &str){
	std::vector<Loader::JobDataBlock> result;
	JobDataBlock jdb;
	for (auto i : str){
		std::vector<std::string> parsedJobStats = split(i, ' ');
		unsigned long inputBufferSize = std::stoul(parsedJobStats[2], nullptr, 16);
		unsigned long outputBufferSize = std::stoul(parsedJobStats[3], nullptr, 16);
		unsigned long tempBufferSize = std::stoul(parsedJobStats[4], nullptr, 16);
	
		jdb.inputBufferSize = inputBufferSize;
		jdb.outputBufferSize = outputBufferSize;
		jdb.tempBufferSize = tempBufferSize;
		result.push_back(jdb);
	}
	return result;
}

Loader::~Loader()
{
}
