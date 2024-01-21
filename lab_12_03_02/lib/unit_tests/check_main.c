#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "check_cmp_funcs.h"
#include "check_is_prime.h"
#include "check_fill_arr_with_primes.h"
#include "check_rewrite_arr.h"

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    printf("Unit tests:\n\n");

    printf("is_prime tests:\n");
    s = is_prime_suit();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("fill_arr_with_primes tests:\n");
    s = fill_arr_with_primes_suit();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    printf("rewrite_arr tests:\n");
    s = rewrite_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");

    return (number_failed == 0) ? OK : ERR_NOT_EQUAL;
}