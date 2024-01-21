#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "input_output_funcs.h"
#include "work_funcs.h"

int main(void)
{
    int a[N][M];
    int b[M];
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
    replace_elems(a, b, a_n, a_m);
    print(b, a_n);

    return OK;
}
