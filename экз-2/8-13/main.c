#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Матрица как одномерный массив
#ifdef OK 
#if OK == ERR
1 - Матрица представленная одномерным массивом
Преимущества:
o Простота выделения и освобождения памяти.
o Возможность использовать как одномерный массив.
Недостатки:
o Отладчик использования памяти (например, Dr. Memory) не может отследить выход за пределы строки.
o Нужно писать i * m + j, где m – число столбцов.

2 - Матрица представленная в виде массива указателей на строки
Преимущества:
o Возможность обмена строки через обмен указателей.
o Отладчик использования памяти может отследить выход за пределы строки.
Недостатки:
o Сложность выделения и освобождения памяти.
o Память под матрицу "не лежит" одной областью.

3 - Объединенный подход-1 (отдельное выделение памяти под массив указателей и массив данных)
Преимущества:
• Относительная простота выделения и освобождения памяти.
• Возможность использовать как одномерный массив.
• Перестановка строк через обмен указателей. (Возможна ошибка в освобождении памяти, когда на нулевой указатель
встанет позиция не нулевого элемента матрицы и освободится не вся матрица, а только её часть)
Недостатки:
• Относительная сложность начальной инициализации.
• Отладчик использования памяти не может отследить выход за пределы строки.

4 - Объединенный подход-2 (массив указателей и массив данных находятся в одной области)
Преимущества:
• Простота выделения и освобождения памяти.
• Возможность использовать как одномерный массив.
• Перестановка строк через обмен указателей.
Недостатки:
• Сложность начальной инициализации.
• Отладчик использования памяти не может отследить выход за пределы строки.
#endif
// Функции
void matrix_free_1(double *data) {
    free(data);
}
double *matrix_alloc_1(size_t n, size_t m) {
    double *data = malloc(n * m * sizeof(double));
    if (data) {
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                data[i * m + j] = 0;
    }
    return data;
}

void matrix_free_2(double **data, size_t n) {
    for (size_t i = 0; i < n; i++) {
        free(data[i]);
    }
    free(data);
}
double **matrix_alloc_2(size_t n, size_t m) {
    double **data = calloc(n, sizeof(double *));
    if (data) {
        for (size_t i = 0; i < n; i++) {
            data[i] = malloc(m * sizeof(double));
            if (!data[i]) {
                matrix_free_2(data, n);
                return NULL;
            }
        }
    }
    return data;
}

void matrix_free_3(double **ptrs) {
    free(ptrs[0]);
    free(ptrs);
}
double **matrix_alloc_3(size_t n, size_t m) {
    double **ptrs, *data;
    ptrs = malloc(n * sizeof(double *));
    if (!ptrs) return NULL;
    data = malloc(n * m * sizeof(double));
    if (!data) {
        free(ptrs);
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        ptrs[i] = data + i * m;
    }
    return ptrs;
}

void matrix_free_4(double **data) {
    free(data);
}
double **matrix_alloc_4(size_t n, size_t m) {
    double **data = malloc(n * sizeof(double *) + n * m * sizeof(double));
    if (data) {
        for (size_t i = 0; i < n; i++)
            data[i] = (double *) ((char *)data + n * sizeof(double *) + i * m * sizeof(double));
    }
    return data;
}

#endif


int main(void)
{
    size_t n = 3;
    size_t m = 4;
    // 1 - Матрица представленная одномерным массивом
    {
        double *data = NULL;
        data = matrix_alloc_1(n, m);
        matrix_free_1(data);
    }

    // 2 - Матрица представленная в виде массива указателей на строки
    {
        double **data = NULL;
        data = matrix_alloc_2(n, m);
        matrix_free_2(data, n);
    }

    // 3 - Объединенный подход-1 (отдельное выделение памяти под массив указателей и массив данных)
    {
        double **data = NULL;
        data = matrix_alloc_3(n, m);
        matrix_free_3(data);
    }

    // 4 - Объединенный подход-2 (массив указателей и массив данных находятся в одной области)
    {
        double **data = NULL;
        data = matrix_alloc_4(n, m);
        matrix_free_4(data);
    }
    return OK;
}