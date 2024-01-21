#include "mtr_io.h"

int matrix_check(const mtr_t *mtr)
{
    if (mtr == NULL || mtr->ptr == NULL)
        return ERR_EMPTY;

    for (size_t i = 0; i < mtr->n; i++)
    {
        if (mtr->ptr[i] == NULL)
            return ERR_CORRUPTED_DATA;

        for (size_t j = 0; j < mtr->m; j++)
        {
            if (&mtr->ptr[i][j] == NULL)
                return ERR_CORRUPTED_DATA;
        }
    }

    return OK;
}

int matrix_input(FILE *f, mtr_t *mtr)
{
    int n, m;
    mtr->n = 0, mtr->m = 0;
    if (fscanf(f, "%d", &n) != ARG_READ)
    {
        mtr->ptr = NULL;
        return ERR_IO;
    }
    if (fscanf(f, "%d", &m) != ARG_READ)
    {
        mtr->ptr = NULL;
        return ERR_IO;
    }
    if (n <= 0 || m <= 0)
    {
        mtr->ptr = NULL;
        return ERR_IO;
    }
    mtr->n = (size_t) n;
    mtr->m = (size_t) m;

    mtr->ptr = matrix_alloc(n, m);
    if (!mtr->ptr)
        return ERR_MEM;

    double val;
    for (size_t i = 0; i < mtr->n; i++)
    {
        for (size_t j = 0; j < mtr->m; j++)
        {
            if (fscanf(f, "%lf", &val) != ARG_READ)
            {
                //matrix_free(mtr->ptr, mtr->n);
                return ERR_CORRUPTED_DATA;
            }
            mtr->ptr[i][j] = val;
        }
    }
    return OK;
}

size_t cnt_nonzero(const mtr_t *mtr)
{
    size_t nonzero_count = 0;
    for (size_t i = 0; i < mtr->n; i++)
    {
        for (size_t j = 0; j < mtr->m; j++)
        {
            if (fabs(mtr->ptr[i][j]) > EPS)
            {
                nonzero_count++;
            }
        }
    }
    return nonzero_count;
}

// Функция вывода матрицы в выходной файл
void matrix_output(FILE *fout, const mtr_t *mtr)
{
    // Запись размеров матрицы и количества ненулевых элементов
    fprintf(fout, "%zu %zu %zu\n", mtr->n, mtr->m, cnt_nonzero(mtr));


    // Запись координат и значений ненулевых элементов
    for (size_t i = 0; i < mtr->n; i++)
    {
        for (size_t j = 0; j < mtr->m; j++)
        {
            if (fabs(mtr->ptr[i][j]) > EPS)
            {
                fprintf(fout, "%zu %zu %.6lf\n", i + 1, j + 1, mtr->ptr[i][j]);
            }
        }
    }
}
// void printMtr(mtr_t mtr)
// {
//     for (size_t i = 0; i < mtr.n; i++)
//     {
//         for (size_t j = 0; j < mtr.m; j++)
//         {
//             printf("%.6lf ", mtr.ptr[i][j]);
//         }
//         printf("\n");
//     }
// }
