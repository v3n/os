#include <iostream>
#include <fstream>

#include "loader.h"
#include "hdd.h"

using namespace std;

int main(int argc, char const *argv[])
{
    HDD *hdd = new HDD();
    Loader *l = new Loader("/Users/jonathan/Development/os/spec/Program-File.txt", hdd);
    
	return 0;
}
