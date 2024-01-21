#include "film_t.h"
#include <string.h>
#include <ctype.h>
#include "film_alloc.h"

int read_film(FILE *file, film_t *film)
{
    char *title = NULL;
    char *name = NULL;
    int year;
    size_t buf_size = 0;

    ssize_t read;
    film_init_default(film);

    //char tmp[2];

    // size_t len;
    int rc = OK;
    read = getline(&title, &buf_size, file);
    //printf("title - %zu\n", read);
    //printf("%s - %zu\n", title, read);
    if (read == STRING_IO_ERR)
    {
        rc = ERR_EMPTY;
    }
    else if (read == 1)
    {
        rc = ERR_DATA;
    }
    if (rc == OK)
    {
        if (title[read - 1] == '\n')
        {
            title[read - 1] = '\0';
        }

        buf_size = 0;
        read = getline(&name, &buf_size, file);
        //printf("name - %zu\n", read);
        if (read == STRING_IO_ERR)
        {
            rc = ERR_DATA;
        }
        else if (read == 1)
        {
            rc = ERR_DATA;
        }
        if (rc == OK)
        {
            if (name[read - 1] == '\n')
                name[read - 1] = '\0';

            if (fscanf(file, "%d\n", &year) != ARG_READ)
                rc = ERR_IO;
            else if (year <= 0)
                rc = ERR_DATA;
            //(*readfields)++;
            if (rc == OK)
            {
                //fgets(tmp, sizeof(tmp), file);
                film_init(film, title, name, year);
            }
        }
        free(name);
    }
    free(title);

    return rc;
}

bool allspace(char *s)
{
    bool flag = true;
    while (flag && *s)
    {
        if (!isspace(*s))
            flag = false;
        s++;
    }
    return flag;
}

void print_film(FILE *file, const film_t *film)
{
    fprintf(file, "%s\n%s\n%u\n", film->title, film->name, film->year);
}

int film_cmp_by_title(const film_t *fl, const film_t *fr)
{
    return strcmp(fl->title, fr->title);
}

int film_cmp_by_name(const film_t *fl, const film_t *fr)
{
    return strcmp(fl->name, fr->name);
}

int film_cmp_by_year(const film_t *fl, const film_t *fr)
{
    return fl->year - fr->year;
}

// int uni_cmp(const void *l, const void *r)
// {
//     const int *pl = l;
//     const int *pr = r;
//     return *pl - *pr;
// }
