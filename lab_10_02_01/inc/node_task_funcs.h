#ifndef NODE_TASK_FUNCS_H__

#define NODE_TASK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include "err_codes.h"

#include "node_io.h"
#include "node_default_funcs.h"

#define MAX_WORD_LEN 3
#define KEY_VAL "val"
#define KEY_DDX "ddx"
#define KEY_SUM "sum"
#define KEY_DVD "dvd"

/**
 * @brief Функция считывает введенное слово из терминала и при возможности помещает в word
 * @param char *word - слово
 * @return Функция возвращает код ошибки
*/
int input_key_word(char *word);

/**
 * @brief Функция считает значение полинома для конкретного целого числа а
 * @param node_t head - голова списка
 * @return Функция возвращает результат
*/
int node_list_calc_val(node_t *head, int a);

/**
 * @brief Функция изменяет список с данными полинома после взятия производной от данного полинома
 * @param node_t head - голова списка
 * @return Функция ничего не возвращает
*/
void node_list_calc_ddx(node_t *head);

/**
 * @brief Функция формирует новый полином, суммируя poly1 и poly2
 * @param node_t *poly1 - указатель на голову первого списка
 * @param node_t *poly2 - указатель на голову второго списка
 * @return Функция возвращает голову нового списка
*/
node_t *node_list_add_lists(node_t *poly1, node_t *poly2);

/**
 * @brief Функция формирует полином с четными степенями и полином с нечетными степенями данного полинома
 * @param node_t *head - указатель на голову исходного полинома
 * @param node_t *even - указатель на голову первого четных степеней
 * @param node_t *odd - указатель на голову списка нечетных степеней
 * @return Функция ничего не возвращает
*/
void node_list_split_lists(node_t *head, node_t **even, node_t **odd);

#endif
