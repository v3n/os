#include <iostream>
#include <fstream>

#include "loader.h"
#include "hdd.h"
#include "cpu.h"

using namespace std;

int main(int argc, char const *argv[])
{
    HDD *hdd = new HDD();
    Loader *l = new Loader("/Users/jonathan/Development/os/spec/Program-File.txt", hdd);
    CPU *cpu = new CPU();

    File * file = hdd->findFile(1);
    WORD * programData = (WORD *)&(*(file+1));

    for (unsigned i = 0; i < file->programSize; i++)
    {
        cpu->fetch(programData++);
        cpu->decode();
    }

	return 0;
}
