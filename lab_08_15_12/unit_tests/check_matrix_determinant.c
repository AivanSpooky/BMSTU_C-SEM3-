#include "check_matrix_determinant.h"
#include <stdlib.h>

#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"
#include "check_mtr.h"

// pos_01 - Найти определитель матрицы (!=0)
START_TEST(pos_01)
{
    double data1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 8 } };
    double *mtr[3] = { data1[0], data1[1], data1[2] };
    mtr_t mtr1 = { .n = 3, .m = 3, .ptr = mtr };

    double real_det = 3;

    double det = 0;
    det = matrix_determinant((const double **)mtr1.ptr, mtr1.n);

    ck_assert_double_lt(det, real_det + EPS);
}
END_TEST

// pos_02 - Найти определитель матрицы (=0)
START_TEST(pos_02)
{
    double data1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    double *mtr[3] = { data1[0], data1[1], data1[2] };
    mtr_t mtr1 = { .n = 3, .m = 3, .ptr = mtr };

    double real_det = 0;

    double det = 0;
    det = matrix_determinant((const double **)mtr1.ptr, mtr1.n);

    ck_assert_double_lt(det, real_det + EPS);
}
END_TEST


Suite *mtr_det_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix_Determinant");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
