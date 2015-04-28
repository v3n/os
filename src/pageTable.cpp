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

void PageTable::AssignPage(PCB proc_id)
{
	int free_page = free_frames[rand() % free_frames.size()];	//select randomly from free_frames for now...

	std::vector<int>::iterator index = free_frames.begin();		//remove given page number from the free_frame list
	while (index != free_frames.end())
	{
		if (*index == free_page)
		{
			free_frames.erase(index);
		}
		index++;
	}

	proc_table[free_page] = proc_id.jobID;			//mark given page index as held by given process
	ram->allocate(PAGE_SIZE, true);					//allocate given page?
}

void PageTable::FreePage(int page_num, PCB proc_id)
{
	free_frames.push_back(page_num);				//add page num to the free frame list
}

WORD* PageTable::LookupPage(int index, int offset)	//return RAM location based on index/offset of pagetable - need some way to index RAM...
{
	//return location in RAM defined by:
	//index * 4 + offset
	//needs work...
	WORD* tmp;	//brief stub so build works...
	return tmp;
}

void PageTable::ResolveFaults(PCB proc)		//called by CPU on current process when a fault is reached...
{
	if (!free_frames.empty())		
	{
		AssignPage(proc);
	}
}
