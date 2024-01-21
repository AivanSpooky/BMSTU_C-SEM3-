#ifndef CHECK_MTR_H__

#define CHECK_MTR_H__

#include <check.h>
#include <math.h>
#include "film_t.h"
#include "film_arr.h"

#define ERR 1

#define UNIT_OK 0
#define UNIT_ERR_TITLE_EQUAL 1
#define UNIT_ERR_NAME_EQUAL 2
#define UNIT_ERR_YEAR_EQUAL 3
#define UNIT_ERR_N_EQUAL 4

/**
 * @brief Функция сравнивает два значения типа bool
 * @return Функция возвращает признак сравнения (0 - равны, 1 - не равны)
*/
int ck_assert_bool_eq(bool p1, bool p2);

// Функция возвращает следующие коды ошибок:
// 0 - все хорошо
// 1 - не совпадают количества строк
// 2 - не совпадают количества столбцов
// 3 - не совпадают некоторые элементы
int ck_assert_film_arr_eq(const film_t *f1, size_t n1, const film_t *f2, size_t n2);

// Функция возвращает следующие коды ошибок:
// 0 - все хорошо
// 1 - не совпадают количества строк
// 2 - не совпадают количества столбцов
// 3 - не совпадают некоторые элементы
int ck_assert_film_eq(const film_t *film1, const film_t *film2);

#endif