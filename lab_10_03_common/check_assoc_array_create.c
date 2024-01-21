#include <stdlib.h>

#include "associative_array.h"

#include "check_assoc_array_create.h"

// pos_01 - Создать ассоциативный массив
START_TEST(pos_01)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_ne(arr, NULL);  
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_create_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("assoc_array_create");
    tc_core = tcase_create("Core");

    // Позитивные тесты
    tcase_add_test(tc_core, pos_01);

    // Негативные тесты

    suite_add_tcase(s, tc_core);

    return s;
}
