#include "check_val.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Найти VAL в полиноме
START_TEST(pos_01)
{
    node_t *head = NULL;
    size_t size = 2;
    int coef[2] = { 4, 1 };
    int pow[2] = { 2, 0 };
    node_list_create_from_array(&head, coef, pow, size);

    int a = 7;
    int result;
    result = node_list_calc_val(head, a);
    int real_result = 197;
    node_list_free(&head);
    ck_assert_int_eq(result, real_result); 
}
END_TEST

// pos_02 - Найти VAL в полиноме при а = 0
START_TEST(pos_02)
{
    node_t *head = NULL;
    size_t size = 4;
    int coef[4] = { 4, 999, 413, 10 };
    int pow[4] = { 3, 2, 1, 0 };
    node_list_create_from_array(&head, coef, pow, size);

    int a = 0;
    int result;
    result = node_list_calc_val(head, a);
    int real_result = 10;
    node_list_free(&head);
    ck_assert_int_eq(result, real_result); 
}
END_TEST

// pos_03 - Найти VAL в полиноме степени 0
START_TEST(pos_03)
{
    node_t *head = NULL;
    size_t size = 1;
    int coef[1] = { 5 };
    int pow[1] = { 0 };
    node_list_create_from_array(&head, coef, pow, size);

    int a = 4;
    int result;
    result = node_list_calc_val(head, a);
    int real_result = 5;
    node_list_free(&head);
    ck_assert_int_eq(result, real_result); 
}
END_TEST

Suite *val_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("VAL");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты


    suite_add_tcase(s, tc_core);

    return s;
}
