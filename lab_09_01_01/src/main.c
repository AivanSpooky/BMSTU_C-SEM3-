#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <assert.h>

#include "film_alloc.h"
#include "film_arr.h"

#include "consts.h"
#include "err_codes.h"

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4 || (strcmp(argv[2], TITLE) != OK && 
        strcmp(argv[2], NAME) != OK && strcmp(argv[2], YEAR) != OK))
    {
        return ERR_ARGS;
    }
    if (argc == 4)
    {
        if ((strcmp(argv[2], YEAR) == OK && strspn(argv[3], DIGITS) != strlen(argv[3]))
            || atoi(argv[3]) < 0)
            return ERR_ARGS;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return ERR_IO;
    }
    
    int rc = OK;
    film_t *films = NULL;
    size_t n = 0;
    film_t film;
    film_init_default(&film);
    cmp_t comparator;
    bool films_read = false;
    
    if (strcmp(argv[2], TITLE) == OK)
    {
        rc = find_films_cnt(file, &n);
        if (rc == OK)
        {
            films_read = true;
            rewind(file);

            films = calloc(n, sizeof(film_t));
            if (!films)
                rc = ERR_MEM;
            if (rc == OK)
            {
                rc = read_films(file, films, &n, film_cmp_by_title);
                comparator = film_cmp_by_title;
                if (argc == 4)
                {
                    film.title = argv[3];
                    if (!film.title)
                        rc = ERR_MEM;
                }
            }
        }
    }
    else if (strcmp(argv[2], NAME) == OK)
    {
        rc = find_films_cnt(file, &n);
        if (rc == OK)
        {
            films_read = true;
            rewind(file);

            films = calloc(n, sizeof(film_t));
            if (!films)
                rc = ERR_MEM;
            if (rc == OK)
            {
                rc = read_films(file, films, &n, film_cmp_by_name);
                comparator = film_cmp_by_name;
                if (argc == 4)
                {
                    film.name = argv[3];
                    if (!film.name)
                        rc = ERR_MEM;
                }
            }
        }
    }
    else if (strcmp(argv[2], YEAR) == OK)
    {
        rc = find_films_cnt(file, &n);
        if (rc == OK)
        {
            films_read = true;
            rewind(file);

            films = calloc(n, sizeof(film_t));
            if (!films)
                rc = ERR_MEM;
            if (rc == OK)
            {
                rc = read_films(file, films, &n, film_cmp_by_year);
                comparator = film_cmp_by_year;
                if (argc == 4)
                    film.year = strtol(argv[3], NULL, BASE);
            }
        }
    }
    else
        assert(0);
    //printf("%d\n", rc);
    fclose(file);

    if (rc == OK)
    {
        if (argc == 3)
            print_films(films, n);
        else
        {
            //print_films(films, n);
            bool found = true;
            found = binary_search(films, n, &film, comparator);

            if (found)
            {
                print_film(stdout, &film);
                film_free(&film);
            }
            else
            {
                printf("Not found\n");
            }
        }
    }
    if (films_read)
        film_arr_free(films, n);
    if (rc != OK && argc != 4)
        film_free(&film);

    return rc;
}
