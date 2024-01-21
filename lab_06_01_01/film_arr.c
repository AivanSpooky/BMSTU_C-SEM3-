#include "film_arr.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
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

int read_films(FILE *file, film_t *films, size_t n_max, size_t *n, cmp_t cmp)
{
    film_t film;
    int rc = OK;
    (*n) = 0;
    //size_t readfields = 0;
    while (rc == OK)
    {
        rc = read_film(file, &film);
        if (rc != OK)
            break;
        if ((*n) < n_max)
        {
            insert_film(films, (*n), film, cmp);
        }
        else
        {
            rc = ERR_OVERFLOW;
            break;
        }
        (*n)++;
    }
    // Проверка на наличие \n в конце
    char tmp[2];
    fgets(tmp, sizeof(tmp), file);
    if (rc != OK && rc != ERR_EMPTY)
        return rc;
    if ((*n) <= 0)
    {
        rc = ERR_RANGE;
        return rc;
    }
    if (feof(file) || tmp[0] == '\n')
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
        //printf("l - %zu; mid - %zu, r - %zu\n", l, mid, r);
        int res_cmp = 0;

        // switch (kt)
        // {
        //     case NTITLE:
        //         strcpy(film->title, key);
        //         res_cmp = cmp(&films[mid], film);
        //         break;
        //     case NNAME:
        //         strcpy(film->name, key);
        //         res_cmp = cmp(&films[mid], film);
        //         break;
        //     case NYEAR:
                
        //         if (strlen(end) != OK)
        //             assert(OK);
        res_cmp = cmp(&films[mid], film);
        //         break;
        //     default:
        //         assert(OK);
        //         break;
        // }
        if (res_cmp == 0)
        {
            (*film) = films[mid];
            return true;
        }
        else if (res_cmp < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return false;
}

