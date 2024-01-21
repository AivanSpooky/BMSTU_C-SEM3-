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
	/* OLD
	size_t b[N];
	find_max_indexes(a, b, a_n, a_m);
	selection_sort(a, b, a_n, a_m);
	*/
    selection_sort(a, a_n, a_m);
    printm(a, a_n, a_m);
    
    return OK;
}
