#ifndef FILE_OP_H__

#define FILE_OP_H__

#include <stdio.h>
#include <stdbool.h>

#include "funcs.h"

#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция считает количество элементов, записанных в файле
 * @param FILE *file - файл
 * @param size_t *n - количество элементов
 * @return Функция возвращает код ошибки
*/
int find_count(FILE *file, size_t *n);

/**
 * @brief Функция заполняет массив целыми числами и файла
 * @param FILE *file - файл
 * @param int *pbeg - указатель на начало массива
 * @param int *pend - указатель на конец массива
 * @return Функция возвращает код ошибки
*/
int array_fill(FILE *file, int *pbeg, int *pend);

/**
 * @brief Функция заполняет файл целыми числами из массива
 * @param FILE *file - файл
 * @param const int *pbeg - указатель на начало массива
 * @param const int *pend - указатель на конец массивав
 * @return Функция ничего возвращает
*/
void print_arr_to_file(FILE *file, const int *pbeg, const int *pend);

/**
 * @brief Функция сортирует массив целых чисел и записывает его содержимое в файл с названием filename
 * @param char *filename - название файла
 * @param const int *ptr - массив целых чисел
 * @param const size_t n - кол-во элементов массива
 * @return Функция ничего возвращает
*/
int print_sorted_arr_to_outfile(char *filename, int *ptr, const size_t n);

#endif
