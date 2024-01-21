#include "check_fill_arr_with_primes.h"
#include <stdlib.h>

#include "array.h"
#include "check_cmp_funcs.h"

// pos_01 - Создать массив из 3-х простых чисел
START_TEST(pos_01)
{
    size_t size = 3;
    int a[size];
    int expected[] = {2, 3, 5};
    int rc = fill_arr_with_primes(a, size);
    ck_assert_int_eq(rc, OK);
    // Проверка результата
    rc = ck_assert_arr_eq(a, expected, size, sizeof(int), as_int);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_02 - Создать массив из 1-ого простого числа
START_TEST(pos_02)
{
    size_t size = 1;
    int a[size];
    int expected[] = {2};
    int rc = fill_arr_with_primes(a, size);
    ck_assert_int_eq(rc, OK);
    // Проверка результата
    rc = ck_assert_arr_eq(a, expected, size, sizeof(int), as_int);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_03 - Создать массив из 0 простых чисел
START_TEST(pos_03)
{
    size_t size = 0;
    int a[size];
    int expected[] = {};
    int rc = fill_arr_with_primes(a, size);
    ck_assert_int_eq(rc, OK);
    // Проверка результата
    rc = ck_assert_arr_eq(a, expected, size, sizeof(int), as_int);
    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *fill_arr_with_primes_suit(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("fill_arr_with_primes");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    suite_add_tcase(s, tc_core);

    return s;
}
