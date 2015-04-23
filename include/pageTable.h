#pragma once
#include "utils.h"
#include "pcb.h"
#include "ram.h"
#include <vector>

#define TABLE_SIZE 256		//designated # of pages in table (1024 / 4)

class PageTable
{
public:
	PageTable();
	~PageTable();

	WORD* LookupPage(int index, int offset);		//search table and return corresponding RAM address
	void AssignPage(int page_num, PCB proc_id);		//assign a page index to a process
	void FreePage(int page_num, PCB proc_id);		//free a given page index for other use
	void ResolveFaults();

private:
	std::vector<int> free_frames;	//holds all unassigned frames
	int page_table[TABLE_SIZE];		//holds the page indices
	int proc_table[TABLE_SIZE];		//holds the process_ID of each assigned page
};

