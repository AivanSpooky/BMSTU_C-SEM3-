#include <stdlib.h>

#include "codes.h"

#include "associative_array.h"

#include "check_assoc_array_remove.h"

// pos_01 - Удалить значение по ключу из ассоциативного массива
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(arr, key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_01 - Удалить значение в неинициализированном ассоциативном массиве
START_TEST(neg_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = NULL;

    char *key = "key";
    rc = assoc_array_remove(arr, key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_02 - Удалить значение по неинициализированному ключу из ассоциативного массива
START_TEST(neg_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *real_key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, real_key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    char *key = NULL;
    rc = assoc_array_remove(arr, key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_03 - Удалить значение по несуществующему ключу из ассоциативного массива
START_TEST(neg_03)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *real_key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, real_key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    char *key = "invalid-key";
    rc = assoc_array_remove(arr, key);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_remove_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_remove");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);
    tcase_add_test(tc_core, neg_03);

    suite_add_tcase(s, tc_core);

    return s;
}
