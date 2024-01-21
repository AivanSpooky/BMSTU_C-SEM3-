#include "check_cmp_funcs.h"

// Функция сравнивает массивы по-элементно
int ck_assert_arr_eq(void *arr1, void *arr2, size_t cnt, size_t size, asserttype assert_elems)
{
    char *pbeg1 = arr1;
    char *pend1 = pbeg1 + (cnt) * size;
    char *pbeg2 = arr2;
    char *pend2 = pbeg2 + (cnt) * size;

    char *p1 = pbeg1;
    char *p2 = pbeg2;
    while (p1 < pend1 && p2 < pend2)
    {
        if (!assert_elems(p1, p2))
            return ERR_NOT_EQUAL;
        p1 += size;
        p2 += size;
    }
    return OK;
}

// Assert для int
int as_int(void *l, void *r)
{
    int *lp = l;
    int *rp = r;
    return *lp == *rp;
}