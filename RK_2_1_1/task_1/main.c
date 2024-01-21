#include <stdio.h>
#include <stdbool.h>

#define OK 0
#define ERR_IO 1
#define ERR_NO_ODD 2
// Функция подсчета количества минимальных нечетных
void find_min_odd_coun(int *n, int *min_odd_n, int *amount)
{
    if (*n < *min_odd_n)
    {
        *min_odd_n = *n;
        *amount = 1;
    }
    else if (*n == *min_odd_n)
    {
        (*amount)++;
    }
}
// Функция ввода чисел
int input(bool *entered, int *min_odd_n, int *amount)
{
    int n = 0;
    (*amount) = 0;
    printf("Input numbers: ");
    do
    {
        if (scanf("%d", &n) != 1)
        {
           return ERR_IO;
        }
        if (n % 2 != 0)
        {
            if (*entered == false)
            {
                (*min_odd_n) = n;
                (*entered) = true;
    		}
            find_min_odd_coun(&n, min_odd_n, amount);
           
        }
    }while (n != 0);
    return OK;
}

int main(void)
{
    int min_odd_n;
    int amount = 0;
    bool entered = false;
    if (input(&entered, &min_odd_n, &amount) != 0)
    {
        return ERR_IO;
    }
    if (entered == false)
    {
       return ERR_NO_ODD;
    }
    printf("%d %d", min_odd_n, amount);
    return OK;
}
