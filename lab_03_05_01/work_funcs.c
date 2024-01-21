#include "work_funcs.h"

int digit_sum(int n)
{
    int result = 0;
    int num = abs(n);
    while (num % 10 != 0)
    {
        result += num % 10;
        num /= 10;
    }
    return result;
}

void left_step(int b[], size_t elems)
{
    int tmp = b[0];
    for (size_t i = 0; i < (elems - 1); i++)
        b[i] = b[i + 1];
    b[elems - 1] = tmp;
}
int replace(int a[][M], size_t a_n, size_t a_m)
{
    int b[N*M];
    size_t elems = 0;
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = 0; j < a_m; j++)
        {
            if (digit_sum(a[i][j]) > 10)
            {
                b[elems] = a[i][j];
                elems++;
            }
        }
    if (elems == 0)
        return ERR_RANGE;
    for (size_t i = 0; i < STEPS; i++)
        left_step(b, elems);
    elems = 0;
    for (size_t i = 0; i < a_n; i++)
    {
        for (size_t j = 0; j < a_m; j++)
        {
            if (digit_sum(a[i][j]) > 10)
            {
                a[i][j] = b[elems];
                elems++;
            }
        }
    }
    return OK;
}

