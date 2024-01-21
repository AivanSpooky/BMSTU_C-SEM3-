#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define N 10
// Функция ввода массива
int input(int a[], size_t *a_size)
{
	printf("Input n: ");
	if (scanf("%zu", a_size) != 1)
		return ERR_IO;
	if (*a_size == 0 || *a_size > N)
		return ERR_RANGE;
	printf("Input n elements: ");
	for (size_t i = 0; i < *a_size; i++)
		if (scanf("%d", &a[i]) != 1)
			return ERR_IO;
	return OK;
}
// Функция вывода массива
void print(const int a[], size_t a_size)
{
	printf("\nArray: \n");
	for (size_t i = 0; i < a_size; i++)
		printf("%d ", a[i]);
	printf("\n");
}
// Нахождение n-ого числа Фибоначи
int find_nth_fib(size_t n)
{
	int fib_n = 0;
	int fib_0 = 0;
	int fib_1 = 1;
	switch (n)
	{
		case 0:
			fib_n = fib_0;
			break;
		case 1:
			fib_n = fib_1;
			break;
		default:
			for (size_t i = 2; i <= n; i++)
			{
				fib_n = fib_0 + fib_1;
				fib_0 = fib_1;
				fib_1 = fib_n;
			}
	}
	return fib_n;
}
// Добавить элемент в массив после указанного индекса
int add_element_after(int a[], size_t *a_size, size_t index, int new_elem)
{
	if (index >= *a_size)
		return ERR_RANGE;
	for (size_t i = *a_size; i > index; i--)
		a[i] = a[i - 1];
	a[index + 1] = new_elem;
	return OK;
}
// Функция находит в массиве все числа кратные трем и добавляет после
// каждого очередное число Фибоначи
// 3*k - number that can be multiplied by 3 (integer division)
int add_fib_after_3k(int a[], size_t *a_size)
{
	size_t fib_number = 0;
	size_t i = 0;
	while (i < *a_size)
	{
		if (a[i] % 3 == 0)
		{
			add_element_after(a, a_size, i, find_nth_fib(fib_number));
			fib_number++;
			(*a_size)++;
			i++;
		}
		i++;
	}
	return OK;
}

int main(void)
{
	int a[2 * N];
	size_t a_size = 0;
	
	int error = input(a, &a_size);
	if (error != 0)
	{
		switch (error)
		{
			case ERR_IO:
				printf("ERR_IO\n");
				break;
			case ERR_RANGE:
				printf("ERR_RANGE\n");
				break;
		}
		return error;
	}
	
	add_fib_after_3k(a, &a_size);
	
	print(a, a_size);
	
	return OK;
}
