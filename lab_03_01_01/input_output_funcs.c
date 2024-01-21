#include "input_output_funcs.h"

int input(int a[][M], size_t *a_n, size_t *a_m)
{
    printf("Input n: ");
    if (scanf("%zu", a_n) != 1)
        return ERR_IO;
    printf("Input m: ");
    if (scanf("%zu", a_m) != 1)
        return ERR_IO;
    if (*a_n == 0 || *a_n > N || *a_m == 0 || *a_m > M)
        return ERR_RANGE;
    for (size_t i = 0; i < *a_n; i++)
    {
        printf("Input elems of line: ");
        for (size_t j = 0; j < *a_m; j++)
        {
            if (scanf("%d", &a[i][j]) != 1)
                return ERR_IO;
        }
    }
    printf("\n");
    return OK;
}

void print(const int a[], const size_t a_n)
{
    printf("\nArray: \n");
    for (size_t i = 0; i < a_n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
