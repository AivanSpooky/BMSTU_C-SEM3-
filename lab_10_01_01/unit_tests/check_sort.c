#include "check_sort.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Отсортировать список int
START_TEST(pos_01)
{
    node_t *node_list = NULL;
    int num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 5;
    int values1[5] = { 3, 2, 1, 5, 4 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 5;
    int values2[5] = { 1, 2, 3, 4, 5 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = sort(node_list, node_cmp_int);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_02 - Отсортировать список double
START_TEST(pos_02)
{
    node_t *node_list = NULL;
    double num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 5;
    double values1[5] = { 3.3, 2.2, 1.1, 5.5, 4.4 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    double values2[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = sort(node_list, node_cmp_double);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_double);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_03 - Отсортировать список int из 2х элемента
START_TEST(pos_03)
{
    node_t *node_list = NULL;
    int num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 2;
    int values1[2] = { 2, 1 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 2;
    int values2[2] = { 1, 2 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = sort(node_list, node_cmp_int);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST


// pos_04 - Отсортировать список int из 1ого элементов
START_TEST(pos_04)
{
    node_t *node_list = NULL;
    int num;
    int rc = UNIT_OK;
    size_t data_size = sizeof(num);
    size_t size = 1;
    int values1[1] = { 4 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 1;
    int values2[1] = { 4 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    node_list = sort(node_list, node_cmp_int);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// pos_05 - Отсортировать список int из 0 элементов
START_TEST(pos_05)
{
    node_t *node_list = NULL;
    int rc = UNIT_OK;

    node_t *node_list_check = NULL;

    node_list = sort(node_list, node_cmp_int);
    rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Sort");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);
    tcase_add_test(tc_core, pos_04);
    tcase_add_test(tc_core, pos_05);
    // tcase_add_test(tc_core, pos_06);

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
