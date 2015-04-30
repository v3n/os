#include "pageTable.h"

PageTable::PageTable()
{
	free_frames = new std::vector<int>(TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		free_frames->at(i) = (page_table[i]);			//initialise all page indices as free frames
	}
}
PageTable::PageTable(Ram *r) : PageTable()
{
    
	ram = r;
}

PageTable::~PageTable()
{
}

void PageTable::AssignPage(PCB proc_id)
{
	int free_page = rand() % free_frames->size();	//select randomly from free_frames for now...

	std::vector<int>::iterator index = free_frames->begin();		//remove given page number from the free_frame list
	while (index != free_frames->end())
	{
		if (*index == free_page)
		{
			free_frames->erase(index);
		}
		index++;
	}

	proc_table[free_page] = proc_id.jobID;					//mark given page index as held by given process
	proc_id.page_index = free_page;	
	void *temp;
	temp = ram->allocate(PAGE_SIZE, free_page, proc_id, true);		//allocate given page?
	vecPointerToRam.pusback(temp);

}

void PageTable::FreePage(int page_num, PCB proc_id)
{
	free_frames->push_back(page_num);				//add page num to the free frame list
}

WORD* PageTable::LookupPage(int index)	//return RAM location based on index
{
    return (WORD*)vecPointerToRam[index];
}

PCB* PageTable::LookupProcess(int index)		//return process information based on table index
{
	PCB *proc_location = &ram->processes[index];
	return proc_location;
}

void PageTable::ResolveFaults(PCB proc)		//called by CPU on current process when a fault is reached...
{
	if (!free_frames->empty())		
	{
		AssignPage(proc);
	}
}
