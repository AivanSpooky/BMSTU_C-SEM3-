#ifndef ARRAY_H__

#define ARRAY_H__

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define OK 0
#define ERR_ARGS 1

/**
 * @brief Функция возвращает максимальное значение типа int
 * @return Функция не принимает аргументов и возвращает максимальное значение типа int
*/
int get_max_int(void);

/**
 * @brief Функция проверяет, является ли число простым.
 * @param int n - число
 * @return Функция возвращает признак простоты числа
*/
bool is_prime(int n);

/**
 * @brief Функция заполняет массив простыми числами
 * @param int a - указатель на массив целых чисел
 * @param size_t size - кол-во элементов в массиве
 * @warning Память под массив должна выделять вызывающая сторона.
 * @return Функция возвращает код ошибки
*/
int fill_arr_with_primes(int *a, size_t size);

// Функция для 
/**
 * @brief Функция переписывает элементы из одного массива в другой, добавляя после каждого четного указанное число
 * @param int src - указатель на исходный массив целых чисел
 * @param int dst - указатель на получившийся массив целых чисел
 * @param size_t size - кол-во элементов в изначальном массиве
 * @param size_t dst_size - указатель на размер получившегося массива
 * @param int number - число, которое необходимо записать после каждого четного числа исходного массива
 * @warning Функция должна зараннее знать, сколько элементов получится в итоговом массиве. Память под получившийся массив выделяет вызывающая сторона
 * @return Функция возвращает код ошибки
*/
int rewrite_arr(int *src, int *dst, size_t size, size_t *dst_size, int number);

#endif