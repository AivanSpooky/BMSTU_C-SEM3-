#include <stdio.h>

#include "process.h"
#include "err_codes.h"
#include "consts.h"

int main(void)
{
    FILE *f = stdin;
    int dist = 0;

    int rc = process(f, &dist);
    if (rc != OK)
        return rc;

    fprintf(stdout, "%d", dist);

    return OK;
}
