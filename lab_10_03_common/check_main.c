#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "associative_array.h"

#include "check_assoc_array_create.h"
#include "check_assoc_array_insert.h"
#include "check_assoc_array_find.h"
#include "check_assoc_array_remove.h"
#include "check_assoc_array_clear.h"
#include "check_assoc_array_each.h"
#include "check_assoc_array_min.h"
#include "check_assoc_array_max.h"

#include "codes.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("assoc_array_create tests:\n");
    s = assoc_array_create_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_insert tests:\n");
    s = assoc_array_insert_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_find tests:\n");
    s = assoc_array_find_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_remove tests:\n");
    s = assoc_array_remove_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_clear tests:\n");
    s = assoc_array_clear_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_each tests:\n");
    s = assoc_array_each_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_min tests:\n");
    s = assoc_array_min_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("assoc_array_max tests:\n");
    s = assoc_array_max_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    return (number_failed == 0) ? UNIT_OK : UNIT_ERR;
}