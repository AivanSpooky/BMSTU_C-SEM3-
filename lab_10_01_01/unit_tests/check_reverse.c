#include "check_reverse.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Перевернуть список типа int
START_TEST(pos_01)
{
    node_t *node_list = NULL;
    int num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 5;
    int values[5] = { 1, 2, 3, 4, 5 };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    node_t *node_list_check = NULL;
    size = 5;
    int values2[5] = { 5, 4, 3, 2, 1 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = reverse(node_list);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_02 - Перевернуть список типа double
START_TEST(pos_02)
{
    node_t *node_list = NULL;
    double num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 5;
    double values1[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    double values2[5] = { 5.5, 4.4, 3.3, 2.2, 1.1 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = reverse(node_list);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_double);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_03 - Перевернуть список типа str
START_TEST(pos_03)
{
    node_t *node_list = NULL;
    char *num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 5;
    char *values1[5] = { "str-1", "str-2", "str-3", "str-4", "str-5" };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    char *values2[5] = { "str-5", "str-4", "str-3", "str-2", "str-1" };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = reverse(node_list);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_double);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_04 - Перевернуть список из 1ого элемента
START_TEST(pos_04)
{
    node_t *node_list = NULL;
    int num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 1;
    int values1[1] = { 1 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 1;
    int values2[1] = { 1 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = reverse(node_list);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_05 - Перевернуть список из 2ух элементов
START_TEST(pos_05)
{
    node_t *node_list = NULL;
    int num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 2;
    int values1[2] = { 1, 2 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 2;
    int values2[2] = { 2, 1 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = reverse(node_list);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_06 - Перевернуть список из 0 элементов
START_TEST(pos_06)
{
    node_t *node_list = NULL;
    int rc = UNIT_OK;

    node_t *node_list_check = NULL;

    node_list = reverse(node_list);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *reverse_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Reverse");
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
