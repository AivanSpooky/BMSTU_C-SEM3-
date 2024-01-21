#include "work_funcs.h"

bool symmetry(const int a[], const size_t a_n)
{
    for (size_t i = 0; i < (a_n / 2); i++)
        if (a[i] != a[a_n - i - 1])
            return false; 
    return true;
}

void replace_elems(int a[][M], int b[], const size_t a_n, const size_t a_m)
{
    for (size_t i = 0; i < a_n; i++)
    {
        if (symmetry(a[i], a_m))
        {
            b[i] = 1;
        }
        else
        {
            b[i] = 0;
        }
    }
}
