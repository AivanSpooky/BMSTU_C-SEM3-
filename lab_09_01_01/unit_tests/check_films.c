#include "check_films.h"

int ck_assert_bool_eq(bool p1, bool p2)
{
    return (p1 == p2) ? 0 : 1;
}

int ck_assert_film_eq(const film_t *film1, const film_t *film2)
{
    if (film_cmp_by_title(film1, film2) != UNIT_OK)
        return UNIT_ERR_TITLE_EQUAL;
    else if (film_cmp_by_name(film1, film2) != UNIT_OK)
        return UNIT_ERR_NAME_EQUAL;
    else if (film_cmp_by_year(film1, film2) != UNIT_OK)
        return UNIT_ERR_YEAR_EQUAL;
    return UNIT_OK;
}

int ck_assert_film_arr_eq(const film_t *f1, size_t n1, const film_t *f2, size_t n2)
{
    if (n1 != n2)
        return UNIT_ERR_N_EQUAL;
    int rc = UNIT_OK;
    for (size_t i = 0; i < n1; i++)
    {
        rc = ck_assert_film_eq(&f1[i], &f2[i]);
        if (rc != UNIT_OK)
            return rc;
    }
    return rc;
}
