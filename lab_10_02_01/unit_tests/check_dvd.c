#include "check_dvd.h"
#include <stdlib.h>
#include "err_codes.h"

#include "check_node.h"

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

// pos_01 - Найти DVD полиномa
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    node_t *head = NULL;
    size_t size = 3;
    int coef[3] = { 4, 12, 1 };
    int pow[3] = { 2, 1, 0 };
    node_list_create_from_array(&head, coef, pow, size);

    node_t *even = NULL;
    node_t *odd = NULL;

    node_t *real_even = NULL;
    size = 2;
    int coef1[2] = { 4, 1 };
    int pow1[2] = { 2, 0 };
    node_list_create_from_array(&real_even, coef1, pow1, size);

    node_t *real_odd = NULL;
    size = 1;
    int coef2[1] = { 12 };
    int pow2[1] = { 1 };
    node_list_create_from_array(&real_odd, coef2, pow2, size);

    node_list_split_lists(head, &even, &odd);
    rc = ck_assert_node_list_eq(even, real_even);
    rc = (rc == UNIT_OK) ? ck_assert_node_list_eq(odd, real_odd) : rc;
    node_list_free(&head);
    node_list_free(&even);
    node_list_free(&odd);
    node_list_free(&real_even);
    node_list_free(&real_odd);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

// pos_02 - Найти DVD полиномa только с четными степенями
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    node_t *head = NULL;
    size_t size = 3;
    int coef[3] = { 4, 4, 1 };
    int pow[3] = { 4, 2, 0 };
    node_list_create_from_array(&head, coef, pow, size);

    node_t *even = NULL;
    node_t *odd = NULL;

    node_t *real_even = NULL;
    size = 3;
    int coef1[3] = { 4, 4, 1 };
    int pow1[3] = { 4, 2, 0 };
    node_list_create_from_array(&real_even, coef1, pow1, size);

    node_t *real_odd = NULL;

    node_list_split_lists(head, &even, &odd);
    rc = ck_assert_node_list_eq(even, real_even);
    rc = (rc == UNIT_OK) ? ck_assert_node_list_eq(odd, real_odd) : rc;
    node_list_free(&head);
    node_list_free(&even);
    node_list_free(&odd);
    node_list_free(&real_even);
    node_list_free(&real_odd);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

// pos_03 - Найти DVD полиномa только с нечетными степенями
START_TEST(pos_03)
{
    int rc = UNIT_OK;
    node_t *head = NULL;
    size_t size = 3;
    int coef[3] = { 4, 4, 1 };
    int pow[3] = { 5, 3, 1 };
    node_list_create_from_array(&head, coef, pow, size);

    node_t *even = NULL;
    node_t *odd = NULL;

    node_t *real_even = NULL;

    node_t *real_odd = NULL;
    size = 3;
    int coef2[3] = { 4, 4, 1 };
    int pow2[3] = { 5, 3, 1 };
    node_list_create_from_array(&real_odd, coef2, pow2, size);

    node_list_split_lists(head, &even, &odd);
    rc = ck_assert_node_list_eq(even, real_even);
    rc = (rc == UNIT_OK) ? ck_assert_node_list_eq(odd, real_odd) : rc;
    node_list_free(&head);
    node_list_free(&even);
    node_list_free(&odd);
    node_list_free(&real_even);
    node_list_free(&real_odd);
    ck_assert_int_eq(rc, UNIT_OK); 
}
END_TEST

Suite *dvd_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("DVD");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
