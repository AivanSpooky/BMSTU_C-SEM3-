#include "film_alloc.h"

void film_init_default(film_t *film)
{
    film->name = NULL;
    film->title = NULL;
    film->year = 0;
}

int film_init(film_t *film, const char *title, const char *name, int year)
{
    int rc = OK;
    char *tmp_title = NULL;
    char *tmp_name = NULL;
    tmp_title = strdup(title);
    if (!tmp_title)
    {
        rc = ERR_MEM;
    }
    if (rc == OK)
    {
        tmp_name = strdup(name);
        if (!tmp_name)
        {   
            free(tmp_title);
            tmp_title = NULL;
            rc = ERR_MEM;
        }
    }
    if (rc == OK)
    {
        // film_free(film);
        film->name = tmp_name;
        film->title = tmp_title;
        film->year = year;
    }
    return rc;
}

void film_free(film_t *film)
{
    //printf("|%s|\n", film->title);
    if (film->title != NULL)
        free(film->title);
    film->title = NULL;
    //printf("|%s|\n", film->name);
    if (film->name != NULL)
        free(film->name);
    film->name = NULL;
}

void film_arr_free(film_t *films, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        film_free(&films[i]);
    }
    free(films);
}
