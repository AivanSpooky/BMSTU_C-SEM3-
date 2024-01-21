#ifndef __INPUT_OUTPUT_H__

#define __INPUT_OUTPUT_H__

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция ввода строки в буфер
 * @param [out] char *str - строка
 * @param [in] size_t str_size - размер строки
 * @return Функция возвращает код ошибки
*/
int get_line(char *str, size_t *str_size);

#endif
