#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "err_codes.h"
#include "check_key.h"
#include "check_mysort.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("Key tests:\n");
    s = key_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Sort tests:\n");
    s = sort_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    return (number_failed == 0) ? OK : ERR;
}