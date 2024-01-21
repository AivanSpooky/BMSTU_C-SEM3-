#ifndef __LOG__H__

#define __LOG__H__


#include <stdio.h>


int log_init(const char *name);


FILE* log_get(void);


void log_close(void);


#endif  //  __LOG__H__
