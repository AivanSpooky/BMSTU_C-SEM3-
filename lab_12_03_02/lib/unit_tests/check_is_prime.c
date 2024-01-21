#include "check_is_prime.h"
#include <stdlib.h>
#include <stdbool.h>

#include "array.h"
#include "check_cmp_funcs.h"

// pos_01 - Проверить какое-то из простых чисел на простоту
START_TEST(pos_01)
{
    int num = 7;
    bool prime = is_prime(num);
    bool expected = true;
    if (prime != expected)
        ck_assert_int_eq(ERR_NOT_EQUAL, OK);
}
END_TEST

// pos_02 - Проверить самое маленькое простое на простоту
START_TEST(pos_02)
{
    int num = 2;
    bool prime = is_prime(num);
    bool expected = true;
    if (prime != expected)
        ck_assert_int_eq(ERR_NOT_EQUAL, OK);
}
END_TEST

// pos_03 - Проверить отрицательное число на простоту
START_TEST(pos_03)
{
    int num = -2;
    bool prime = is_prime(num);
    bool expected = false;
    if (prime != expected)
        ck_assert_int_eq(ERR_NOT_EQUAL, OK);
}
END_TEST

// pos_04 - Проверить ноль на простоту
START_TEST(pos_04)
{
    int num = 0;
    bool prime = is_prime(num);
    bool expected = false;
    if (prime != expected)
        ck_assert_int_eq(ERR_NOT_EQUAL, OK);
}
END_TEST

// pos_05 - Проверить единицу на простоту
START_TEST(pos_05)
{
    int num = 1;
    bool prime = is_prime(num);
    bool expected = false;
    if (prime != expected)
        ck_assert_int_eq(ERR_NOT_EQUAL, OK);
}
END_TEST

// pos_06 - Проверить составное число на простоту
START_TEST(pos_06)
{
    int num = 49;
    bool prime = is_prime(num);
    bool expected = false;
    if (prime != expected)
        ck_assert_int_eq(ERR_NOT_EQUAL, OK);
}
END_TEST

Suite *is_prime_suit(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_prime");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);
    tcase_add_test(tc_core, pos_04);
    tcase_add_test(tc_core, pos_05);
    tcase_add_test(tc_core, pos_06);   

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
