#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"
#include "err_codes.h"

// Функция считает сумму цифр числа
// int n - целое число
// Функция возвращает сумму цифр числа
int digit_sum(int n);

// Функция циклически сдвигает элементы массива влево на 1 элемент
// int b[] - массив
// size_t elems - кол-во элементов массива
// Функция ничего не возвращает
void left_step(int b[], size_t elems);

// Функция заменяет элементы матрицы с суммой цифр больше 10 
// (в порядке обхода матрицы по строкам) на те же самые, сдвинутые
// циклически на 3 единицы влево
// int a[][M] - матрица
// size_t a_n - кол-во строк матрицы
// size_t a_n - кол-во столбцов матрицы
// Функция возвращает код ошибки
int replace(int a[][M], size_t a_n, size_t a_m);

#endif
