#ifndef __FILE_OPT_H__

#define __FILE_OPT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#include "file_check.h"

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция заполняет бинарный файл случайными числами 
 * @param FILE* file - файл
 * @param size_t count - количество чисел
 * @return Функция возвращает код ошибки
*/
int fill_file_with_rand(FILE* file, size_t count);

/**
 * @brief Функция выводит числа из бинарного файла на экран
 * @param FILE* file - файл
 * @return Функция возвращает код ошибки
*/
int output_numbers_from_file(FILE* file);

#endif
