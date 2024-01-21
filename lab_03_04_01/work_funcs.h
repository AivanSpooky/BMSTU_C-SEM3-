#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"

// Функция меняет местами элементы строк, заключенных внутри главной и побочной диагоналях
// int a[][M]; - матрица;
// size_t a_n; - кол-во строк;
// Функция ничего не возвращает
void swap(int a[][M], const size_t a_n);

#endif
