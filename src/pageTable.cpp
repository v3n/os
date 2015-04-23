#include "pageTable.h"

PageTable::PageTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		free_frames.push_back(page_table[i]);			//initialise all page indices as free frames
	}
}
PageTable::~PageTable()
{
}

void PageTable::AssignPage(int page_num, PCB proc_id)
{
	std::vector<int>::iterator index = free_frames.begin();		//remove given page number from the free_frame list
	while (index != free_frames.end())
	{
		if (*index == page_num)
		{
			free_frames.erase(index);
		}
		index++;
	}

	proc_table[page_num] = proc_id.jobID;			//mark given page index as held by given process
}

void PageTable::FreePage(int page_num, PCB proc_id)
{
	free_frames.push_back(page_num);				//add page num to the free frame list
}

WORD* PageTable::LookupPage(int index, int offset)	//return RAM location based on index/offset of pagetable
{
	//return location in RAM defined by:
	//index * 4 + offset
	//needs work...
	WORD* tmp;	//brief stub so build works...
	return tmp;
}

void PageTable::ResolveFaults()
{

}
