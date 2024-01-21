#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "err_codes.h"
#include "check_mtr.h"
#include "check_matrix_inverse.h"
#include "check_matrix_determinant.h"
#include "check_matrix_addition.h"
#include "check_matrix_multiplication.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("Matrix_Inverse tests:\n");
    s = mtr_inv_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Matrix_Determinant:\n");
    s = mtr_det_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Matrix_Addition tests:\n");
    s = mtr_add_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Matrix_Multiplication:\n");
    s = mtr_mul_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    return (number_failed == 0) ? UNIT_OK : UNIT_ERR;
}