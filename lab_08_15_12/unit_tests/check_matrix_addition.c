#include "check_matrix_addition.h"
#include <stdlib.h>

#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"
#include "check_mtr.h"

// pos_01 - Сложение двух квадратных матриц
START_TEST(pos_01)
{
    double data1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    double *mtr[3] = { data1[0], data1[1], data1[2] };
    mtr_t mtr1 = { .n = 3, .m = 3, .ptr = mtr };

    mtr_t mtr2 = { .n = 3, .m = 3, .ptr = mtr };

    mtr_t mtrout;
    mtrout.n = 3, mtrout.m = 3;
    double dataout[3][3] = { { 2.000000, 4.000000, 6.000000 }, { 8.000000, 10.000000, 12.000000 }, { 14.000000, 16.000000, 18.000000 } };
    double *mtrou[3] = { dataout[0], dataout[1], dataout[2] };
    mtrout.ptr = mtrou;

    int rc = OK;
    mtr_t res = matrix_addition(&mtr1, &mtr2);

    rc = assert_mtr_eq(res, mtrout);
    ck_assert_int_eq(rc, OK);

    matrix_free(res.ptr, res.n);
}
END_TEST

// pos_02 - Сложение двух неквадратных матриц
START_TEST(pos_02)
{
    mtr_t mtr1;
    mtr1.n = 2, mtr1.m = 4;
    double data1[2][4] = { { 1, 2, 3, 4 }, { 9, 8, 7, 6 } };
    double *mdata1[2] = { data1[0], data1[1] };
    mtr1.ptr = mdata1;

    mtr_t mtr2;
    mtr2.n = 2, mtr2.m = 4;
    double data2[2][4] = { { 4, 3, 2, 1 }, { 6, 7, 8, 9 } };
    double *mdata2[2] = { data2[0], data2[1] };
    mtr2.ptr = mdata2;

    mtr_t mtrout;
    mtrout.n = 2, mtrout.m = 4;
    double dataout[2][4] = { { 5.000000, 5.000000, 5.000000, 5.000000 }, { 15.000000, 15.000000, 15.000000, 15.000000 } };
    double *mdataout[2] = { dataout[0], dataout[1] };
    mtrout.ptr = mdataout;

    int rc = OK;
    mtr_t res = matrix_addition(&mtr1, &mtr2);

    rc = assert_mtr_eq(res, mtrout);
    ck_assert_int_eq(rc, OK);

    matrix_free(res.ptr, res.n);
}
END_TEST

// neg_01 - Попытка сложить матрицы разных размеров
START_TEST(neg_01)
{
    mtr_t mtr1;
    mtr1.n = 3, mtr1.m = 3;
    double data1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9} };
    double *mdata1[3] = { data1[0], data1[1], data1[2] };
    mtr1.ptr = mdata1;

    mtr_t mtr2;
    mtr2.n = 3, mtr2.m = 2;
    double data2[3][2] = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    double *mdata2[3] = { data2[0], data2[1], data2[2] };
    mtr1.ptr = mdata2;

    mtr_t res = matrix_addition(&mtr1, &mtr2);

    ck_assert_ptr_eq(res.ptr, NULL);
}
END_TEST


Suite *mtr_add_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix_Addition");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);

    suite_add_tcase(s, tc_core);

    return s;
}
