#include "log.h"


FILE *flog;


int log_init(const char *name)
{
    flog = fopen(name, "w");
    if(!flog)
        return 1;

    return 0;
}


void log_close(void)
{
    fclose(flog);
}
