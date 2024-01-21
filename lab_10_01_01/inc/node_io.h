#ifndef NODE_IO_H__

#define NODE_IO_H__

#define EPS 1e-6

#include "err_codes.h"
#include <stddef.h>
#include <math.h>

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

typedef int (*cmp_t)(const void*, const void*);

/**
 * @brief Функция выделяет память под новый узел (создает новый список с одним элементом)
 * @param void data - данные узла
 * @return Функция возвращает указатель на новый узел
*/
node_t *node_create(void *data, size_t data_size);

/**
 * @brief Функция освобождает память из под узла
 * @param node_t node - узел
 * @return Функция ничего не возвращает
*/
void node_free(node_t *node);

/**
 * @brief Функция сравнивает информацию по узлам типа int
 * @param const void *l - указатель на значение первого узла
 * @param const void *r - указатель на значение второго узла
 * @return Функция возвращает признак сравнения
*/
int node_cmp_int(const void *l, const void *r);

/**
 * @brief Функция сравнивает информацию по узлам типа double
 * @param const void *l - указатель на значение первого узла
 * @param const void *r - указатель на значение второго узла
 * @return Функция возвращает признак сравнения
*/
int node_cmp_double(const void *l, const void *r);

/**
 * @brief Функция сравнивает информацию по узлам типа "строка"
 * @param const void *l - указатель на значение первого узла
 * @param const void *r - указатель на значение второго узла
 * @return Функция возвращает признак сравнения
*/
int node_cmp_str(const void *l, const void *r);

#endif
