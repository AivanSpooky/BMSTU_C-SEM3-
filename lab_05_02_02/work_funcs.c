#include "work_funcs.h"

int calc_avg(FILE *f, double *avg, size_t *n)
{
    double num;
    double sum = 0;
    (*n) = 0;
    bool entered = false;
    while (fscanf(f, "%lf", &num) == ANALYZE_NUM)
    {
        entered = true;
        sum += num;
        (*n)++;
    }
    if (entered && n != 0)
        (*avg) = sum / (*n);
    else
        return ERR_EMPTY;
    return OK;
}

int calc_s_sq(FILE *f, double avg, size_t n, double *s_sq)
{
    size_t tmp_n = 0;
    double num;
    double sum = 0;
    bool entered = false;
    while (fscanf(f, "%lf", &num) == ANALYZE_NUM)
    {
        entered = true;
        sum += (num - avg) * (num - avg);
        tmp_n++;
    }
    if (entered && n > 1 && tmp_n == n)
    {
        (*s_sq) = sum / n;
    }
    else
        return ERR_WRONG_ARGS;
    return OK;
}
