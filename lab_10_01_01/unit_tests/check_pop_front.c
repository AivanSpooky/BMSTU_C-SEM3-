#include "check_pop_front.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Взять первый элемент типа int
START_TEST(pos_01)
{
    node_t *node_list = NULL;
    int num;
    size_t data_size = sizeof(num);

    size_t size = 5;
    int values1[5] = { 1, 2, 3, 4, 5 };
    int first_elem = values1[0];
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 4;
    int values2[4] = { 2, 3, 4, 5 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    int rc = OK;
    int *p = pop_front(&node_list);
    if (node_cmp_int(p, &first_elem) != 0)
        rc = UNIT_ERR_DATA_NOT_EQUAL;
    else
        rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_int);
    free(p);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// pos_02 - Взять первый элемент типа string
START_TEST(pos_02)
{
    node_t *node_list = NULL;
    size_t data_size = sizeof(char *);
    char *first_elem = "str-1";
    size_t size = 5;
    char *values1[5] = { "str-1", "str-2", "str-3", "str-4", "str-5" };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 4;
    char *values2[4] = { "str-2", "str-3", "str-4", "str-5" };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    int rc = OK;
    char *p = pop_front(&node_list);
    if (node_cmp_str(p, &first_elem) != 0)
        rc = UNIT_ERR_DATA_NOT_EQUAL;
    else
    {
        rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_str);
    }
    free(p);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// pos_03 - Взять первый элемент типа double
START_TEST(pos_03)
{
    node_t *node_list = NULL;
    double num;
    size_t data_size = sizeof(num);
    double first_elem = 1.0;
    size_t size = 5;
    double values1[5] = { 1.0, 2.2, 3.3, 4.4, 5.0 };
    node_list_create_from_array(&node_list, (void *)values1, size, data_size);

    node_t *node_list_check = NULL;
    size = 4;
    double values2[4] = { 2.2, 3.3, 4.4, 5.0 };
    node_list_create_from_array(&node_list_check, (void *)values2, size, data_size);

    int rc = OK;
    double *p = pop_front(&node_list);
    if (node_cmp_double(p, &first_elem) != 0)
        rc = UNIT_ERR_DATA_NOT_EQUAL;
    else
    {
        rc = ck_assert_node_list_eq(node_list, node_list_check, node_cmp_double);
    }
    free(p);
    node_list_free(&node_list);
    node_list_free(&node_list_check);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// neg_01 - Попытка взять элемент из пустого списка
START_TEST(neg_01)
{
    node_t *node_list = NULL;
    double *p = pop_front(&node_list);
    ck_assert_ptr_eq(p, NULL);
    free(p);
}
END_TEST

Suite *pop_front_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Pop-Front");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);

    suite_add_tcase(s, tc_core);

    return s;
}
