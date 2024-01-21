#ifndef CHECK_MTR_H__

#define CHECK_MTR_H__

#include <check.h>
#include <math.h>
#include "mtr_io.h"
#include "mtr_alloc.h"

#define UNIT_OK 0
#define UNIT_ERR 1

#define UNIT_ERR_ROW_EQUAL 1
#define UNIT_ERR_COL_EQUAL 2
#define UNIT_ERR_NOT_EQUAL 3

// Функция возвращает следующие коды ошибок:
// 0 - все хорошо
// 1 - не совпадают количества строк
// 2 - не совпадают количества столбцов
// 3 - не совпадают некоторые элементы
int assert_mtr_eq(const mtr_t mtr1, const mtr_t mtr2);

// Функция заполняет матрицу значениями из values
void fill_mtr(mtr_t *mtr, double *values);

#endif