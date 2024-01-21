#include <check_key.h>
#include <stdlib.h>

#include "funcs.h"

void assert_arr_eq(const int *pbkey, const int *pekey, const int *pb2, const int *pe2)
{
    ck_assert_ptr_ne(pb2, NULL);
    ck_assert_ptr_ne(pe2, NULL);
    ck_assert_int_eq(pe2 - pb2, pekey - pbkey);

    const int *pcurkey = pbkey;
    const int *pcur = pb2;

    while (pcur < pe2)
    {
        ck_assert_int_eq(*pcur, *pcurkey);
        pcur++;
        pcurkey++;
    }
}

// pos_01 - Все числа (кроме последнего) прошли фильтр и попали в конечный массив
START_TEST(pos_01)
{
    const int arr[] = {5, 2, 1, 0};
    const int expected[] = {5, 2, 1};
    const int *pb1 = arr;
    const int *pe1 = arr + 4;
    int *pb2, *pe2;

    const int *pbkey = expected;
    const int *pekey = expected + 3;

    int rc = key(pb1, pe1, &pb2, &pe2);
    ck_assert_int_eq(rc, OK);

    assert_arr_eq(pbkey, pekey, pb2, pe2);

    free(pb2);
}
END_TEST

// pos_02 - Фильтр прошли только часть чисел первоначального массива
START_TEST(pos_02)
{
    const int arr[] = {1, 10, 1, 4, 0};
    const int expected[] = {10, 4};
    const int *pb1 = arr;
    const int *pe1 = arr + 5;
    int *pb2, *pe2;

    const int *pbkey = expected;
    const int *pekey = expected + 2;

    int rc = key(pb1, pe1, &pb2, &pe2);
    ck_assert_int_eq(rc, OK);
    
    assert_arr_eq(pbkey, pekey, pb2, pe2);

    free(pb2);
}
END_TEST

// neg_01 - Пустой массив
START_TEST(neg_01)
{
    const int *pb1 = NULL;
    const int *pe1 = NULL;
    int *pb2 = NULL, *pe2 = NULL;

    int rc = key(pb1, pe1, &pb2, &pe2);
    ck_assert_int_eq(rc, ERR_EMPTY);

    ck_assert_ptr_eq(pb2, NULL);
    ck_assert_ptr_eq(pe2, NULL);
}
END_TEST

// neg_02 - После фильтра не осталось ни одного элемента
START_TEST(neg_02)
{
    const int arr[] = {1, 2, 3, 4, 5};
    const int *pb1 = arr;
    const int *pe1 = arr + 5;
    int *pb2 = NULL;
    int *pe2 = NULL;

    int rc = key(pe1, pb1, &pb2, &pe2);

    ck_assert_int_eq(rc, ERR_RANGE);
    ck_assert_ptr_eq(pb2, NULL);
    ck_assert_ptr_eq(pe2, NULL);
}
END_TEST

// neg_03 - На вход фильтру подали массив из одного элемента
START_TEST(neg_03)
{
    const int arr[] = {1};
    const int *pb1 = arr;
    const int *pe1 = arr + 1;
    int *pb2 = NULL;
    int *pe2 = NULL;

    int rc = key(pe1, pb1, &pb2, &pe2);

    ck_assert_int_eq(rc, ERR_RANGE);
    ck_assert_ptr_eq(pb2, NULL);
    ck_assert_ptr_eq(pe2, NULL);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Key");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);
    tcase_add_test(tc_core, neg_03);

    suite_add_tcase(s, tc_core);

    return s;
}
