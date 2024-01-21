#include "check_ddx.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Найти DDX в полиноме
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    node_t *head = NULL;
    size_t size = 3;
    int coef[3] = { 4, 12, 1 };
    int pow[3] = { 2, 1, 0 };
    node_list_create_from_array(&head, coef, pow, size);

    node_t *real = NULL;
    size = 2;
    int coef1[2] = { 8, 12 };
    int pow1[2] = { 1, 0 };
    node_list_create_from_array(&real, coef1, pow1, size);

    node_list_calc_ddx(head);
    rc = ck_assert_node_list_eq(head, real);
    node_list_free(&head);
    node_list_free(&real);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

// pos_02 - Найти DDX в полиноме степени 1
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    node_t *head = NULL;
    size_t size = 2;
    int coef[2] = { 12, 1 };
    int pow[2] = { 1, 0 };
    node_list_create_from_array(&head, coef, pow, size);

    node_t *real = NULL;
    size = 1;
    int coef1[1] = { 12 };
    int pow1[1] = { 0 };
    node_list_create_from_array(&real, coef1, pow1, size);

    node_list_calc_ddx(head);
    rc = ck_assert_node_list_eq(head, real);
    node_list_free(&head);
    node_list_free(&real);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

// pos_03 - Найти DDX в полиноме степени 0
START_TEST(pos_03)
{
    int rc = UNIT_OK;
    node_t *head = NULL;
    size_t size = 1;
    int coef[1] = { 99 };
    int pow[1] = { 0 };
    node_list_create_from_array(&head, coef, pow, size);

    node_t *real = NULL;
    size = 1;
    int coef1[1] = { 0 };
    int pow1[1] = { 0 };
    node_list_create_from_array(&real, coef1, pow1, size);

    node_list_calc_ddx(head);
    rc = ck_assert_node_list_eq(head, real);
    node_list_free(&head);
    node_list_free(&real);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

Suite *ddx_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("DDX");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
