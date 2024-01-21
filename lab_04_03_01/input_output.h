#ifndef __INPUT_OUTPUT_H__

#define __INPUT_OUTPUT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция ввода строки в буфер
 * @param [out] char *str - строка
 * @param [in] size_t str_size - размер строки
 * @return Функция возвращает код ошибки
*/
int get_line(char *str, size_t *str_size);

/**
 * @brief Функция вывода массива строк в обратном порядке (без учета слов, равных последнему)
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t *words_size - размер массива слов
 * @param size_t indexes[] - массив с индексами элементов, которые необходимо вывести
 * @return Функция ничего не возвращает
*/ 
int print_reverse(char words[][WORD_LEN], size_t words_size, size_t indexes[], char *str);

/**
 * @brief Функция вывода ошибки
 * @param int rc - код ошибки
 * @return Функция возвращает булево значение, показывающее, есть ли ошибка или нет.
*/ 
bool print_error(int rc);

#endif
