#include <stdlib.h>

#include "associative_array.h"

#include "check_assoc_array_insert.h"

#include "codes.h"

// pos_01 - Создать ассоциативный массив и добавить в него ("key", 10)
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);
    rc = assoc_array_insert(arr, "key", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// pos_02 - Создать ассоциативный массив и добавить в него несколько ключей ("key-1", 10), ("key-2", 15)
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);
    rc = assoc_array_insert(arr, "key-1", 10);
    rc = assoc_array_insert(arr, "key-2", 15);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_01 - Попытка добавить уже существующий ключ
START_TEST(neg_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);
    rc = assoc_array_insert(arr, "key", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "key", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_02 - Попытка добавить пустую строку
START_TEST(neg_02)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);
    char *str = NULL;
    rc = assoc_array_insert(arr, str, 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_insert_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_insert");
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
