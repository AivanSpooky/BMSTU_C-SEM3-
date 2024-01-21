#ifndef __PROCESS_H__

#define __PROCESS_H__

#include <stdio.h>
#include <stdbool.h>

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция считает среднее арифметическое чисел в файле
 * @param FILE *f - файл с вещественными числами
 * @param double *avg - среднее арифметическое
 * @param size_t *n - число элементов (вещестенных чисел) в файле
 * @return Функция возвращает код ошибки
*/
int calc_avg(FILE *f, double *avg, size_t *n);

/**
 * @brief Функция считает среднее арифметическое чисел в файле
 * @param FILE *f - файл с вещественными числами
 * @param double avg - среднее арифметическое
 * @param size_t n - число элементов (вещестенных чисел) в файле
 * @param double *s_sq - дисперсия
 * @return Функция возвращает код ошибки
*/
int calc_s_sq(FILE *f, double avg, size_t n, double *s_sq);

#endif
