#include <iostream>
#include <fstream>
#include <chrono>
#include "loader.h"
#include "hdd.h"
#include "cpu.h"

using namespace std;

int main(int argc, char const *argv[])
{
    HDD *hdd = new HDD();
#ifdef __APPLE__
	Loader *l = nnew Loader("/Users/jonathan/Development/os/spec/Program-File.txt", hdd);
#elif _WIN32
	Loader *l = new Loader("..\\OSProj\\spec\\Program-File.txt", hdd);
#endif

    CPU *cpu = new CPU();

    File * file = hdd->findFile(1);
    WORD * programData = (WORD *)&(*(file+1));

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
    for (unsigned i = 0; i < file->programSize; i++)
    {
		start = std::chrono::steady_clock::now();
        cpu->fetch(programData++);
        cpu->decode();
		end = std::chrono::steady_clock::now();
		std::cout << "Execution Time " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<'\n';
    }
	system("pause");
	return 0;
}