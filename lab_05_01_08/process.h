#ifndef __PROCESS_H__

#define __PROCESS_H__

#include <stdio.h>

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция определяет наименьшее расстояние между двумя локальными максимумами
 * @param FILE *f - файл с целыми числами
 * @param int *r - расстояние между двумя локальными максимумами
 * @return Функция возвращает код ошибки
*/
int process(FILE *f, int *r);

#endif
