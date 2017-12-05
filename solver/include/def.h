/**
 * \file   def.h
 * \brief  definitions and macros
 *
 * \author Martin Luipersbeck 
 * \date   2015-05-03
 */

#ifndef DEF_H_
#define DEF_H_

#define PROGRAM_NAME "da"
#define PROJECT_NAME "dapcstp"
#define PROGRAM_VERSION "1.0"
#define PROGRAM_MAJOR 1
#define PROGRAM_MINOR 0
#define PROGRAM_MICRO 0
#define PROGRAM_BUILD 0

// for windows rc.exe just parse upto here
#ifndef RC_INVOKED 

#include <cstdint>
#include <inttypes.h>
#include <limits>

extern const char* RED;
extern const char* GREEN;
extern const char* NORMAL;
extern const char* CYAN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* GRAY;
extern const char* YELLOWBI;
extern const char* GREENBI;
extern const char* CYANBI;
extern const char* PURPLEBI;
extern const char* BLUEBI;

#define WMAX std::numeric_limits<weight_t>::max()
#define DMAX std::numeric_limits<double>::max()
#define IMAX std::numeric_limits<int>::max()
#define gap(lb,ub) ((double)abs(ub-lb)/ub)
#define gapP(lb,ub) ((double)abs(ub-lb)*100.0/ub)
#define EXIT(...) {fprintf(stderr, __VA_ARGS__);exit(1);}

typedef std::int64_t weight_t;
typedef char flag_t;

#endif

#endif // DEF_H_
