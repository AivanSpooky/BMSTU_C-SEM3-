#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "err_codes.h"

#include "check_node.h"
#include "check_find.h"
#include "check_pop_front.h"
#include "check_reverse.h"
#include "check_sort.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("Find tests:\n");
    s = find_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Pop-Front tests:\n");
    s = pop_front_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Reverse tests:\n");
    s = reverse_suite();
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

    return (number_failed == 0) ? UNIT_OK : UNIT_ERR;
}