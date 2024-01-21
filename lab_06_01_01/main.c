#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <assert.h>

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
        if (strcmp(argv[2], TITLE) == OK && strlen(argv[3]) > MAX_TITLE_LEN)
            return ERR_ARGS;
        if (strcmp(argv[2], NAME) == OK && strlen(argv[3]) > MAX_NAME_LEN)
            return ERR_ARGS;
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
    film_t films[MAX_FILMS_COUNT];
    size_t n = 0;
    film_t film;
    cmp_t comparator;
    
    if (strcmp(argv[2], TITLE) == OK)
    {
        rc = read_films(file, films, MAX_FILMS_COUNT, &n, film_cmp_by_title);
        comparator = film_cmp_by_title;
        if (argc == 4)
            strcpy(film.title, argv[3]);
    }
    else if (strcmp(argv[2], NAME) == OK)
    {
        rc = read_films(file, films, MAX_FILMS_COUNT, &n, film_cmp_by_name);
        comparator = film_cmp_by_name;
        if (argc == 4)
            strcpy(film.name, argv[3]);
    }
    else if (strcmp(argv[2], YEAR) == OK)
    {
        rc = read_films(file, films, MAX_FILMS_COUNT, &n, film_cmp_by_year);
        comparator = film_cmp_by_year;
        if (argc == 4)
            film.year = strtol(argv[3], NULL, BASE);
    }
    else
        assert(0);
    //printf("%d\n", rc);
    fclose(file);
    if (rc != OK)
        return rc;
    if (argc == 3)
        print_films(films, n);
    else
    {
        
        bool found = true;
        found = binary_search(films, n, &film, comparator);

        if (found)
            print_film(stdout, &film);
        else
        {
            printf("Not found\n");
        }
    }

    return rc;
}
