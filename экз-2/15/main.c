#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Строки/структуры и динамическое выделение памяти
Функции, возвращающие динамическую строку: strdup/strndup, getline, snprintf/asprintf.
strdup — нестандартная функция языка программирования Си, создающая копию указанной нуль-терминированной строки в куче (используя malloc)
и возвращающая указатель на неё. Чтобы освободить место, используемое созданной копией, необходимо вызвать free.
Функция появилась в BSD, включена в POSIX, но не является частью стандартов ANSI/ISO, хотя поддерживается почти всеми компиляторами.
Прототип описан в заголовочном файле string.h: 
char *strdup(const char *src); src — указатель на исходную строку.
char *strndup(const char *src, size_t size);
Функция getline предназначена для ввода данных из потока, например, для ввода данных из консольного окна.
Если формально описывать её функционал, то она извлекает данные из входного потока до строкового разделителя,
который не записывается в получившийся массив данных.
#include <stdio.h>
ssize_t getline(char **lineptr, size_t *n, FILE *stream); //POSIX
lineptr - либо NULL (и тогда в n - 0), либо указатель на буфер, выделенный с помощью malloc
(и тогда в n - размер буфера). Если буфера не хватает, он будет перевыделен.

int snprintf (char *s, size_t n, const char *format, ...);
Помещает форматную строку в буфер определённого размера, возвращая количество байтов, которые могли бы записаться в буфер.
int asprintf(char **strp, const char *fmt, ...); 
Выделяет в памяти строку, достаточную для размещения результата, включая символ окончания строки, и возвращает указатель на эту строку первым аргументом.

char *custom_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    if (new_str) {
        memcpy(new_str, str, len);
    }
    return new_str;
}

char *custom_strndup(const char *str, size_t n) {
    size_t len = strnlen(str, n);
    char *new_str = malloc(len + 1);
    if (new_str) {
        memcpy(new_str, str, len);
        new_str[len] = '\0';
    }
    return new_str;
}


int custom_snprintf(char *buffer, size_t buf_size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vsnprintf(buffer, buf_size, format, args);
    va_end(args);
    return result;
}


ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    if (!lineptr || !n) {
        return -1;
    }

    size_t bufsize = 128;
    char *buffer = (char *)malloc(bufsize);
    if (!buffer) {
        return -1;
    }

    size_t pos = 0;
    int c;
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (pos + 1 >= bufsize) {
            bufsize *= 2;
            char *new_buffer = (char *)realloc(buffer, bufsize);
            if (!new_buffer) {
                free(buffer);
                return -1;
            }
            buffer = new_buffer;
        }
        buffer[pos++] = c;
    }

    if (c == EOF && pos == 0) {
        free(buffer);
        return -1;
    }

    buffer[pos] = '\0';
    *lineptr = buffer;
    *n = bufsize;
    return pos;
}


Feature Test Macro.
"Feature test macros" позволяет программисту управлять определениями, которые выставляются системными заголовочными файлами при компиляции программы.
 
Для того, чтобы получить результат, перед включением любых заголовочных файлов должен быть определен Feature test macros.
Это можно сделать либо с помощью команды компиляции ("cc -DMACRO=значение"), либо путем определения макроса в исходном коде
перед включением любых заголовочных файлов. Требование о том, что макрос должен быть определен перед включением любого заголовочного файла,
существует, поскольку заголовочные файлы могут свободно включать друг друга. Таким образом, например, в следующих строках определение макроса
_GNU_SOURCE может не иметь никакого эффекта, так как заголовок <abc.h> сам по себе включает <xyz.h> (POSIX это явно разрешает):
 
    #include <abc.h>
    #define _POSIX_C_SOURCE 200809L  // с версии glibc 2.10
    #define _GNU_SOURCE // до версии glibc 2.10
    #include <xyz.h>
Некоторые Feature test macros полезны для создания портативных приложения, предотвращая появление нестандартных определений.
Другие макросы могут быть использованы для воздействия нестандартных определения, которые не раскрываются по умолчанию.

#endif

#ifdef OK // Функции

#endif


int main(void)
{
    return OK;
}