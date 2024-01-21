#include "check_read_films.h"
#include <stdlib.h>

#include "check_films.h"
#include "film_t.h"
#include "film_arr.h"
#include "film_alloc.h"

// pos_01 - В файле находится 3 фильма (порядок по названию)
START_TEST(pos_01)
{
    int rc = UNIT_OK;

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    rc = read_films(f, films_in, &n, film_cmp_by_title);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_eq(rc, OK);

    film_t films_out[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, };

    rc = ck_assert_film_arr_eq(films_in, n, films_out, n);
    ck_assert_int_eq(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

// pos_02 - В файле находится 1 фильм (порядок по имени)
START_TEST(pos_02)
{
    int rc = UNIT_OK;

    size_t n = 1;
    film_t films[1] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    rc = read_films(f, films_in, &n, film_cmp_by_name);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_eq(rc, OK);

    film_t films_out[1] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, };

    rc = ck_assert_film_arr_eq(films_in, n, films_out, n);
    ck_assert_int_eq(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

// pos_03 - В файле находится 3 фильма (порядок по году, изначально все в обратном порядке)
START_TEST(pos_03)
{
    int rc = UNIT_OK;

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-2", .name = "author-3", .year = 3000 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    rc = read_films(f, films_in, &n, film_cmp_by_year);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_eq(rc, OK);

    film_t films_out[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 }, };
    rc = ck_assert_film_arr_eq(films_in, n, films_out, n);
    ck_assert_int_eq(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

// neg_01 - В файле нет фильмов
START_TEST(neg_01)
{
    int rc = UNIT_OK;

    size_t n = 0;
    film_t films[1] = { {.title = ""} };

    FILE *f = fopen("unit_tests/pos_01_in.txt", "w");
    ck_assert_ptr_ne(f, NULL);
    for (size_t i = 0; i < n; i++)
        print_film(f, &films[i]);
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    rc = read_films(f, films_in, &n, film_cmp_by_name);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

// neg_02 - В файле фильм задан не полностью
START_TEST(neg_02)
{
    int rc = UNIT_OK;

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
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    size_t n1 = 3;
    rc = read_films(f, films_in, &n1, film_cmp_by_name);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

// neg_03 - В файле фильм имеет отрицательный год выпуска
START_TEST(neg_03)
{
    int rc = UNIT_OK;

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
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    size_t n1 = 3;
    rc = read_films(f, films_in, &n1, film_cmp_by_name);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

// neg_04 - В файле фильм имеет буквы в поле год выпуска
START_TEST(neg_04)
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
    fprintf(f, "letters");
    fclose(f);

    f = fopen("unit_tests/pos_01_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);
    film_t *films_in = calloc(n, sizeof(film_t));
    ck_assert_ptr_ne(films_in, NULL);

    rc = read_films(f, films_in, &n, film_cmp_by_name);
    fclose(f);
    remove("unit_tests/pos_01_in.txt");
    ck_assert_int_ne(rc, UNIT_OK);

    film_arr_free(films_in, n);
}
END_TEST

Suite *read_films_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("read_films");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);
    tcase_add_test(tc_core, neg_03);
    tcase_add_test(tc_core, neg_04);

    suite_add_tcase(s, tc_core);

    return s;
}
