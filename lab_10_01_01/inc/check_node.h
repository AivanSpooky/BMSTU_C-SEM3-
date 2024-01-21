#ifndef CHECK_NODE_H__

#define CHECK_NODE_H__

#include <check.h>
#include "node_io.h"
#include "node_default_funcs.h"

#define UNIT_OK 0
#define UNIT_ERR 1

#define UNIT_ERR_DATA_NOT_EQUAL 1
#define UNIT_ERR_LENGHT_NOT_EQUAL 2

/**
 * @brief Функция заполняет список по значениям из массива
 * @param node_t head - голова списка
 * @param void arr - массив значений
 * @param size_t size - размер массива
 * @return Функция 
*/
void node_list_create_from_array(node_t **head, void *arr, size_t size, size_t data_size);

/**
 * @brief Функция проверяет, одинаковы ли списки
 * @param const node_t l - первый список
 * @param const node_t r - второй список
 * @param cmp_t comparator - компаратор для сравнения data
 * @return Функция возвращает признак сравнения
*/
int ck_assert_node_list_eq(const node_t *l, const node_t *r, cmp_t comparator);

#endif