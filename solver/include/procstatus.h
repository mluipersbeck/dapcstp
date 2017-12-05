/**
 * \file   procstatus.cpp
 * \brief  read and check memory limit
 *
 * \author Mario Ruthmaier 
 * \date   2012-05-03
 */
#ifndef PROCSTATUS_H_
#define PROCSTATUS_H_

#include <cstdio>
#include <inttypes.h>

#include "def.h"

using namespace std;

/*
 * class for querying current process status
 */
class ProcStatus
{

private:

	static uint32_t memlimit;

	static uint32_t maxusedmem;

#if __linux__
	static size_t page_size;
#endif

public:
	ProcStatus();
	virtual ~ProcStatus();

	/**
	 * Set the memory bounds
	 */
	static void setMemLimit( int lim );

	/**
	 * Get the amount of memory in MB currently used by this process
	 */
	static uint32_t mem();

	/**
	 * Get the amount of memory in MB currently marked as free
	 */
	static uint32_t available();

	/**
	 * Get the amount of memory in MB installed
	 */
	static uint32_t total();

	/**
	 * returns true, if the process is still within memory bounds
	 */
	static inline bool memOK()
	{
		uint32_t mb = mem();
		if( mb > maxusedmem ) maxusedmem = mb;
		if( maxusedmem > memlimit ) {
			printf("%s### Memory-Usage too high: %" PRIu32 " MB%s\n", RED, maxusedmem, NORMAL);
			return false;
		}
		else return true;
	}
};

#endif /* PROCSTATUS_H_ */
