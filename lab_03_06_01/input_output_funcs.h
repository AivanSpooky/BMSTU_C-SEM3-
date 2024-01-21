#ifndef __INPUT_OUTPUT_FUNCS__

#define __INPUT_OUTPUT_FUNCS__

#include <stdio.h>
#include <stdlib.h>
#include "consts.h"
#include "err_codes.h"

// Функция ввода размера матрицы
// int a[][M] - матрица
// size_t *a_n - указатель на кол-во строк матрицы
// size_t *a_m - указатель на кол-во столбцов матрицы
// Функция возвращает код ошибки
int input_n_m(size_t *a_n, size_t *a_m);

// Функция вывода матрицы
// int a[][M] - матрица
// size_t a_n - кол-во строк матрицы
// size_t a_m - кол-во столбцов матрицы
// Функция ничего не возвращает
void printm(int a[][M], const size_t a_n, const size_t a_m);

#endif
