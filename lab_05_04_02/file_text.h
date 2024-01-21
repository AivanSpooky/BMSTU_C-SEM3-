#ifndef __FILE_TEXT_H__

#define __FILE_TEXT_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "product_t.h"

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция считает количетсво продуктов (product_t) в текстовом файле, 
 * @brief название которых оканчиваются на переданную подстроку
 * @param FILE *file - файл
 * @param size_t *n - количество продуктов
 * @param char *substr - подстрока
 * @return Функция ничего не возвращает
*/
void get_lines_cnt(FILE *file, size_t *n);

/**
 * @brief Функция считывает строку из файла и помещает её в передаваемый буфер со своей длиной
 * @param FILE *file - файл
 * @param char *line - буфер
 * @param size_t len - длина буфера
 * @return Функция возвращает код ошибки
*/
int get_line_to_data(FILE *file, char *line, size_t len);

/**
 * @brief Функция заполняет массив продуктов, читая продукты из текстового файла
 * @param FILE *file - файл
 * @param product_t *products - массив продуктов
 * @param size_t cnt - количество продуктов
 * @param char *substr - подстрока
 * @return Функция возвращает код ошибки
*/
int fill_parray(FILE *file, product_t *products, size_t *cnt);

/**
 * @brief Функция выводит на экран все продукты из массива продуктов, оканчивающихся на подстроку
 * @param product_t *products - массив продуктов
 * @param size_t count - количество продуктов
 * @param char *substr - подстрока
 * @return Функция возвращает код ошибки
*/
int print_products(product_t *products, size_t count, char *substr);

#endif
