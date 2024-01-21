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
 * @param size_t str_size - размер строки
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t *words_size - размер массива слов
 * @return Функция возвращает код ошибки
*/
int split_line(const char *str, size_t str_size, char words[][WORD_LEN], size_t *words_size);

// /**
//  * @brief Функция удаляет слово из массива слов
//  * @param char words[WORD_LEN] - массив слов длинной WORD_LEN каждое
//  * @param size_t *words_size - размер массива слов
//  * @param size_t index - индекс удаляемого слова
//  * @return Функция ничего не возвращает
// */
// void delete_word(char words[][WORD_LEN], size_t *words_size, size_t index);

/**
 * @brief Функция считает количество вхождений слова word в массив слов words, начиная с элемента под номером ind
 * @param char *word - слово
 * @param char words[][WORD_LEN] - массив слов
 * @param size_t words_size - длина массива слов
 * @param size_t ind - начальная позиция
 * @return Функция возвращает количество вхождений
*/
size_t cnt_word_in_array(char *word, char words[][WORD_LEN], size_t words_size, size_t ind);

/**
 * @brief Функция формирует новый массив слов uwords, состоящий из уникальных слов массива words
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t *words_size - размер массива слов
 * @param char uwords[][WORD_LEN] - новый массив слов
 * @param size_t *uwords_size - размер нового массива слов
 * @return Функция ничего не возвращает
*/
void make_array_equal(char words[][WORD_LEN], size_t words_size, char uwords[][WORD_LEN], size_t *uwords_size);

/**
 * @brief Функция сортирует слова в лексикографическом порядке (опорный алгоритм - сортировка выбором)
 * @param char words[][WORD_LEN] - массив слов длинной WORD_LEN каждое
 * @param size_t *words_size - размер массива слов
 * @return Функция ничего не возвращает
*/
void sort(char words[][WORD_LEN], size_t words_size);

#endif
