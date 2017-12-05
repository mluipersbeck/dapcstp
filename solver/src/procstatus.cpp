/**
 * \file   procstatus.cpp
 * \brief  read and check memory limit
 *
 * \author Mario Ruthmaier 
 * \date   2015-05-03
 */

#include "procstatus.h"

#include <cmath>
#include <limits>
#if _WIN32
#include <windows.h>
#include <psapi.h>
#elif __linux__
#include <unistd.h>
#endif

using namespace std;

uint32_t ProcStatus::memlimit = std::numeric_limits<uint32_t>::max();
uint32_t ProcStatus::maxusedmem = 0;

#if __linux__
size_t ProcStatus::page_size = sysconf(_SC_PAGESIZE);
#endif

ProcStatus::ProcStatus()
{

}

void ProcStatus::setMemLimit( uint32_t lim )
{
	if (lim > 0)
		memlimit = lim;
	else if (lim < 0)
		memlimit = available() * 0.9;
}

uint32_t ProcStatus::mem()
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

uint32_t ProcStatus::available()
{
#if __linux__
	return (uint32_t) floor(((double)(ProcStatus::page_size * sysconf(_SC_AVPHYS_PAGES))) / (1024.0*1024));
#elif _WIN32
	MEMORYSTATUSEX sMeminfo;
	sMeminfo.dwLength = sizeof(sMeminfo);
	GlobalMemoryStatusEx(&sMeminfo);
	return (uint32_t) floor(((double) sMeminfo.ullAvailPhys) / (1024.0*1024.0));
#endif
}

uint32_t ProcStatus::total()
{
#if __linux__
	return (uint32_t) floor(((double)(ProcStatus::page_size * sysconf(_SC_PHYS_PAGES))) / (1024.0*1024));
#elif _WIN32
	MEMORYSTATUSEX sMeminfo;
	sMeminfo.dwLength = sizeof(sMeminfo);
	GlobalMemoryStatusEx(&sMeminfo);
	return (uint32_t) floor(((double) sMeminfo.ullTotalPhys) / (1024.0*1024.0));
#endif
}

ProcStatus::~ProcStatus()
{

}
