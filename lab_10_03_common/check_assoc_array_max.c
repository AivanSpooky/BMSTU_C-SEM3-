#include <stdlib.h>

#include "codes.h"

#include "associative_array.h"

#include "check_assoc_array_max.h"

// pos_01 - Создать ассоциативный массив, найти минимум
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    key = "another";
    num = 1;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    key = "last-one";
    num = -12;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *maximum;
    int real_value = -12;
    rc = assoc_array_max(arr, &maximum);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*maximum, real_value);
    assoc_array_destroy(&arr);
}
END_TEST

// pos_02 - Создать ассоциативный массив из одного элемента, найти минимум
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *maximum;
    int real_value = 10;
    rc = assoc_array_max(arr, &maximum);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*maximum, real_value);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_01 - Попытка найти минимум в неинициализированном ассоциативном массиве
START_TEST(neg_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = NULL;

    int *maximum;
    rc = assoc_array_max(arr, &maximum);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_02 - Попытка найти минимум в ассоциативном массиве и записать минимум в неправильный указатель
START_TEST(neg_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);


    int **maximum = NULL;
    rc = assoc_array_max(arr, maximum);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_max_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_max");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);

    suite_add_tcase(s, tc_core);

    return s;
}
