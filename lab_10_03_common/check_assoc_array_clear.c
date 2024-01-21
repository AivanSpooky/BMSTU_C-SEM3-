#include <stdlib.h>

#include "codes.h"

#include "associative_array.h"

#include "check_assoc_array_clear.h"

// pos_01 - Создать ассоциативный массив, заполнить тремя записями и сделать его пустым
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

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// pos_02 - Создать ассоциативный массив, заполнить одной записью и сделать его пустым
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_01 - Попытка сделать пустым неинициализированный ассоциативный массив
START_TEST(neg_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = NULL;

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_clear_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_clear");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);

    suite_add_tcase(s, tc_core);

    return s;
}
