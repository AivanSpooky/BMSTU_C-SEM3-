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
    if (error == OK && a_n != a_m)
        error = ERR_NOT_EQUAL;
    switch (error)
    {
        case ERR_IO:
            printf("ERR_IO\n");
            return error;
        case ERR_RANGE:
            printf("ERR_RANGE\n");
            return error;
        case ERR_NOT_EQUAL:
            printf("ERR_NOT_EQUAL\n");
            return error;
        default:
            if (error != OK)
            {
                printf("UNKNOWN ERROR CODE!\n");
                return error;
            }
            break;
    }
    int number;

    //
    // Похоже, ни разу не компилировали...
    // reply: - компилировал, но за столь короткое время исправить ошибки build-а - неуспел
    /*int*/ error = find_num(a, a_n, &number);
    switch (error)
    {
        case ERR_NO_NUM:
            printf("ERR_NO_NUM\n");
            return error;
        default:
            if (error != OK)
            {
                printf("UNKNOWN ERROR CODE!\n");
                return error;
            }
            break;
    }
    printf("\n%d\n", number);
    
    return OK;
}
