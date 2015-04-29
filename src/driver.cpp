#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include <boost/program_options.hpp>

#include "loader.h"
#include "hdd.h"
#include "cpu.h"
#include "ram.h"
#include "scheduler.h"
#include "pageTable.h"
#include "dispatcher.h"

using namespace std;
namespace po = boost::program_options;

static std::vector<CPU *> cpus;

int main(int argc, char const ** argv)
{
    Scheduler::SchedulerMode Policy;

    /* boost::program_options */
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "print this help")
        ("cpu,c", po::value<int>(), "number of cpu cores (default: 1)")
        ("fifo", "FIFO scheduling policy")
        ("sjf", "SFJ scheduling policy")
        ("priority", "Job priority scheduling policy")
    ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).run(), vm);
    po::notify(vm);

    if ( vm.count("help") ) {
        cout << desc << "\n";
        return 1;
    }

    /* number of cpus */
    if ( vm.count("cpu") )
    {
        size_t NumCPUs = vm["cpu"].as<int>();

        for ( size_t i = 0; i < NumCPUs; i++ )
        {
            cpus.push_back( new CPU() );
        }
    }
    else
    {
        cpus.push_back( new CPU() );
    }

    cout << "Simulation OS starting..." << endl;
    cout << "Initializing " << cpus.size() << " CPU cores..." << endl;

    /* Scheduling policy */
    if ( vm.count( "sjf") )
    {
        Policy = Scheduler::POLICY_SJF;
        cout << "Scheduling jobs with policy SJF" << endl;
    }
    else if ( vm.count( "priority" ) )
    {
        Policy = Scheduler::POLICY_Priority;
        cout << "Scheduling jobs with policy PRIORITY" << endl;
    }
    else {
        Policy = Scheduler::POLICY_FIFO;
        cout << "Scheduling jobs with policy FIFO" << endl;
    }


    /* initialize hard drive */
    HDD *hdd = new HDD();

    /* initialize loader */
#ifdef __APPLE__
	Loader *l = new Loader("/Users/jonathan/Development/os/spec/Program-File.txt", hdd);
#elif _WIN32
	Loader *l = new Loader("..\\OSProj\\spec\\Program-File.txt", hdd);
#endif

    // File * file = hdd->findFile(1);
    // WORD * programData = (WORD *)&(*(file+1));

    // for (unsigned i = 0; i < file->programSize; i++)
    // {
    //     cpu->fetch(programData++);
    //     cpu->decode();
    // }

    /* rest of component modules */
	Ram * ram               = new Ram();
	PageTable * page_table  = new PageTable(ram);
	Scheduler * long_term   = new Scheduler(page_table, hdd);
    Dispatcher * short_term = new Dispatcher(long_term);

    long_term->LoadJobs();
    long_term->SetSchedulingMode(Policy);

    cout << "Entering runtime loop..." << endl;

    PCB * NextProgram;
    while ( (NextProgram = long_term->Peek()) )
    {
        long_term->Dequeue();
    }

    /* clean up */
    delete l;
    delete hdd;
    delete ram;
    delete page_table;
    delete long_term;
    delete short_term;
    for ( size_t i = 0; i < cpus.size(); i++ )
        delete cpus[i];

	return 0;
}
