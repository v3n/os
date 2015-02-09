#include <iostream>
#include "loader.h"

int main(int argc, char const *argv[])
{
	//data can be retrieved from mainDisk through its methods 
	//since the size of the disk is wrong on the instructions, just filling it up and disregarding 
	//its size
	Disk mainDisk;
	Loader loader(mainDisk);

	for ( ; ; )
	{

	}
	return 0;
}