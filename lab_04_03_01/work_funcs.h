#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция делит строку на слова по разделителям
 * @param const char *str - строка
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t *words_size - размер массива слов
 * @return Функция возвращает код ошибки
*/
int split_line(char *str, char words[][WORD_LEN], size_t *words_size);

/**
 * @brief Функция оставляет только первые вхождения каждой буквы
 * @param char *str - строка
 * @return Функция ничего не возвращает
*/
void make_set_letters(char *str);

/**
 * @brief Функция проверяет корректность слов в исходной строке (в соответствии с условием задачи)
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t words_size - размер массива слов
 * @param size_t indexes[ARR_LEN] - признак вывода каждого (по индексу) слова  (0 - выводим, 1 - не выводим)
 * @return Функция возвращает код ошибки
*/
int check_words(char words[][WORD_LEN], size_t words_size, size_t *indexes);

#endif
