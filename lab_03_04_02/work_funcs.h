#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consts.h"
#include "err_codes.h"

// Функция находит под побочной диагональю наибольший элемент, оканчивающийся на 5
// int a[][M]; - матрица;
// size_t a_n; - кол-во строк;
// int *number - искомое число
// Функция возвращает код ошибки

//
// Забыли в конце поставить точку с запятой. Не могу понять, как такое у Вас получилось?
// reply: - торопился)))
//
int find_num(int a[][M], size_t a_n, int *number);

#endif
