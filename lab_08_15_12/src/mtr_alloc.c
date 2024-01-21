#include "mtr_alloc.h"


double **matrix_alloc(size_t n, size_t m)
{
    double **matrix = NULL;

    matrix = calloc(n, sizeof(double *));
    if (!matrix)
        return NULL;
    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = malloc(m * sizeof(double));
        if (!matrix[i])
        {
            matrix_free(matrix, n);
            return NULL;
        }
    }
    return matrix;
}

void matrix_free(double **matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}
// double **matrix_alloc(size_t n, size_t m)
// {
//     double **matrix = NULL;

//     matrix = malloc(n * sizeof(double *) + n * m * sizeof(double));
//     if (!matrix)
//         return NULL;

//     for (size_t i = 0; i < n; i++)
//     {
//         matrix[i] = (double *)(((char *) matrix) + n * sizeof(double *) + i * m * sizeof(double));
//     }

//     for (size_t i = 1; i < n; i++)
//     {
//         matrix[i] = matrix[i - 1] + m;
//     }

//     return matrix;
// }

// void matrix_free(double **matrix, size_t n)
// {
//     (void) n;
//     free(matrix);
//     matrix = NULL;
// }
