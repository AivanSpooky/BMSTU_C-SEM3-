#include "work_funcs.h"

int find_max(const int a[], const size_t a_m)
{
    int max_elem = a[0];
    for (size_t i = 1; i < a_m; i++)
    {
        if (a[i] > max_elem)
            max_elem = a[i];
    }
    return max_elem;
}
/* OLD
void find_max_indexes(int a[][M], size_t b[], const size_t a_n, const size_t a_m)
{
    for (size_t i = 0; i < a_n; i++)
    {
        int max_elem_ind = 0;
        for (size_t j = 0; j < a_m; j++)
            if (a[i][j] > a[i][max_elem_ind])
                max_elem_ind = j;
        b[i] = max_elem_ind;
    }
}
*/
void swap_arrays(int a[], int b[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void selection_sort(int a[][M], const size_t a_n, const size_t a_m)
{
    int max_elem = 0;
    size_t max_elem_ind = 0;
    for (size_t i = 0; i < a_n; i++)
    {
        max_elem_ind = i;
        max_elem = find_max(a[i], a_m);
        for (size_t j = i; j < a_n; j++)
        {
            int tmp = find_max(a[j], a_m);
            if (tmp > max_elem)
            {
                max_elem_ind = j;
                max_elem = tmp;
            }
        }
        swap_arrays(a[i], a[max_elem_ind], a_m);
    }
}

/* OLD
void selection_sort(int a[][M], size_t b[], const size_t a_n, const size_t a_m)
{
    size_t max_elem = 0;
    int tmp_elem = 0;
    size_t tmp_ind = 0;
    for (size_t i = 0; i < a_n; i++)
    {
        max_elem = i;
        for (size_t j = i; j < a_n; j++)
        {
            if (a[j][b[j]] > a[max_elem][b[max_elem]])
            {
                max_elem = j;
            }
        }
        for (size_t j = 0; j < a_m; j++)
        {
            tmp_elem = a[i][j];
            a[i][j] = a[max_elem][j];
            a[max_elem][j] = tmp_elem;
        }
        tmp_ind = b[i];
        b[i] = b[max_elem];
        b[max_elem] = tmp_ind;
    }
}
*/
