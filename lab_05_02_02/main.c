#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "consts.h"
#include "err_codes.h"
#include "work_funcs.h"


int main(int argc, char **argv)
{
    FILE *f;
    int rc = OK;

    if (argc != 2)
    {
        fprintf(stdout, "App.exe file_name\n");
        return ERR_ARGS;
    }
    
    f = fopen(argv[1], "r");

    if (f == NULL)
    {
        fprintf(stdout, "Can not open file\n");
        return ERR_IO;
    }

    size_t n = 0;
    double avg;
    rc = calc_avg(f, &avg, &n);
    if (rc != OK)
    {
        fprintf(stdout, "No nums error\n");
        fclose(f);
        return rc;
    }
    //
    rewind(f);
    //
    double s_sq;
    rc = calc_s_sq(f, avg, n, &s_sq);
    if (rc == OK)
    {
        fprintf(stdout, "%lf\n", s_sq);
    }
    else
    {
        fprintf(stdout, "No nums (or only one) error\n");
    }
    fclose(f);

    return rc;
}
