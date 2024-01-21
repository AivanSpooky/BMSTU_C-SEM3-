#ifndef MTR_ALLOC_H__

#define MTR_ALLOC_H__

#include <stdlib.h>
#include "err_codes.h"

/**
 * @brief Функция освобождает матрицу
 * @param double **matrix - указатели на строки матрицы и сами значения матрицы
 * @param size_t n - количество строк матрицы
 * @return Функция ничего не возвращает
*/
void matrix_free(double **matrix, size_t n);

/**
 * @brief Функция выделяет память под матрицу
 * @param size_t n - количество строк матрицы
 * @param size_t m - количество столбцов матрицы
 * @return Функция возвращает получившийся указатель
*/
double **matrix_alloc(size_t n, size_t m);

#endif
