#pragma once
#include "utils.h"
#include "pcb.h"
#include "ram.h"
#include <vector>

#define TABLE_SIZE 132		//designated # of pages in table (528 / 4)

class PageTable
{
public:
	PageTable();
	~PageTable();

	WORD* LookupPage(int index, int offset);
	void AssignPage(int page_num, PCB proc_id);
	void FreePage(int page_num, PCB proc_id);

private:
	std::vector<int> free_frames;
	int page_table[TABLE_SIZE];		//holds the page indices
	int proc_table[TABLE_SIZE];		//holds the process_ID of each assigned page
};

