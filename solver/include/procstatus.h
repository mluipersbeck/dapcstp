/**
 * \file   procstatus.cpp
 * \brief  read and check memory limit
 *
 * \author Mario Ruthmaier 
 * \date   2012-05-03
 */
#ifndef PROCSTATUS_H_
#define PROCSTATUS_H_

#include <cmath>
#include <iostream>
#include <limits>
#include <fstream>
#include <cstdint>
using namespace std;

/*
 * class for querying current process status
 */
class ProcStatus
{

private:

	static uint64_t memlimit;

public:

	static uint64_t maxusedmem;

	ProcStatus();
	virtual ~ProcStatus();

	static void setMemLimit( uint64_t lim );
	static uint64_t mem();
	static bool memOK();

};

#endif /* PROCSTATUS_H_ */
