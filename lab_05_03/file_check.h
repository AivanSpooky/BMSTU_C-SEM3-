#ifndef __FILE_CHECK_H__

#define __FILE_CHECK_H__

#include <stdio.h>

#include "err_codes.h"
#include "consts.h"

/**
 * @brief Функция проверяет файл на корректность (по размеру)
 * @param FILE* file - файл
 * @return Функция возвращает код ошибки
*/
int file_size_check(FILE *file);

#endif
