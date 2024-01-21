// log.h

#ifndef __LOG__H__

#define __LOG__H__

#include <stdio.h>

int log_init(const char
                  *name);

void log_message(const char
                 *format, ...);

void log_close(void);

#endif  //  __LOG__H__
