#ifndef FILM_T_H__

#define FILM_T_H__

#include <stdio.h>
#include <stdbool.h>

#include "consts.h"
#include "err_codes.h"

// Структура фильма
typedef struct
{
    char title[MAX_TITLE_LEN];
    char name[MAX_NAME_LEN];
    int year;
} film_t;

typedef int (*cmp_t)(const film_t *l, const film_t *r);

/**
 * @brief Функция считает информацию об одном фильме (film_t) из текстового файла
 * @param FILE *file - файл
 * @param film_t *film - структура считываемого фильма
 * @return Функция возвращает код ошибки
*/
int read_film(FILE *file, film_t *film);

/**
 * @brief Функция выводит информацию об одном фильме (film_t)
 * @param FILE *file - поток, в который будет выведена информация
 * @param const film_t *film - фильм
 * @return Функция ничего не возвращает
*/
void print_film(FILE *file, const film_t *film);

/**
 * @brief Функция проверяет, является ли строка пробельными символами
 * @param char *s - строка
 * @param const film_t *film - фильм
 * @return Функция возвращает признак
*/
bool allspace(char *s);

/**
 * @brief Функция сравнивает названия двух фильмов и выводит значение
 * @brief по принципу работы функции strcmp
 * @param const film_t *fl - первый фильм
 * @param const film_t *fr - второй фильм
 * @return Функция возвращает значения аналогично функции strcmp
*/
int film_cmp_by_title(const film_t *fl, const film_t *fr);

/**
 * @brief Функция сравнивает имена авторов двух фильмов и выводит
 * @brief значение по принципу работы функции strcmp
 * @param const film_t *fl - первый фильм
 * @param const film_t *fr - второй фильм
 * @return Функция возвращает значения аналогично функции strcmp
*/
int film_cmp_by_name(const film_t *fl, const film_t *fr);

/**
 * @brief Функция сравнивает дату выпуска двух фильмов и выводит
 * @brief значение по принципу работы функции strcmp
 * @param const film_t *fl - первый фильм
 * @param const film_t *fr - второй фильм
 * @return Функция возвращает значения аналогично функции strcmp
*/
int film_cmp_by_year(const film_t *fl, const film_t *fr);

// int title_cmp(const film_t *fl, const film_t *fr);

#endif
