// log.c
#include <stdio.h>
#include <stdarg.h>

static FILE* flog;

int log_init(const char
                      *name)
{
    flog = fopen(name, "w");
    if(!flog)
        return 1;

    return 0;
}

void log_message(const char
                 *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(flog, format, args);
    va_end(args);
}

void log_close(void)
{
    fclose(flog);
}
