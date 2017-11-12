/**
 * \file   procstatus.cpp
 * \brief  read and check memory limit
 *
 * \author Mario Ruthmaier 
 * \date   2015-05-03
 */

#include "procstatus.h"

#include <limits>
#include <cstdint>
#if _WIN32
#include <windows.h>
#include <psapi.h>
#elif __linux__
#include <unistd.h>
#endif

using namespace std;

uint64_t ProcStatus::memlimit = std::numeric_limits<uint64_t>::max();
uint64_t ProcStatus::maxusedmem = 0;

#if __linux__
size_t ProcStatus::page_size = sysconf(_SC_PAGESIZE);
#endif

ProcStatus::ProcStatus()
{

}

void ProcStatus::setMemLimit( uint64_t lim )
{
	memlimit = lim;
}

uint64_t ProcStatus::mem()
{
#if __linux__
	uint64_t rss;

	FILE* fd = fopen("/proc/self/statm", "r");
	// get resource set size
	fscanf(fd, "%*s %lu", &rss);
	fclose(fd);

	// statm provides sizes in number of pages
	double mb = ((double) (rss * ProcStatus::page_size)) / (1024.0*1024.0);
	return ceil( mb );
#elif _WIN32
	HANDLE pHandle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS sMeminfo;
	GetProcessMemoryInfo(pHandle, &sMeminfo, sizeof(sMeminfo));
	double mb = ((double) sMeminfo.WorkingSetSize) / (1024.0*1024.0);
	return ceil( mb );
#endif
}

bool ProcStatus::memOK()
{
	uint64_t mb = mem();
	if( mb > maxusedmem ) maxusedmem = mb;
	if( maxusedmem > memlimit ) {
		cout << "### Memory-Usage too high: " << maxusedmem << " MB\n";
		return false;
	}
	else return true;
}

ProcStatus::~ProcStatus()
{

}
