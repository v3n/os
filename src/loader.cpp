#include "loader.h"


Loader::Loader(Disk &diskName)
{

	std::string textFromFile = loadTextFile("..\\res\\Program-File.txt");
	//this can be made more efficient by modifying parseString_v method in loader.cpp, having a switch statement inside the while loop to load two
	//PCB(control cards) and instructions to a vector at the same time.
	std::vector<std::string> v_JobsCC = parseString_v(textFromFile, "// J"); //job Control Card
	std::vector<std::string> v_JobsDataCC = parseString_v(textFromFile, "// D");//job data Control Card
	std::vector<std::string> v_Instructions = parseString_v(textFromFile, "0x");//instructions to be stored in Harddrive

	std::vector<Loader::JobBlock> loadedJobBlock = loadJobBlock(v_JobsCC);
	std::vector<Loader::JobDataBlock> loadedJobDataBlock = loadJobDataBlock(v_JobsDataCC);

	//load into disk jb
	Disk::JobBlock jb = diskName.getJobBlock();
	std::vector<Disk::JobBlock> tempJBVector;
	for (auto i : loadedJobBlock){
		jb.id = i.id;
		jb.priority = i.priority;
		jb.wordSize = i.wordSize;
		tempJBVector.push_back(jb);
	}
	diskName.setVectorJB(tempJBVector);

	//load into disk jdb
	Disk::JobDataBlock jdb = diskName.getJobDataBlock();
	std::vector<Disk::JobDataBlock> tempJDBVector;
	for (auto i : loadedJobDataBlock){
		jdb.inputBufferSize = i.inputBufferSize;
		jdb.outputBufferSize = i.outputBufferSize;
		jdb.tempBufferSize = i.tempBufferSize;
		tempJDBVector.push_back(jdb);
	}
	diskName.setVectorJDB(tempJDBVector);

	//load into disk instructions
	diskName.getVectorDataInstructions().clear();
	diskName.setVectorDataInstruction(v_Instructions);
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
	Loader::JobBlock jb;
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
	Loader::JobDataBlock jdb;
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