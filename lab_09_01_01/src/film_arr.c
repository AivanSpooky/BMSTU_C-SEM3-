#include "film_arr.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int check_if_empty(size_t n, int rc)
{
    return ((n) <= 0) ? ERR_RANGE : rc;
}

//
size_t find_pos(film_t *films, size_t n, const film_t film, cmp_t cmp)
{
    size_t pos = 0;
    while (pos < n)
    {
        if (cmp(&films[pos], &film) > 0)
        {
            break;
        }
        pos++;
    }
    return pos;
}

void insert_to_pos(film_t *films, size_t n, const film_t film, size_t pos)
{
    size_t new_n = n;
    while (new_n > pos)
    {
        films[new_n] = films[new_n - 1];
        new_n--;
    }
    films[pos] = film;
}

void insert_film(film_t *films, size_t n, const film_t film, cmp_t cmp)
{
    size_t pos = find_pos(films, n, film, cmp);
    insert_to_pos(films, n, film, pos);
}

int find_films_cnt(FILE *file, size_t *n)
{
    int rc = OK;
    film_t film;
    film_init_default(&film);

    while (rc == OK)
    {
        rc = read_film(file, &film);
        film_free(&film);
        if (rc == OK)
            (*n)++;
    }
    char tmp[2];
    fgets(tmp, sizeof(tmp), file);
    rc = check_if_empty(*n, rc);
    if ((feof(file) || tmp[0] == '\n') && rc != ERR_RANGE && rc == ERR_EMPTY)
        rc = OK;
    return rc;
}

int read_films(FILE *file, film_t *films, size_t *n, cmp_t cmp)
{
    film_t film;
    film_init_default(&film);
    int rc = OK;
    *n = 0;
    //size_t readfields = 0;
    while (rc == OK)
    {
        rc = read_film(file, &film);
        if (rc == OK)
        {
            insert_film(films, (*n), film, cmp);
            (*n)++;
        }
    }
    // Проверка на наличие \n в конце
    char tmp[2];
    fgets(tmp, sizeof(tmp), file);
    assert(&film != NULL);
    rc = check_if_empty(*n, rc);
    if ((feof(file) || tmp[0] == '\n') && rc != ERR_RANGE && rc == ERR_EMPTY)
        rc = OK;
    return rc;
}

void print_films(film_t *films, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        print_film(stdout, &films[i]);
    }
}

bool binary_search(film_t *films, size_t n, film_t *film, cmp_t cmp)
{
    // Для границ выбрал тип size_t, так как если мы хотим найти (допустим год, меньший,
    // чем первый год в массиве), то граница r приняла бы отрицательное значение, а не
    // большое положительное, иначе цикл не завершится.
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        int res_cmp = 0;
        res_cmp = cmp(&films[mid], film);

        if (res_cmp == 0)
        {
            film_init(film, films[mid].title, films[mid].name, films[mid].year);
            return true;
        }
        else if (res_cmp < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return false;
}

