#ifndef MTR_IO_H__

#define MTR_IO_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "consts.h"
#include "err_codes.h"
#include "mtr_alloc.h"

#define EPS 1e-6

typedef struct
{
    size_t n;
    size_t m;
    double **ptr;
} mtr_t;

/**
 * @brief Функция проверяет корректность существующей матрицы
 * @param const mtr_t *mtr - матрица
 * @return Функция возвращает код ошибки
*/
int matrix_check(const mtr_t *mtr);

/**
 * @brief Функция вводит матрицу из файла и сохраняет в переменной
 * @param FILE *f - файл
 * @param mtr_t *mtr - матрица
 * @return Функция возвращает код ошибки
*/
int matrix_input(FILE *f, mtr_t *mtr);

/**
 * @brief Функция записывает матрицу в файл, указывая только положение ненулевых элементов
 * @param FILE *fout - выходной файл
 * @param const mtr_t *mtr - матрица
 * @return Функция ничего не возвращает
*/
void matrix_output(FILE *fout, const mtr_t *mtr);

// void printMtr(mtr_t mtr);

#endif
