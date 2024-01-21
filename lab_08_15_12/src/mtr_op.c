#include "mtr_op.h"

// Функция считает определитель матрицы (рекурсивный алгоритм)
double matrix_determinant(const double **ptr, size_t n)
{
    // Обработка частных маленьких случаев
    if (n == 1)
    {
        return ptr[0][0];
    }
    else if (n == 2)
    {
        return ptr[0][0] * ptr[1][1] - ptr[0][1] * ptr[1][0];
    }
    else
    {
        double det = 0;
        // Итерируем по первой строке матрицы
        for (size_t j = 0; j < n; j++)
        {
            // Выделение памяти для подматрицы
            double **submtr = matrix_alloc(n - 1, n - 1);
            if (!submtr)
            {
                return OK; // Ошибочное значение взято как 0.
            }

            // Заполнение подматрицы значениями из исходной
            for (size_t i = 1; i < n; i++)
            {
                size_t k = 0;
                for (size_t l = 0; l < n; l++)
                {
                    // Пропускаем столбец, взятый у текущего элемента
                    if (l != j)
                    {
                        submtr[i - 1][k] = ptr[i][l];
                        k++;
                    }
                }
            }
            
            // Рекурсивный вызов для подматрицы
            double subdet = matrix_determinant((const double **)submtr, n - 1);
            matrix_free(submtr, n - 1);
            // Вычисление определителя
            det += (j % 2 == 0 ? 1 : -1) * ptr[0][j] * subdet;
        }

        return det;
    }
}

// Функция сложения двух матриц
mtr_t matrix_addition(const mtr_t *mtr1, const mtr_t *mtr2)
{
    mtr_t result;
    result.n = mtr1->n;
    result.m = mtr1->m;

    // Проверка на корректность размеров матриц
    if (mtr1->n != mtr2->n || mtr1->m != mtr2->m)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }
    // Проверка на корректность элементов матрицы
    if (matrix_check(mtr1) != OK || matrix_check(mtr2) != OK)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }

    // Выделение памяти для результирующей матрицы
    result.ptr = matrix_alloc(result.n, result.m);
    if (!result.ptr)
    {
        return result;
    }
    // result.ptr = (double **)malloc(result.n * sizeof(double *));
    // for (size_t i = 0; i < result.n; i++)
    // {
    //     result.ptr[i] = (double *)malloc(result.m * sizeof(double));
    // }

    // Сложение элементов матриц
    for (size_t i = 0; i < result.n; i++)
    {
        for (size_t j = 0; j < result.m; j++)
        {
            result.ptr[i][j] = mtr1->ptr[i][j] + mtr2->ptr[i][j];
        }
    }

    return result;
}

// Функция умножения двух матриц
mtr_t matrix_multiplication(const mtr_t *mtr1, const mtr_t *mtr2)
{
    mtr_t result;
    result.n = mtr1->n;
    result.m = mtr2->m;

    // Проверка на корректность элементов матрицы
    if (matrix_check(mtr1) != OK || matrix_check(mtr2) != OK)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }
    // Проверка на корректность размеров матриц
    if (mtr1->m != mtr2->n)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }

    // Выделение памяти для результирующей матрицы
    result.ptr = matrix_alloc(result.n, result.m);
    if (!result.ptr)
    {
        return result;
    }
    // result.ptr = (double **)malloc(result.n * sizeof(double *));
    // for (size_t i = 0; i < result.n; i++)
    // {
    //     result.ptr[i] = (double *)malloc(result.m * sizeof(double));
    // }

    // Умножение матриц
    for (size_t i = 0; i < result.n; i++)
    {
        for (size_t j = 0; j < result.m; j++)
        {
            result.ptr[i][j] = 0;
            for (size_t k = 0; k < mtr1->m; k++)
            {
                result.ptr[i][j] += mtr1->ptr[i][k] * mtr2->ptr[k][j];
            }
        }
    }

    return result;
}

mtr_t matrix_inverse(const mtr_t *mtr)
{
    mtr_t result;
    result.n = mtr->n;
    result.m = mtr->m;

    // Проверка на корректность элементов матрицы
    if (matrix_check(mtr) != OK)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }
    // Проверка квадратности матрицы
    if (mtr->n != mtr->m)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }
    // Проверка определителя
    double det = matrix_determinant((const double **)mtr->ptr, mtr->n);
    if (fabs(det) < EPS)
    {
        result.ptr = NULL;
        result.n = 0;
        return result;
    }

    // Создание расширенной матрицы [A|E]
    double **extended_mtr = matrix_alloc(mtr->n, 2 * mtr->n);
    if (extended_mtr)
    {
        for (size_t i = 0; i < mtr->n; i++)
        {
            for (size_t j = 0; j < mtr->n; j++)
            {
                extended_mtr[i][j] = mtr->ptr[i][j];
                extended_mtr[i][mtr->n + j] = 0.0;
            }
            extended_mtr[i][mtr->n + i] = 1.0;
        }

        // Приведение левой половины расширенной матрицы к единичной
        for (size_t i = 0; i < mtr->n; i++)
        {
            // leading_element выбирается как максимальный из столбца
            size_t pivot_row = i;
            for (size_t j = i + 1; j < mtr->n; j++)
            {
                if (extended_mtr[j][i] - extended_mtr[pivot_row][i] > EPS)
                    pivot_row = j;
            }
            if (pivot_row != i)
            {
                double *tmp = extended_mtr[pivot_row];
                extended_mtr[pivot_row] = extended_mtr[i];
                extended_mtr[i] = tmp;
            }
            // Деление строки на ведущий элемент
            double leading_element = extended_mtr[i][i];
            for (size_t j = 0; j < 2 * mtr->n; j++)
            {
                extended_mtr[i][j] /= leading_element;
            }

            // Вычитание текущей строки из остальных строк
            for (size_t k = 0; k < mtr->n; k++)
            {
                if (k != i)
                {
                    double factor = extended_mtr[k][i];
                    for (size_t j = 0; j < 2 * mtr->n; j++)
                    {
                        extended_mtr[k][j] -= factor * extended_mtr[i][j];
                    }
                }
            }
        }

        // Извлечение обратной матрицы из правой половины расширенной матрицы
        result.ptr = matrix_alloc(result.n, result.n);
        if (result.ptr)
        {
            for (size_t i = 0; i < mtr->n; i++)
            {
                for (size_t j = 0; j < mtr->n; j++)
                {
                    // printf("%lf\n", extended_mtr[i][mtr->n + j]);
                    result.ptr[i][j] = extended_mtr[i][mtr->n + j];
                }
            }
        }
    }
    else
    {
        result.ptr = NULL;
        result.n = 0;
    }

    matrix_free(extended_mtr, mtr->n);

    return result;
}
