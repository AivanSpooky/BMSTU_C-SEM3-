#include "check_sum.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Найти SUM 2x полиномов
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    node_t *h1 = NULL;
    size_t size = 3;
    int coef[3] = { 1, 1, 1 };
    int pow[3] = { 2, 1, 0 };
    node_list_create_from_array(&h1, coef, pow, size);

    node_t *h2 = NULL;
    int coef1[3] = { 1, 1, 1 };
    int pow1[3] = { 2, 1, 0 };
    node_list_create_from_array(&h2, coef1, pow1, size);

    node_t *real_res = NULL;
    int coef2[3] = { 2, 2, 2 };
    int pow2[3] = { 2, 1, 0 };
    node_list_create_from_array(&real_res, coef2, pow2, size);

    node_t *res = node_list_add_lists(h1, h2);
    rc = ck_assert_node_list_eq(res, real_res);
    node_list_free(&h1);
    node_list_free(&h2);
    node_list_free(&res);
    node_list_free(&real_res);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

// pos_02 - Найти SUM 2х полиномов с разными степенями
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    node_t *h1 = NULL;
    size_t size = 2;
    int coef[2] = { 1, 1 };
    int pow[2] = { 2, 1 };
    node_list_create_from_array(&h1, coef, pow, size);

    node_t *h2 = NULL;
    int coef1[2] = { 1, 1 };
    int pow1[2] = { 3, 0 };
    node_list_create_from_array(&h2, coef1, pow1, size);

    node_t *real_res = NULL;
    size = 4;
    int coef2[4] = { 1, 1, 1, 1 };
    int pow2[4] = { 3, 2, 1, 0 };
    node_list_create_from_array(&real_res, coef2, pow2, size);

    node_t *res = node_list_add_lists(h1, h2);
    rc = ck_assert_node_list_eq(res, real_res);
    node_list_free(&h1);
    node_list_free(&h2);
    node_list_free(&res);
    node_list_free(&real_res);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

// pos_03 - Найти SUM 2х полиномов (один из них пустой)
START_TEST(pos_03)
{
    int rc = UNIT_OK;
    node_t *h1 = NULL;
    size_t size = 3;
    int coef[3] = { 1, 1, 1 };
    int pow[3] = { 2, 1, 0 };
    node_list_create_from_array(&h1, coef, pow, size);

    node_t *h2 = NULL;
    size = 1;
    int coef1[1] = { 0 };
    int pow1[1] = { 0 };
    node_list_create_from_array(&h2, coef1, pow1, size);

    node_t *real_res = NULL;
    size = 3;
    int coef2[3] = { 1, 1, 1 };
    int pow2[3] = { 2, 1, 0 };
    node_list_create_from_array(&real_res, coef2, pow2, size);

    node_t *res = node_list_add_lists(h1, h2);
    rc = ck_assert_node_list_eq(res, real_res);
    node_list_free(&h1);
    node_list_free(&h2);
    node_list_free(&res);
    node_list_free(&real_res);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

Suite *sum_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("SUM");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
