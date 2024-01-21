#include "check_mtr.h"

int assert_mtr_eq(const mtr_t mtr1, const mtr_t mtr2)
{
    if (mtr1.n != mtr2.n)
    {
        return UNIT_ERR_ROW_EQUAL;
    }
    if (mtr1.m != mtr2.m)
    {
        return UNIT_ERR_COL_EQUAL;
    }
    for (size_t i = 0; i < mtr1.n; i++)
        for (size_t j = 0; j < mtr1.m; j++)
        {
            if (fabs(mtr1.ptr[i][j] - mtr2.ptr[i][j]) > EPS)
            {
                return UNIT_ERR_NOT_EQUAL;
            }
        }
    return UNIT_OK;
}

void fill_mtr(mtr_t *mtr, double *values)
{
    for (size_t i = 0; i < mtr->n; i++)
    {
        for (size_t j = 0; j < mtr->m; j++)
        {
            //printf("%lf\n", values[i * mtr->m + j]);
            mtr->ptr[i][j] = values[i * mtr->m + j];
        }
    }
}
