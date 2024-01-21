#include "check_find_films_cnt.h"
#include <stdlib.h>

#include "check_films.h"
#include "film_t.h"
#include "film_arr.h"
#include "film_alloc.h"

// pos_01 - В файле находится 3 фильма
START_TEST(pos_01)
{
    int rc = OK;
    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    size_t n1 = 0;
    rc = find_films_cnt(f, &n1);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(n1, n);
}
END_TEST

// pos_02 - В файле находится 1 фильм
START_TEST(pos_02)
{
    int rc = OK;
    size_t n = 1;
    film_t films[1] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 } };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    size_t n1 = 0;
    rc = find_films_cnt(f, &n1);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(n1, n);
}
END_TEST

// neg_01 - В файле нет фильмов
START_TEST(neg_01)
{
    int rc = OK;
    size_t n = 0;
    film_t films[1] = { {.title = ""} };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    size_t n1 = 0;
    rc = find_films_cnt(f, &n1);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, OK);
}
END_TEST

// neg_02 - В файле фильм задан не полностью
START_TEST(neg_02)
{
    int rc = OK;
    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2",} };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    size_t n1 = 0;
    rc = find_films_cnt(f, &n1);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, OK);
}
END_TEST

// neg_03 - В файле фильм имеет отрицательный год выпуска
START_TEST(neg_03)
{
    int rc = OK;
    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = -3000 } };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    size_t n1 = 0;
    rc = find_films_cnt(f, &n1);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, OK);
}
END_TEST

// neg_04 - В файле фильм имеет буквы в поле год выпуска
START_TEST(neg_04)
{
    int rc = UNIT_OK;
    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fprintf(f, "letters");
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    size_t n1 = 0;
    rc = find_films_cnt(f, &n1);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, OK);
}
END_TEST

Suite *film_findcnt_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("find_films_cnt");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);
    tcase_add_test(tc_core, neg_03);
    tcase_add_test(tc_core, neg_04);

    suite_add_tcase(s, tc_core);

    return s;
}
