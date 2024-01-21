#include "array.h"

int get_max_int(void)
{
    return INT_MAX;
}

bool is_prime(int n)
{
    if (n <= 1)
        return false;

    // Оптимально проверять делители, меньшие чем корень из n
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int fill_arr_with_primes(int *a, size_t size)
{
    if (a == NULL)
        return ERR_ARGS;
    // Начинаем с первого простого числа (2)
    int num = 2;
    for (size_t i = 0; i < size; i++)
    {
        // Ищем следующее простое число
        while (!is_prime(num))
            num++;
        a[i] = num;
        num++;
    }
    return OK;
}

int rewrite_arr(int *src, int *dst, size_t size, size_t *dst_size, int number)
{
    size_t cnt = 0;
    for (size_t i = 0; i < size; i++)
        if (src[i] % 2 == 0)
            cnt++;
    if (*dst_size < (cnt + size))
    {
        *dst_size = (cnt + size);
        return ERR_ARGS;
    }

    cnt = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (dst != NULL)
            dst[cnt] = src[i];
        cnt++;
        // Если элемент четный, добавляем указанное число
        if (src[i] % 2 == 0)
        {
            if (dst != NULL)
                dst[cnt] = number;
            //printf("EVEN FOUND\n");
            cnt++;
        }
    }
    *dst_size = cnt;
    return OK;
}