#ifndef FILM_ALLOC_H__

#define FILM_ALLOC_H__

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

#include "film_t.h"
#include "consts.h"
#include "err_codes.h"
#include <string.h>

/**
 * @brief Функция заполняет поля фильма значениями по умолчанию
 * @param film_t film - фильм
 * @return Функция ничего не возвращает
*/
void film_init_default(film_t *film);

/**
 * @brief Функция заполняет поля фильма значениями, указанными в аргументах
 * @param film_t film - фильм
 * @param const char title - название фильма
 * @param const char name - имя автора
 * @param int year - год выпуска
 * @return Функция ничего возвращает код ошибки
*/
int film_init(film_t *film, const char *title, const char *name, int year);

/**
 * @brief Функция освобождает память из под одного фильма
 * @param film_t film - фильм
 * @return Функция ничего возвращает код ошибки
*/
void film_free(film_t *film);

/**
 * @brief Функция освобождает память из под массива фильмов
 * @param film_t films - массив фильмов
 * @param size_t n - количество фильмов в массиве
 * @return Функция ничего возвращает код ошибки
*/
void film_arr_free(film_t *films, size_t n);

#endif
