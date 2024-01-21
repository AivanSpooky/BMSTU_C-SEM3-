#include <check_mysort.h>
#include <stdlib.h>

#include "funcs.h"

// Функция сравнивает массивы по-элементно
void ck_assert_arr_eq(void *arr1, void *arr2, size_t cnt, size_t size, asserttype assert_elems)
{
    char *pbeg1 = arr1;
    char *pend1 = pbeg1 + (cnt) * size;
    char *pbeg2 = arr2;
    char *pend2 = pbeg2 + (cnt) * size;

    char *p1 = pbeg1;
    char *p2 = pbeg2;
    while (p1 < pend1 && p2 < pend2)
    {
        assert_elems(p1, p2);
        p1 += size;
        p2 += size;
    }
}

// Assert для int
void as_int(void *l, void *r)
{
    int *lp = l;
    int *rp = r;
    ck_assert_int_eq(*lp, *rp);
}

// Assert для double
void as_double(void *l, void *r)
{
    double *lp = l;
    double *rp = r;
    ck_assert_double_eq(*lp, *rp);
}

// Assert для string
void as_string(void *l, void *r)
{
    char *lp = l;
    char *rp = r;
    ck_assert_int_eq(*lp, *rp);
}

// pos_01 - Сортировка упорядоченного в обратном порядке массива чисел 
START_TEST(pos_01)
{
    int arr[] = {4, 2, 3, 1};
    int expected[] = {1, 2, 3, 4};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), int_cmp);

    // for (size_t i = 0; i < cnt; i++)
    // {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");
    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(int), as_int);
}
END_TEST

// pos_02 - Пустой массив
START_TEST(pos_02)
{
    int *arr = NULL;
    int *expected = NULL;
    size_t cnt = 0;

    mysort(arr, cnt, 0, int_cmp);

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(int), as_int);
}
END_TEST

// pos_03 - Массив вещественных чисел, упорядоченных в порядке возрастания
START_TEST(pos_03)
{
    double arr[] = {1.1, 2.2, 2.25, 3, 5.0};
    double expected[] = {1.1, 2.2, 2.25, 3, 5.0};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), double_cmp);;

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(double), as_double);
}
END_TEST

// pos_04 - Массив вещественных чисел
START_TEST(pos_04)
{
    double arr[] = {1.1, 2.29, 2.25, 3, 5.0};
    double expected[] = {1.1, 2.25, 2.29, 3, 5.0};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), double_cmp);;

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(double), as_double);
}
END_TEST

// pos_05 - Массив строк
START_TEST(pos_05)
{
    char arr[][7] = {"Banana", "Apple", "Orange", "Peach", "Lemon"};
    char expected[][7] = {"Apple", "Banana", "Lemon", "Orange", "Peach"};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), string_cmp);

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(char), as_string);
}
END_TEST

// pos_06 - Сортировка массива из одного элемента
START_TEST(pos_06)
{
    int arr[] = {5};
    int expected[] = {5};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), int_cmp);

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(int), as_int);
}
END_TEST

// pos_07 - Сортировка массива из 2х элементов (по возрастанию)
START_TEST(pos_07)
{
    int arr[] = {5, 10};
    int expected[] = {5, 10};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), int_cmp);

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(int), as_int);
}
END_TEST

// pos_08 - Сортировка массива из 2х элементов (по убыванию)
START_TEST(pos_08)
{
    int arr[] = {5, 10};
    int expected[] = {5, 10};
    size_t cnt = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, cnt, sizeof(arr[0]), int_cmp);

    // Проверка результата
    ck_assert_arr_eq(arr, expected, cnt, sizeof(int), as_int);
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("mysort");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);
    tcase_add_test(tc_core, pos_02);
    tcase_add_test(tc_core, pos_03);
    tcase_add_test(tc_core, pos_04);
    tcase_add_test(tc_core, pos_05);
    tcase_add_test(tc_core, pos_06);
    tcase_add_test(tc_core, pos_07);
    tcase_add_test(tc_core, pos_08);

    suite_add_tcase(s, tc_core);

    return s;
}
