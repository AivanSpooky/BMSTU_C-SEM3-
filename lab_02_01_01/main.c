#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_ODD 3
#define NOT_ODD 3

#define N 10

// Функция ввода массива целых чисел 
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
// Проверка числа на нечетность
bool is_odd(int num)
{
	if (abs(num) % 2 != 0)
		return true;
	return false;
}
// Нахождение произведения нечетных чисел массива
int find_odd_product(const int a[], size_t a_size)
{
	int product = 0;
	for (size_t i = 0; i < a_size; i++)
		if (is_odd(a[i]))
		{
			if (product == 0)
				product = 1;
			product *= a[i];
		}
	return product;		
}

int main(void)
{
	int a[N];
	size_t a_size = 0;
	int odd_product = 0;
	
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

	odd_product = find_odd_product(a, a_size);
	if (odd_product == 0)
	{
		printf("ERR_NO_ODD\n");
		return ERR_NO_ODD;
	}
	printf("\nResult: %d\n", odd_product);

	return OK;
}
