#ifndef MY_SNPRINTF_IMPL_H__

#define MY_SNPRINTF_IMPL_H__

#include <stddef.h>

/**
 * @brief Функция преобразует в строку число типа long long int (в 10-ой системе счисления) без использования стандартных функций
 * @param long long int num - число
 * @param char *buffer - буфер
 * @return Функция ничего не возвращает
*/
void long_long_to_string(long long int num, char *buffer);

/**
 * @brief Функция копирует символы строки source в буфер buffer, учитывая ограничение в size
 * @param char *source - строка
 * @param char *buffer - буфер
 * @param int written - указатель на количество символов, записанных в буфер
 * @param int size - размер буфера
 * @return Функция ничего не возвращает
*/
void copy_string_to_buffer(const char *source, char *buffer, int *written, int size);

/**
 * @brief Функция является собственной реализацией библиотечной функции snprintf для спецификаторов %s, %lld 
 * @param char *str - строка, куда будет сохранена результирующая строка
 * @param size_t size - максимальное количество символов, которое может быть записано в результирующую строку, включая завершающий нуль
 * @param format - форматная строка
 * @param ... - дополнительные аргументы, каждый из которых подставляется в форматную строку
 * @return Функция возвращает отрицательное число при возникновении ошибки или общее количество записанных символов при отсутствии ошибок
*/
int my_snprintf(char *str, size_t size, const char *format, ...);

#endif