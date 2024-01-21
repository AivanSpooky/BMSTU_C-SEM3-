#include "film_t.h"
#include <string.h>
#include <ctype.h>

int read_film(FILE *file, film_t *film)
{
    char title[MAX_TITLE_LEN + 1];
    char name[MAX_NAME_LEN + 1];
    int year;

    char tmp[8];

    size_t len;

    if (!fgets(title, MAX_TITLE_LEN + 1, file))
    {
        return ERR_EMPTY;
    }
    len = strlen(title);
    //printf("%s - %zu\n", title, len);
    if (title[len - 1] == '\n')
        title[--len] = '\0';
    if (!len)
        return ERR_IO;
    if (len > MAX_TITLE_LEN - 1)
        return ERR_RANGE;
    if (allspace(title))
        return ERR_DATA;

    if (!fgets(name, MAX_NAME_LEN + 1, file))
    {
        return ERR_IO;
    }
    len = strlen(name);
    //printf("%s - %zu\n", name, len);
    if (name[len - 1] == '\n')
        name[--len] = '\0';
    if (!len)
        return ERR_IO;
    if (len > MAX_NAME_LEN - 1)
        return ERR_RANGE;
    if (allspace(name))
        return ERR_DATA;
    //(*readfields)++;

    if (fscanf(file, "%d", &year) != ARG_READ)
        return ERR_IO;
    if (year <= 0)
        return ERR_DATA;
    //(*readfields)++;
    fgets(tmp, sizeof(tmp), file);
    
    strcpy(film->title, title);
    strcpy(film->name, name);
    film->year = year;

    return OK;
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
