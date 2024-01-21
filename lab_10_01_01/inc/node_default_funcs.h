#ifndef NODE_DEFAULT_FUNCS_H__

#define NODE_DEFAULT_FUNCS_H__

#define _POSIX_C_SOURCE 200809L

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
 * @param void *data - указатель на данные, которые необходимо добавить в список
 * @param size_t data_size - размер data
 * @return Функция ничего не возвращает
*/
void node_list_push(node_t **head, void *data, size_t data_size);

/**
 * @brief Функция читатет данные из файла
 * @param FILE file - файл, из которого необходимо считать данные
 * @param read_data_t read_func - функция чтения данных определенного типа
 * @warning В случае пустого ввода (файла) функция возвращает NULL-голову
 * @warning В функции предполагается корректный размер данных (int, double, str)
 * @warning Если функция чтения (read_func), читающая тип type, получила на вход файл, который содержит данные посторонних типов, то функция вернет NULL-голову
 * @return Функция ничего не возвращает
*/
node_t *node_list_read_from_file(FILE *file, read_data_t read_func);

/**
 * @brief Функция выводит информацию из списка на экран
 * @param node_t *head - указатель на голову списка
 * @param print_data_t print_func - функция вывода информации конкретного типа данных
 * @return Функция ничего не возвращает
*/
void node_print_data(const node_t *head, print_data_t print_func);

void *node_read_int(FILE *file);
// int-вывод
void node_print_int(const node_t *head);

void *node_read_double(FILE *file);
// double-вывод
void node_print_double(const node_t *head);

void *node_read_str(FILE *file);
// str-вывод
void node_print_str(const node_t *head);

#endif
