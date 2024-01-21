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
 * @brief Функция проверяет, одинаковы ли списки
 * @param const node_t l - первый список
 * @param const node_t r - второй список
 * @param cmp_t comparator - компаратор для сравнения data
 * @return Функция возвращает признак сравнения
*/
int ck_assert_node_list_eq(const node_t *l, const node_t *r);

/**
 * @brief Функция заполняет список слагаемыми полинома
 * @param node_t *head - голова списка
 * @param int coef - массив коэффициентов слагаемых
 * @param int pow - массив степеней слагаемых
 * @param size_t size - размер обоих массивов
 * @return Функция возвращает признак сравнения
*/
void node_list_create_from_array(node_t **head, int *coef, int *pow, size_t size);

#endif