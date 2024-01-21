#include "check_find.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Найти в списке целое число, которое стоит не в начале и не в конце списка
START_TEST(pos_01)
{
    node_t *node_list = NULL;
    int num;
    size_t data_size = sizeof(num);
    size_t size = 5;
    int values[5] = { 1, 2, 3, 4, 5 };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    int rc = OK;
    num = 3;
    if (find(node_list, &num, node_cmp_int) == NULL)
        rc = ERR_DATA;
    node_list_free(&node_list);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// pos_02 - Найти в списке целое число, которое стоит в начале списка
START_TEST(pos_02)
{
    node_t *node_list = NULL;
    int num;
    size_t data_size = sizeof(num);
    size_t size = 5;
    int values[5] = { 1, 2, 3, 4, 5 };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    int rc = OK;
    num = 1;
    if (find(node_list, &num, node_cmp_int) == NULL)
        rc = ERR_DATA;
    node_list_free(&node_list);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// pos_03 - Найти в списке целое число, которое стоит в конце списка
START_TEST(pos_03)
{
    node_t *node_list = NULL;
    int num;
    size_t data_size = sizeof(num);
    size_t size = 5;
    int values[5] = { 1, 2, 3, 4, 5 };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    int rc = OK;
    num = 5;
    if (find(node_list, &num, node_cmp_int) == NULL)
        rc = ERR_DATA;
    node_list_free(&node_list);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// pos_04 - Найти в списке вещественное число
START_TEST(pos_04)
{
    node_t *node_list = NULL;
    double num;
    size_t data_size = sizeof(num);
    size_t size = 5;
    double values[5] = { 1.0, 2.2, 3.3, 4.4, 5.0 };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    int rc = OK;
    num = 2.2;
    if (find(node_list, &num, node_cmp_double) == NULL)
        rc = ERR_DATA;
    node_list_free(&node_list);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// pos_05 - Найти в списке строку
START_TEST(pos_05)
{
    node_t *node_list = NULL;
    char *str;
    size_t data_size = sizeof(str);
    size_t size = 5;
    char *values[5] = { "str-1", "str-2", "str-3", "str-4", "str-5" };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    int rc = OK;
    str = "str-1";
    if (find(node_list, &str, node_cmp_str) == NULL)
        rc = ERR_DATA;
    node_list_free(&node_list);
    ck_assert_int_eq(rc, OK); 
}
END_TEST

// neg_01 - Попытка найти несуществующий элемент
START_TEST(neg_01)
{
    node_t *node_list = NULL;
    int num;
    size_t data_size = sizeof(num);
    size_t size = 5;
    int values[5] = { 1, 2, 3, 4, 5 };
    node_list_create_from_array(&node_list, (void *)values, size, data_size);

    int rc = OK;
    num = 6;
    if (find(node_list, &num, node_cmp_int) == NULL)
        rc = ERR_DATA;
    node_list_free(&node_list);
    ck_assert_int_ne(rc, OK); 
}
END_TEST


Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Find");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);
    tcase_add_test(tc_core, pos_04);
    tcase_add_test(tc_core, pos_05);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);

    suite_add_tcase(s, tc_core);

    return s;
}
