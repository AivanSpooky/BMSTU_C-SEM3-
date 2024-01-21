#include <stdlib.h>

#include "codes.h"
#include "associative_array.h"

#include "check_assoc_array_find.h"

// pos_01 - Вернуть значение по ключу
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int real_num = 10;
    rc = assoc_array_insert(arr, key, real_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = 0;
    rc = assoc_array_find(arr, key, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, real_num);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_01 - Вернуть значение по ключу из неинициализированного ассоц. массива
START_TEST(neg_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = NULL;

    char *key = "key";
    int *num = 0;
    rc = assoc_array_find(arr, key, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_02 - Вернуть значение по неинициализированному ключу
START_TEST(neg_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = NULL;
    int *num = 0;
    rc = assoc_array_find(arr, key, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_03 - Вернуть значение по неинициализированному значению (int num)
START_TEST(neg_03)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int **num = NULL;
    rc = assoc_array_find(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_04 - Вернуть значение по несуществующему ключу
START_TEST(neg_04)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int real_num = 10;
    rc = assoc_array_insert(arr, key, real_num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = 0;
    char *another_key = "key-1";
    rc = assoc_array_find(arr, another_key, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_find_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_find");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);
    tcase_add_test(tc_core, neg_03);
    tcase_add_test(tc_core, neg_04);


    suite_add_tcase(s, tc_core);

    return s;
}
