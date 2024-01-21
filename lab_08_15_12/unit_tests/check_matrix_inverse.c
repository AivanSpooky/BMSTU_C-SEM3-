#include "check_matrix_inverse.h"
#include <stdlib.h>

#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"
#include "check_mtr.h"

// pos_01 - Найти обратную матрицу к квадратной матрице (3x3)
START_TEST(pos_01)
{
    mtr_t mtr1;
    mtr1.n = 3, mtr1.m = 3;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 8 };
    fill_mtr(&mtr1, data1);

    mtr_t mtr2;
    mtr2.n = 3, mtr2.m = 3;
    mtr2.ptr = matrix_alloc(mtr2.n, mtr2.m);
    //double data2[9] = { -2.666667, 2.666667, -1.000000, 3.333333, -4.333333, 2.000000, -1.000000, 2.000000, -1.000000 };
    double data2[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    fill_mtr(&mtr2, data2);

    int rc = OK;
    mtr_t res = matrix_inverse(&mtr1);

    mtr_t check = matrix_multiplication(&res, &mtr1);
    rc = assert_mtr_eq(check, mtr2);
    ck_assert_int_eq(rc, OK);

    matrix_free(mtr1.ptr, mtr1.n);
    matrix_free(mtr2.ptr, mtr2.n);
    matrix_free(check.ptr, check.n);
    matrix_free(res.ptr, res.n);
}
END_TEST

// pos_02 - Найти обратную матрицу к квадратной матрице (2x2)
START_TEST(pos_02)
{
    mtr_t mtr1;
    mtr1.n = 2, mtr1.m = 2;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[4] = { 1, 4, 4, 8 };
    fill_mtr(&mtr1, data1);

    mtr_t mtr2;
    mtr2.n = 2, mtr2.m = 2;
    mtr2.ptr = matrix_alloc(mtr2.n, mtr2.m);
    //double data2[9] = { -2.666667, 2.666667, -1.000000, 3.333333, -4.333333, 2.000000, -1.000000, 2.000000, -1.000000 };
    double data2[9] = { 1, 0, 0, 1 };
    fill_mtr(&mtr2, data2);

    int rc = OK;
    mtr_t res = matrix_inverse(&mtr1);

    mtr_t check = matrix_multiplication(&res, &mtr1);
    rc = assert_mtr_eq(check, mtr2);
    ck_assert_int_eq(rc, OK);

    matrix_free(mtr1.ptr, mtr1.n);
    matrix_free(mtr2.ptr, mtr2.n);
    matrix_free(check.ptr, check.n);
    matrix_free(res.ptr, res.n);
}
END_TEST

// neg_01 - Определиитель матрицы равен нулю
START_TEST(neg_01)
{
    mtr_t mtr1;
    mtr1.n = 3, mtr1.m = 3;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    fill_mtr(&mtr1, data1);

    mtr_t res = matrix_inverse(&mtr1);
    ck_assert_ptr_eq(res.ptr, NULL);

    matrix_free(mtr1.ptr, mtr1.n);
}
END_TEST

// neg_02 - Попытка найти обратную матрицу к неквадратной
START_TEST(neg_02)
{
    mtr_t mtr1;
    mtr1.n = 3, mtr1.m = 4;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[12] = { 1, 2, 3, 5, 4, 5, 6, 5, 7, 8, 9, 5 };
    fill_mtr(&mtr1, data1);

    mtr_t res = matrix_inverse(&mtr1);
    ck_assert_ptr_eq(res.ptr, NULL);

    matrix_free(mtr1.ptr, mtr1.n);
}
END_TEST

Suite *mtr_inv_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix_Inverse");
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
