/**
 * \file   procstatus.cpp
 * \brief  read and check memory limit
 *
 * \author Mario Ruthmaier 
 * \date   2015-05-03
 * 
 * \author Max Resch
 * \date   2017-12-01
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

void ProcStatus::setMemLimit( int lim )
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
	fscanf(fd, "%*s %" SCNu64, &rss);
	fclose(fd);

	// statm provides sizes in number of pages
	return (rss * ProcStatus::page_size) / (1024*1024);
#elif _WIN32
	HANDLE pHandle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS sMeminfo;
	GetProcessMemoryInfo(pHandle, &sMeminfo, sizeof(sMeminfo));
	return sMeminfo.WorkingSetSize / (1024*1024);
#endif
}

uint32_t ProcStatus::available()
{
#if __linux__
	uint64_t memory;
	char buf[128];

	FILE* fd = fopen("/proc/meminfo", "r");
	while (fgets(buf, 128, fd) != NULL) {
		// Linux Kernel > 3.14 Provides an explicit estimate
		if (sscanf(buf, "MemAvailable: %" SCNu64, &memory) == 1)
			break;
	}
	fclose(fd);

	// statm provides sizes in number of pages
	return memory / 1024;
#elif _WIN32
	MEMORYSTATUSEX sMeminfo;
	sMeminfo.dwLength = sizeof(sMeminfo);
	GlobalMemoryStatusEx(&sMeminfo);
	return sMeminfo.ullAvailPhys / (1024*1024);
#endif
}

uint32_t ProcStatus::total()
{
#if __linux__
	return (ProcStatus::page_size * sysconf(_SC_PHYS_PAGES)) / (1024*1024);
	return (uint32_t) floor(((double)(ProcStatus::page_size * sysconf(_SC_PHYS_PAGES))) / (1024.0*1024));
#elif _WIN32
	MEMORYSTATUSEX sMeminfo;
	sMeminfo.dwLength = sizeof(sMeminfo);
	GlobalMemoryStatusEx(&sMeminfo);
	return sMeminfo.ullTotalPhys / (1024*1024);
#endif
}

ProcStatus::~ProcStatus()
{

}
