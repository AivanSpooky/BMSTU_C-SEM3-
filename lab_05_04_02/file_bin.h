#ifndef __FILE_BIN_H__

#define __FILE_BIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#include "product_t.h"

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция находит в файле продукт, записанный на переданной позиции
 * @param FILE* file - файл
 * @param size_t pos - позиция в файле
 * @param product_t *product - продукт
 * @return Функция ничего не возвращает
*/
void get_product_by_pos(FILE *file, size_t pos, product_t *product);

/**
 * @brief Функция записывает продукт в файл по переданной позиции
 * @param FILE* file - файл
 * @param size_t pos - позиция в файле
 * @param product_t *product - продукт
 * @return Функция ничего не возвращает
*/
void put_product_to_pos(FILE *file, size_t pos, product_t product);

/**
 * @brief Функция добавляет новый продукт в файл
 * @param FILE* file - файл
 * @param size_t count - количество структур, записанных в файле
 * @return Функция возвращает код ошибки
*/
int add_product(FILE *file, size_t count);

#endif
