#include <stdio.h>

#define OK 0
#define ERR_IO 1
// Нужный размер для типа int
#define N 10
// Функция находит сумму цифр числа
size_t digit_count(int n)
{
    int m = n;
    int count = 1;
    while ((m / 10) != 0)
    {
        m /= 10;
        count++;
    }
    return count;
}
// Функция заполняет массив цифрами числа
void fill_array(int a[], size_t a_size, int n)
{
   for (size_t i = 0; i < a_size; i++)
   {
       a[i] = n % 10;
       n /= 10;
   }
}
// Функция сортирует массив по возрастанию (методом выбора)
void sort(int a[], size_t a_size)
{
    for (size_t i = 0; i < a_size; i++)
    {
        int min = a[i];
    	size_t ind = i;
        for (size_t j = i+1; j < a_size; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                ind = j;
            }
        }
        int tmp = min;
        a[ind] = a[i];
        a[i] = tmp;
    }
}
// Функция формирует новое число на основе элементов массива
int form_new_n(int a[], size_t a_size)
{
    int new_n = 0;
    int grade = 1;
    for (size_t i = 0; i < a_size; i++)
    {
       new_n += a[i]*grade;
       grade *= 10;
    }
    return new_n;
}

int main(void)
{
    int n;
    int a[N];
    size_t a_size;
    printf("Input number: ");
    if (scanf("%d", &n) != 1)
    {
        return ERR_IO;
    }
    if (n < 0)
    {
        n *= -1;
    }
    
    a_size = digit_count(n);
    fill_array(a, a_size, n);
    sort(a, a_size);
    n = form_new_n(a, a_size);
    printf("%d", n);
    return OK;
}
