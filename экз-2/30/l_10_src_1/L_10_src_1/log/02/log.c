#include "log.h"


static FILE *flog;


int log_init(const char *name)
{
    flog = fopen(name, "w");
    if(!flog)
        return 1;

    return 0;
}


FILE* log_get(void)
{
    return flog;
}


void log_close(void)
{
    fclose(flog);
}
