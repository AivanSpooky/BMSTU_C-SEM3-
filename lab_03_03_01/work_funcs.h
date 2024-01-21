#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"

// Функция находит индекс первого вхождения максимума в массив
// int *a - массив
// size_t a_m - кол-во элементов массива
// Функция возвращает индекс первого вхождения максимума в массив
size_t find_max_index(const int a[], const size_t a_m);

// Функция сортировки выбором
// int a[][M] - матрица
// size_t b[] - массив индексов максимумов в каждой строке матрицы
// size_t a_n - кол-во строк матрицы
// size_t a_m - кол-во столбцов матрицы
void selection_sort(int a[][M], const size_t a_n, const size_t a_m);

#endif
