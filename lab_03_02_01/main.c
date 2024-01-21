#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "input_output_funcs.h"
#include "work_funcs.h"

int main(void)
{
    int a[N][M];
    size_t a_n, a_m;
    size_t fi, fj;
    
    int error = input(a, &a_n, &a_m);
    switch (error)
    {
        case ERR_IO:
            printf("ERR_IO\n");
            return error;
        case ERR_RANGE:
            printf("ERR_RANGE\n");
            return error;
        default:
            if (error != OK)
            {
                printf("UNKNOWN ERROR CODE!\n");
                return error;
            }
            break;
    }
    min_digit_sum(a, a_n, a_m, &fi, &fj);
    del_row(a, &a_n, a_m, fi);
    del_col(a, a_n, &a_m, fj);
    if (a_n == 0 || a_m == 0)
    {
        printf("ERR_RANGE\n");
        return ERR_RANGE;
    }
    printm(a, a_n, a_m);
    
    return OK;
}
