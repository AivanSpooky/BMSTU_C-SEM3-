#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "err_codes.h"
#include "check_films.h"
#include "check_find_films_cnt.h"
#include "check_read_films.h"
#include "check_binary_search.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("Find_Films_Cnt tests:\n");
    s = film_findcnt_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Read_Films tests:\n");
    s = read_films_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("Binary_Search:\n");
    s = bin_search_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    return (number_failed == 0) ? OK : ERR;
}