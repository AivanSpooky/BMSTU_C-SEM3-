#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdbool.h>
#include "consts.h"

// Проверка массива на симметрию (по элементам)
// int a[] - массив
// size_t a_n - кол-во элементов в массиве
// Функция возвращает признак (true/false)
bool symmetry(const int a[], const size_t a_n);

// Формирование одномерного массива на основе симметричности строк матрицы
// int a[][M] - матрица
// int b[] - массив
// size_t a_n - кол-во строк матрицы
// size_t a_m - кол-во столбцов матрицы
// Функция ничего не возвращает
void replace_elems(int a[][M], int b[], const size_t a_n, const size_t a_m);

#endif
