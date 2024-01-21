#include "check_matrix_multiplication.h"
#include <stdlib.h>

#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"
#include "check_mtr.h"

// pos_01 - Умножение двух квадратных матриц
START_TEST(pos_01)
{
    mtr_t mtr1;
    mtr1.n = 3, mtr1.m = 3;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    fill_mtr(&mtr1, data1);

    mtr_t mtr2;
    mtr2.n = 3, mtr2.m = 3;
    mtr2.ptr = matrix_alloc(mtr2.n, mtr2.m);
    double data2[9] = { -1, -2, -3, -4, -5, -6, -7, -8, -9 };
    fill_mtr(&mtr2, data2);

    mtr_t mtrout;
    mtrout.n = 3, mtrout.m = 3;
    mtrout.ptr = matrix_alloc(mtrout.n, mtrout.m);
    double dataout[9] = { -30.000000, -36.000000, -42.000000, -66.000000, -81.000000, -96.000000, -102.000000, -126.000000, -150.000000 };
    fill_mtr(&mtrout, dataout);

    int rc = OK;
    mtr_t res = matrix_multiplication(&mtr1, &mtr2);

    rc = assert_mtr_eq(res, mtrout);
    ck_assert_int_eq(rc, OK);

    matrix_free(mtr1.ptr, mtr1.n);
    matrix_free(mtr2.ptr, mtr2.n);
    matrix_free(mtrout.ptr, mtrout.n);
    matrix_free(res.ptr, res.n);
}
END_TEST

// pos_02 - Умножение двух неквадратных матриц (кол-во столбцов первой равно кол-ву строк второй)
START_TEST(pos_02)
{
    mtr_t mtr1;
    mtr1.n = 2, mtr1.m = 4;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[8] = { 1, 2, 3, 5, 9, 0, 8, 5 };
    fill_mtr(&mtr1, data1);

    mtr_t mtr2;
    mtr2.n = 4, mtr2.m = 4;
    mtr2.ptr = matrix_alloc(mtr2.n, mtr2.m);
    double data2[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    fill_mtr(&mtr2, data2);

    mtr_t mtrout;
    mtrout.n = 2, mtrout.m = 4;
    mtrout.ptr = matrix_alloc(mtrout.n, mtrout.m);
    double dataout[8] = { 103.000000, 114.000000, 125.000000, 136.000000, 146.000000, 168.000000, 190.000000, 212.000000 };
    fill_mtr(&mtrout, dataout);

    int rc = OK;
    mtr_t res = matrix_multiplication(&mtr1, &mtr2);

    rc = assert_mtr_eq(res, mtrout);
    ck_assert_int_eq(rc, OK);

    matrix_free(mtr1.ptr, mtr1.n);
    matrix_free(mtr2.ptr, mtr2.n);
    matrix_free(mtrout.ptr, mtrout.n);
    matrix_free(res.ptr, res.n);
}
END_TEST

// neg_01 - Попытка сложить матрицы разных размеров
START_TEST(neg_01)
{
    mtr_t mtr1;
    mtr1.n = 3, mtr1.m = 3;
    mtr1.ptr = matrix_alloc(mtr1.n, mtr1.m);
    double data1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    fill_mtr(&mtr1, data1);

    mtr_t mtr2;
    mtr2.n = 4, mtr2.m = 4;
    mtr2.ptr = matrix_alloc(mtr2.n, mtr2.m);
    double data2[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    fill_mtr(&mtr2, data2);

    mtr_t res = matrix_addition(&mtr1, &mtr2);

    ck_assert_ptr_eq(res.ptr, NULL);
    matrix_free(mtr1.ptr, mtr1.n);
    matrix_free(mtr2.ptr, mtr2.n);
}
END_TEST


Suite *mtr_mul_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix_Multiplication");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);

    suite_add_tcase(s, tc_core);

    return s;
}
