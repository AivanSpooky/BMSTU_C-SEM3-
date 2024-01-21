#ifndef __INPUT_OUTPUT_FUNCS__

#define __INPUT_OUTPUT_FUNCS__

#include <stdio.h>
#include "consts.h"
#include "err_codes.h"

// Функция ввода матрицы
// int a[][M] - матрица
// size_t *a_n - указатель на кол-во строк матрицы
// size_t *a_m - указатель на кол-во столбцов матрицы
// Функция возвращает код ошибки
int input(int a[][M], size_t *a_n, size_t *a_m);

// Функция вывода массива
// int a[] - массив
// size_t a_n - кол-во элементов в массиве
// Функция ничего не возвращает
void print(const int a[], const size_t a_n);

#endif
