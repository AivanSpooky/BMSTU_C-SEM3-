#ifndef NODE_DEFAULT_FUNCS_H__

#define NODE_DEFAULT_FUNCS_H__

#include <stdio.h>
#include "err_codes.h"

#include "node_io.h"

typedef void *(*read_data_t)(FILE *);
typedef void (*print_data_t)(const node_t *);

/**
 * @brief Функция полностью очищает память из под списка
 * @param node_t *head - голова списка
 * @return Функция ничего не возвращает
*/
void node_list_free(node_t **head);

/**
 * @brief Функция проверяет, является ли список пустым
 * @param node_t head - голова списка
 * @return Функция возвращает признак пустоты списка
*/
int node_list_is_empty(node_t *head);

/**
 * @brief Функция добавляет новый элемент в конец списка
 * @param node_t *head - голова списка
 * @param int coefficient - коэффициент одночлена
 * @param int power - степень одночлена
 * @return Функция ничего не возвращает
*/
void node_list_push(node_t **head, int coefficient, int power);

/**
 * @brief Функция удаляет последний элемент из списка
 * @param node_t *head - голова списка
 * @return Функция ничего не возвращает
*/
void node_list_pop_last(node_t **head);

/**
 * @brief Функция удаляет узел из списка, который следует за prev
 * @param node_t *prev - указатель на узел
 * @return Функция ничего не возвращает
*/
void node_list_pop_after(node_t *prev);

/**
 * @brief Функция позволяет ввести полином с терминала
 * @return Функция возвращает указатель на голову списка введенного полинома
*/
node_t *node_list_input();

/**
 * @brief Функция выводит полином, представленный в виде списка согласно формату вывода из задания
 * @param node_t head - голова списка
 * @return Функция ничего не возвращает
*/
void node_list_print(const node_t *head);

#endif
