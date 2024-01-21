#include "check_binary_search.h"
#include <stdlib.h>

#include "check_films.h"
#include "film_t.h"
#include "film_arr.h"
#include "film_alloc.h"

// pos_01 - Найти фильм по имени названию фильма
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    bool found;
    film_t film;
    film_init_default(&film);
    cmp_t comparator = film_cmp_by_title;
    film.title = "Film-3";
    ck_assert_ptr_ne(film.title, NULL);

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    found = binary_search(films, n, &film, comparator);
    ck_assert_int_eq(ck_assert_bool_eq(found, true), OK);

    film_t film_out;
    film_init_default(&film_out);
    film_out.title = strdup("Film-3");
    film_out.name = strdup("author-1");
    film_out.year = 2000;

    rc = ck_assert_film_eq(&film, &film_out);
    film_free(&film_out);
    film_free(&film);
    ck_assert_int_eq(rc, UNIT_OK);
}
END_TEST

// pos_02 - Найти фильм по имени автора
START_TEST(pos_02)
{
    int rc = UNIT_OK;
    bool found;
    film_t film;
    film_init_default(&film);
    cmp_t comparator = film_cmp_by_name;
    film.name = "author-1";
    ck_assert_ptr_ne(film.name, NULL);

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1000 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    found = binary_search(films, n, &film, comparator);
    ck_assert_int_eq(ck_assert_bool_eq(found, true), OK);

    film_t film_out;
    film_init_default(&film_out);
    film_out.title = strdup("Film-3");
    film_out.name = strdup("author-1");
    film_out.year = 2000;

    rc = ck_assert_film_eq(&film, &film_out);
    film_free(&film_out);
    film_free(&film);
    ck_assert_int_eq(rc, UNIT_OK);
}
END_TEST

// pos_03 - Найти фильм по году выпуска
START_TEST(pos_03)
{
    int rc = UNIT_OK;
    bool found;
    film_t film;
    film_init_default(&film);
    cmp_t comparator = film_cmp_by_year;
    film.year = 1942;

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    found = binary_search(films, n, &film, comparator);
    ck_assert_int_eq(ck_assert_bool_eq(found, true), OK);

    film_t film_out;
    film_init_default(&film_out);
    film_out.title = strdup("Film-1");
    film_out.name = strdup("author-2");
    film_out.year = 1942;

    rc = ck_assert_film_eq(&film, &film_out);
    film_free(&film_out);
    film_free(&film);
    ck_assert_int_eq(rc, UNIT_OK);
}
END_TEST

// neg_01 - Не найден фильм по имени названию фильма
START_TEST(neg_01)
{
    bool found;
    film_t film;
    film_init_default(&film);
    cmp_t comparator = film_cmp_by_title;
    film.title = "Film-367";
    ck_assert_ptr_ne(film.title, NULL);

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    found = binary_search(films, n, &film, comparator);
    //film_free(&film);
    ck_assert_int_eq(ck_assert_bool_eq(found, false), OK);
}
END_TEST

// neg_02 - Не найден фильм по имени автора
START_TEST(neg_02)
{
    bool found;
    film_t film;
    film_init_default(&film);
    cmp_t comparator = film_cmp_by_name;
    film.name = strdup("author-SmirnovIvan");
    ck_assert_ptr_ne(film.name, NULL);

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    found = binary_search(films, n, &film, comparator);
    film_free(&film);
    ck_assert_int_eq(ck_assert_bool_eq(found, false), OK);
}
END_TEST

// neg_03 - Не найден фильм по году выхода
START_TEST(neg_03)
{
    bool found;
    film_t film;
    film_init_default(&film);
    cmp_t comparator = film_cmp_by_year;
    film.year = 19421943;

    size_t n = 3;
    film_t films[3] = { \
    { .title = "Film-1", .name = "author-2", .year = 1942 }, \
    { .title = "Film-3", .name = "author-1", .year = 2000 }, \
    { .title = "Film-2", .name = "author-3", .year = 3000 } };

    found = binary_search(films, n, &film, comparator);
    film_free(&film);
    ck_assert_int_eq(ck_assert_bool_eq(found, false), OK);
}
END_TEST


Suite *bin_search_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Binary Search");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);
    tcase_add_test(tc_core, neg_02);
    tcase_add_test(tc_core, neg_03);

    suite_add_tcase(s, tc_core);

    return s;
}
