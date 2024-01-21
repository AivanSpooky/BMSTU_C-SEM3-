#ifndef __SORT_H__

#define __SORT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_check.h"

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция сортирует числа в бинарном файле (в качестве алгоритма используется сортировка выбором)
 * @param FILE *file - файл
 * @return Функция возвращает код ошибки
*/
int selection_sort_numbers_in_file(FILE* file);

/**
 * @brief Функция находит в бинарном файле число по указанной позиции
 * @param FILE *file - файл
 * @param size_t pos - позиция в файле
 * @return Функция возвращает найденное число
*/
number_t get_number_by_pos(FILE* file, size_t pos);

/**
 * @brief Функция записывает в бинарный файл переданное число на переданную позицию
 * @param FILE *file - файл
 * @param number_t num - число, которое необходимо записать в файл
 * @param size_t pos - позиция в файле
 * @return Функция возвращает код ошибки
*/
int put_number_by_pos(FILE* file, number_t num, size_t pos);



#endif
