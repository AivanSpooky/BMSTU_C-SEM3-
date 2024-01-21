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
    error = replace(a, a_n, a_m);
    if (error != 0)
    {
        return error;
    }
    printm(a, a_n, a_m);
    
    return OK;
}
