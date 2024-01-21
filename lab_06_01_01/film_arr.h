#ifndef FILM_ARR_H__

#define FILM_ARR_H__

#include <stdio.h>
#include <stdbool.h>

#include "film_t.h"
#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция вставляет фильм в существующий массив фильмов так
 * @brief чтобы массив был упорядочен по указанному полю
 * @param film_t *films - массив фильмов
 * @param size_t *n - количество элементов в массиве фильмов
 * @param const film_t film - фильм, который необходимо добавить в массив
 * @param const char *field - поле, по которому фильмы будут упорядочены в массиве
 * @return Функция ничего не возвращает
*/
void insert_film(film_t *films, size_t n, const film_t film, cmp_t cmp);

/**
 * @brief Функция считает информацию о фильмах (film_t) из текстового файла
 * @brief и записывает их в массив фильмов так, чтобы они были упорядочены
 * @brief по указанному полю
 * @param FILE *file - файл
 * @param film_t *films - массив фильмов
 * @param size_t n_max - максимальный размер массива фильмов
 * @param size_t *n - количество элементов в массиве фильмов
 * @param const char *field - поле, по которому фильмы будут упорядочены в массиве
 * @return Функция возвращает код ошибки
*/
int read_films(FILE *file, film_t *films, size_t n_max, size_t *n, cmp_t cmp);

/**
 * @brief Функция спечатает информацию о фильмах,
 * @brief хранящихся в массиве
 * @param film_t *films - массив фильмов
 * @param size_t n - количество элементов в массиве фильмов
 * @return Функция ничего не возвращает
*/
void print_films(film_t *films, size_t n);

/**
 * @brief Функция находит в массиве фильмов нужный фильм по клюючу для
 * @brief заданного поля. Реализован на основе алгоритма двоичного поиска
 * @param film_t *films - массив фильмов
 * @param size_t n - количество элементов в массиве фильмов
 * @param const char *field - поле, по которому фильмы будут упорядочены в массиве
 * @param const char *key - ключ, по которому необходимо найти нужный фильм
 * @param const film_t *film - фильм, который необходимо найти в массиве
 * @return Функция возвращает булево значение, которое означает: смогли найти фильм по критериям?
*/
bool binary_search(film_t *films, size_t n, film_t *film, cmp_t cmp);

#endif
