#include <iostream>
#include <fstream>
#include <chrono>

#include "loader.h"
#include "hdd.h"
#include "cpu.h"
#include "ram.h"
#include "scheduler.h"
#include "pageTable.h"

using namespace std;

int main(int, char const **)
{
    HDD *hdd = new HDD();
#ifdef __APPLE__
	Loader *l = new Loader("./spec/Program-File.txt", hdd);
#elif _WIN32
	Loader *l = new Loader("..\\OSProj\\spec\\Program-File.txt", hdd);
#endif

    CPU *cpu = new CPU();	

    File * file = hdd->findFile(1);
    WORD * programData = (WORD *)&(*(file+1));

	// std::chrono::steady_clock::time_point start;
	// std::chrono::steady_clock::time_point end;
    for (unsigned i = 0; i < file->programSize; i++)
    {
		// start = std::chrono::steady_clock::now();
        cpu->fetch(programData++);
        cpu->decode();
		// end = std::chrono::steady_clock::now();
		// std::cout << "Execution Time " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<'\n';
    }

	Ram *ram;
	PageTable *page_table = new PageTable(ram);
	Scheduler *long_term = new Scheduler(page_table, hdd);

	return 0;
}
