#ifndef CHECK_CMP_FUNCS_H__

#define CHECK_CMP_FUNCS_H__

#include <check.h>

#define OK 0
#define ERR_NOT_EQUAL 1

typedef int (*asserttype)(void *l, void *r);

int ck_assert_arr_eq(void *arr1, void *arr2, size_t cnt, size_t size, asserttype assert_elems);

int as_int(void *l, void *r);

#endif