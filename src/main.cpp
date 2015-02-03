#include <iostream>
#include "baseconverter.h"
#include "loader.h"



int main(){
	BaseConverter bc;
	Loader loader;
	//std::cout << bc.baseConvert("14", 16, 10) << '\n';
	std::string textFromFile = loader.loadTextFile("..\\res\\Program-File.txt");

	//std::cout << textFromFile.at(0) << '\n';
	std::vector<std::string> v_Jobs = loader.parseString_v(textFromFile, "// J");
	std::vector<std::string> v_JobsData = loader.parseString_v(textFromFile, "// D");

	std::vector<Loader::JobBlock> loadedJobBlock = loader.loadJobBlock(v_Jobs);
	std::cout << loadedJobBlock.size()<< '\n';
	for (auto i : loadedJobBlock){
		std::cout << i.id << "\t"<< i.wordSize<<"\t"<<i.priority<< '\n';
	}
	std::vector<Loader::JobDataBlock> loadedJobDataBlock = loader.loadJobDataBlock(v_JobsData);
	std::cout << loadedJobDataBlock.size() << '\n';
	for (auto i : loadedJobDataBlock){
		std::cout << i.inputBufferSize << "\t" << i.outputBufferSize <<"\t"<<i.tempBufferSize<< '\n';
	}

	system("pause");
	return 0;
}

