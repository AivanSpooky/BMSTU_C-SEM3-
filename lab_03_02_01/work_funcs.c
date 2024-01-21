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

void min_digit_sum(int a[][M], size_t a_n, size_t a_m, size_t *fi, size_t *fj)
{
    int result = digit_sum(a[0][0]);
    size_t mi = 0;
    size_t mj = 0;
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = 0; j < a_m; j++)
        {
            int cur_sum = digit_sum(a[i][j]);
            if (cur_sum < result)
            {
                result = cur_sum;
                mi = i;
                mj = j;
            }
        }
    (*fi) = mi;
    (*fj) = mj;
}

void swap_arrays(int a[], int b[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void del_array_elem(int a[], size_t *n, size_t ind)
{
    for (size_t i = ind; i < (*n - 1); i++)
        a[i] = a[i + 1];
    (*n)--;
}

void del_row(int a[][M], size_t *a_n, size_t a_m, size_t index)
{
    for (size_t i = index; i < (*a_n - 1); i++)
        swap_arrays(a[i], a[i + 1], a_m);
    (*a_n)--;
}

void del_col(int a[][M], size_t a_n, size_t *a_m, size_t index)
{
    for (size_t i = 0; i < a_n; i++)
    {
        size_t array_size = *a_m;
        del_array_elem(a[i], &array_size, index);
    }
    (*a_m)--;
}

/* OLD
void del_row(int a[][M], size_t *a_n, size_t a_m, size_t index)
{
    for (size_t i = index; i < *a_n - 1; i++)
        for (size_t j = 0; j < a_m; j++)
            a[i][j] = a[i + 1][j];
    (*a_n)--;
}

void del_col(int a[][M], size_t a_n, size_t *a_m, size_t index)
{
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = index; j < *a_m - 1; j++)
            a[i][j] = a[i][j + 1];
    (*a_m)--;
}
*/
