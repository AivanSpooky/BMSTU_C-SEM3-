#ifndef __WORK_FUNCS_H__

#define __WORK_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция делит строку на теоретически возможные числа (по словам) и ищет среди них те, что подходят по регулярному выражению [+-]?(\d+([.]\d*)?([eE][+-]?\d+)?|[.]\d+([eE][+-]?\d+)?)
 * @param char *str - строка
 * @param size_t str_size - размер строки
 * @return Функция возвращает код ошибки
*/
int find_num(char *str, size_t str_size);

/**
 * @brief Функция проверяет, является ли строка целым числом
 * @param char *str - строка
 * @return Функция возвращает признак (является ли строка целым числом)
*/
bool is_integer(char *str);

/**
 * @brief Функция проверяет, является ли строка целым числом (без знака)
 * @param char *str - строка
 * @return Функция возвращает признак (является ли строка целым числом без знака)
*/
bool is_integer_no_sign(char *str);

/**
 * @brief Функция проверяет, является ли строка целым числом или знаком
 * @param char *str - строка
 * @return Функция возвращает признак (является ли строка целым числом или знаком)
*/
bool is_integer_or_sign(char *str);

/**
 * @brief Функция проверяет, является ли строка числом с точкой
 * @param char *str - строка
 * @return Функция возвращает признак (является ли строка числом с точкой)
*/
bool is_real(char *str);

// 
/**
 * @brief Функция проверяет, является ли строка числом в экспоненциальном виде (буква e)
 * @param char *str - строка
 * @return Функция возвращает признак (является ли строка числом в экспоненциальном виде (c буквой e))
*/
bool is_exponent(char *str);

/**
 * @brief Функция проверяет, является ли строка числом в экспоненциальном виде (буква e) (по заданному рег.выр.)
 * @param char *str - строка
 * @return Функция возвращает признак, присутствует в строке данное рег.выр.
*/
bool is_regex_found(char *str);

#endif
