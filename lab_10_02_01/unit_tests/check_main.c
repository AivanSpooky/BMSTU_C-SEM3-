#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "err_codes.h"

#include "check_node.h"
#include "check_val.h"
#include "check_ddx.h"
#include "check_sum.h"
#include "check_dvd.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("VAL tests:\n");
    s = val_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("DDX tests:\n");
    s = ddx_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("SUM tests:\n");
    s = sum_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("DVD tests:\n");
    s = dvd_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    return (number_failed == 0) ? UNIT_OK : UNIT_ERR;
}