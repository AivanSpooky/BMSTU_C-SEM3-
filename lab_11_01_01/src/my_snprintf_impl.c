#include "my_snprintf_impl.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include <inttypes.h>
#include <math.h>

#define END '\0'
#define CONVERTER '0'

#define ERR_SIZE -1
#define ERR_BUF_OVERFLOW -2 

#define BASE 10
// INT64_MAXLEN - максимальное количество символов в строков представлении lld
// + 2 (один для цифры, другой для завершающего нуля)
// под знак информация не хранится в макросе
#define INT64_MAXLEN ((int)log10((double)INT64_MAX) + 2)

void long_long_to_string(long long int num, char *buffer)
{
    // Флаг, обозначающий, является ли число минимально возможным INT64 (INT64_MIN)
    bool is_min = false;
    // Если число отрицательное - записываем его знак, а само число инвертируем (берем его модуль)
    if (num < 0)
    {
        *buffer++ = '-';
        // Если число равно INT64_MIN - флаг равен true, работаем с числом INT64_MAX, которое по модулю меньше исходного на 1
        if (num == INT64_MIN)
            is_min = true;
        num = (!is_min) ? -num : INT64_MAX;
    }
    // Заводим переменную для временной записи строкового представления числа (используем константу INT64_MAXLEN в качестве максимального размера)
    char temp[INT64_MAXLEN];
    char *p = temp;
    // Пока не обработали все цифры числа - обрабатываем их
    do
    {
        // Обработка частного случая, когда num == INT64_MIN
        if (is_min)
        {
            is_min = false;
            // Записываем строковое представление последней цифры INT64_MIN
            *p++ = (char)((INT64_MAX % 10) + 1 + CONVERTER);
        }
        // Записываем строковое представление цифры
        else
            *p++ = (char)(num % BASE + CONVERTER);
        // Этим действием мы осуществляем переход к следующей цифре числа
        num /= BASE;
    } while (num != 0);
    // Получаем строковое представление числа в обратном порядке - записываем в конечный буфер в прямом порядке 
    while (p != temp)
        *buffer++ = *--p;

    *buffer = END;
}

void copy_string_to_buffer(const char *source, char *buffer, int *written, int size)
{
    // Пока не дошли до завершающего нуль-символа - считываем символы из строки и записываем в буфер, если соблюдается соотношение размеров (смотреть if)
    while (*source != END)
    {
        if (*written < size - 1 && buffer != NULL)
            buffer[*written] = *source;
        (*written)++;
        source++;
    }
}

int my_snprintf(char *str, size_t size, const char *format, ...)
{
    // Если переданный размер буфера меньше 0 - возвращаем -1.
    if ((int)size < 0)
        return ERR_SIZE;
    // Если формат - NULL-строка, заменяем на стандартное представление формата NULL
    if (format == NULL)
        format = "(null)";
    // Считываем переданные аргументы
    va_list args;
    va_start(args, format);
    // Заводим необходимые переменные
    int written = 0; // количество символов, записанных в строку
    int i = 0; // индекс текущего символа в format
    // Проходимся поиндексно по форматной строке, пока не нашли зарешающий нуль-символ
    // Увеличиваем i на то количество, которое обработалось во время очередного действия в форматной строке
    while (format[i] != END)
    {
        // Вводим переменную, которая определяет, в каком случае выводить символ %, а в каком случае пропустить (если в форматной строке встретилось "%%")
        bool single_percent = (size - written + 1 > 0) && (str != NULL);
        if (format[i] == '%' && format[i + 1] == '%')
        {
            if (single_percent && written < (int)size - 1 && str != NULL)
                str[written] = '%';
            written++;
            i += 1;
        }
        // Встретили спецификатор %s - обрабатываем строку
        else if (format[i] == '%' && format[i + 1] == 's')
        {
            // Получаем строку из аргументов, копируем в буфер, увеличиваем индекс на 2 (%s)
            char *s = va_arg(args, char *);
            copy_string_to_buffer(s, str, &written, (int)size);
            i += 2;
        }
        // Встретили спецификатор %lld - обрабатываем INT64
        else if (format[i] == '%' && format[i + 1] == 'l' && format[i + 2] == 'l' && format[i + 3] == 'd')
        {
            // Получаем число из аргументов, преобразовываем его в строку, копируем в буфер, увеличиваем индекс на 4 (%lld)
            long long int num = va_arg(args, long long int);
            char num_s[INT64_MAXLEN];
            long_long_to_string(num, num_s);
            char *s = num_s;
            copy_string_to_buffer(s, str, &written, (int)size);
            i += 4;
        }
        // Нашли не предусмотренный функцией спецификатор - просто пропускаем.
        else if (format[i] == '%' && format[i + 1] != '\0')
        {
            i++;
        }
        // Иначе просто обрабатываем обычные символы
        else
        {
            if (written < (int)size - 1 && str != NULL)
            {
                str[written] = format[i];
            }
            written++;
            i++;
        }
    }

    if (str != NULL)
    {
        if (written < (int)size)
            str[written] = END; // добавляем завершающий нуль-символ
        else
            str[size - 1] = END; // обрезаем строку, если она не помещается в буфер
    }

    va_end(args);
    return written;
}