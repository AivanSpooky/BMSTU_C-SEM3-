#include "check_rewrite_arr.h"
#include <stdlib.h>

#include "array.h"
#include "check_cmp_funcs.h"

// pos_01 - Добавить число после одного четного в начале
START_TEST(pos_01)
{
    size_t size = 3;
    int a[] = {2, 3, 5};
    int num = 5;
    size_t size_e = 4;
    int expected[] = {2, 5, 3, 5};
    
    size_t new_size = rewrite_arr(a, NULL, size, num);
    ck_assert_int_eq(new_size, size_e);
    int dst[new_size];
    rewrite_arr(a, dst, size, num);

    // Проверка результата
    int rc = ck_assert_arr_eq(dst, expected, new_size, sizeof(int), as_int);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_02 - Добавить число после всех цифр (они четные)
START_TEST(pos_02)
{
    size_t size = 3;
    int a[] = {2, 4, 6};
    int num = 5;
    size_t size_e = 6;
    int expected[] = {2, 5, 4, 5, 6, 5};
    
    size_t new_size = rewrite_arr(a, NULL, size, num);
    ck_assert_int_eq(new_size, size_e);
    int dst[new_size];
    rewrite_arr(a, dst, size, num);

    // Проверка результата
    int rc = ck_assert_arr_eq(dst, expected, new_size, sizeof(int), as_int);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_03 - Добавить число после четных (четных чисел нет)
START_TEST(pos_03)
{
    size_t size = 3;
    int a[] = {1, 3, 5};
    int num = 5;
    size_t size_e = 3;
    int expected[] = {1, 3, 5};
    
    size_t new_size = rewrite_arr(a, NULL, size, num);
    ck_assert_int_eq(new_size, size_e);
    int dst[new_size];
    rewrite_arr(a, dst, size, num);

    // Проверка результата
    int rc = ck_assert_arr_eq(dst, expected, new_size, sizeof(int), as_int);
    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *rewrite_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("rewrite_arr");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    suite_add_tcase(s, tc_core);

    return s;
}
