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
 * @param [out] size_t str_size - размер строки
 * @return Функция возвращает код ошибки
*/
int get_line(char *str, size_t *str_size);

/**
 * @brief Функция вывода массива
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t *words_size - размер массива слов
 * @return Функция ничего не возвращает
*/ 
void print(char words[][WORD_LEN], size_t words_size);

/**
 * @brief Функция вывода ошибки
 * @param int rc - код ошибки
 * @return Функция возвращает булево значение, показывающее, есть ли ошибка или нет.
*/ 
bool print_error(int rc);

#endif
