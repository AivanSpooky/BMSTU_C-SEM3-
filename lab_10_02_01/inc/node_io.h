#ifndef NODE_IO_H__

#define NODE_IO_H__

#define EPS 1e-6

#include "err_codes.h"
#include <stddef.h>
#include <math.h>

typedef struct node
{
    int coefficient;
    int power;
    struct node *next;
} node_t;

/**
 * @brief Функция выделяет память под новый узел
 * @param int coefficient - коэффициент одночлена
 * @param int power - степень одночлена
 * @return Функция возвращает указатель на новый узел
*/
node_t *node_create(int coefficient, int power);

/**
 * @brief Функция освобождает память из под узла
 * @param node_t node - узел
 * @return Функция ничего не возвращает
*/
void node_free(node_t *node);

#endif
