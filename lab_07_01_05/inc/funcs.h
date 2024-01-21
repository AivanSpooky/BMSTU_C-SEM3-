#ifndef FUNCS_H__

#define FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "err_codes.h"

typedef int (*uni_cmp)(const void *l, const void *r);

/**
 * @brief Функция по фильтру помещает нужные элементы из первого массива во второй
 * @param const int *pb1 - указатель на нулевой элемент первого массива
 * @param const int *pe1 - указатель на за-последний элемент первого массива
 * @param const int **pb2 - указатель на нулевой элемент второго массива
 * @param const int **pe2 - указатель на за-последний элемент второго массива 
 * @return Функция возвращает код ошибки
*/
int key(const int *pb1, const int *pe1, int **pb2, int **pe2);

/**
 * @brief Функция сравнивает 2 элемента типа int
 * @param const void *l - левый int
 * @param const void *r - правый int
 * @return Функция возвращает признак сравнения
*/
int int_cmp(const void *l, const void *r);

int double_cmp(const void *l, const void *r);

int string_cmp(const void *l, const void *r);


/**
 * @brief Функция сортирует массив элементов
 * @param void *ptr - массив элементов
 * @param size_t cnt - количество элементов в массиве
 * @param size_t size - размер элемента в массиве
 * @param uni_cmp cmp - функция сравнения двух элементов
 * @return Функция ничего не возвращает
*/
void mysort(void *ptr, size_t cnt, size_t size, uni_cmp cmp);

#endif
