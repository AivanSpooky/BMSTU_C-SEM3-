#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_NEG 2

void print_number(int n)
{
    if (n == 0)
    {
        return;
    }
    int digit = n % 10;
    print_number(n / 10);
    printf("%d", digit);
}

int main(void)
{
    int n;
    
    printf("Введите натуральное число n:\n");
    if (scanf("%d", &n) != 1)
    {
        printf("IO error!");
        return ERR_IO;
    }
    else if (n <= 0)
    {
        printf("Число N должно быть натуральным!\n");
        return ERR_NEG;
    }

    print_number(n);

    return OK;
}