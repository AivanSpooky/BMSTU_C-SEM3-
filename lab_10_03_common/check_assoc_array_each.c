#include <stdlib.h>

#include "codes.h"

#include "associative_array.h"

#include "check_assoc_array_each.h"

/**
 * Добавляет значение ко всем элементам ассоц. массива
 *
 * \param[in] key - ключ
 * \param[in] num - значение по ключу
 * \param[in] param - инкремент
 *
 * \return Функция ничего не возвращает
 */
void add_value_to(const char *key, int *num, void *param)
{
    (void) key;
    int *value = param;
    *num += *value;
}


// pos_01 - Создать ассоциативный массив, заполнить тремя записями, прибавить к каждому элементу в поле значение число 5.
START_TEST(pos_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);

    char *key = "key";
    int num = 10;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    key = "another";
    num = 1;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    key = "last-one";
    num = -12;
    rc = assoc_array_insert(arr, key, num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int right_values[3] = {15, 6, -7};
    size_t cnt = 3;
    int increment = 5;
    rc = assoc_array_each(arr, add_value_to, &increment);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_cmp_values(arr, right_values, cnt);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// neg_01 - Попытка применить действие к неинициализированному ассоц. массиву
START_TEST(neg_01)
{
    int rc = UNIT_OK;
    assoc_array_t arr = NULL;

    int increment = 5;
    rc = assoc_array_each(arr, add_value_to, &increment);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_each_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_each");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);

    // Негативные тесты
    tcase_add_test(tc_core, neg_01);

    suite_add_tcase(s, tc_core);

    return s;
}
