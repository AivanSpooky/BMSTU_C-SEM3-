#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define OK_MAX 100
#define ERR_IO 1
#define ERR_RANGE 2

#define N 10
// Функция ввода массива
int input(int a[], size_t *a_size)
{
	int arg = 0;
	printf("Input elements: ");
	for (size_t i = 0; i < N; i++)
	{
		arg = scanf("%d", &a[i]);
		if (arg != 1 && i == 0)
			return ERR_RANGE;
		
		if (arg != 1)
			return OK;
		
		(*a_size)++;
	}
	int test;
	if (scanf("%d", &test) == 1)
		return OK_MAX;
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
// Функция находит минимум в диапазоне от strat_ind до end_ind
size_t find_min_elem(const int a[], size_t start_ind, size_t end_ind)
{
	size_t min_elem = start_ind;
	for (size_t j = start_ind; j < end_ind; j++)
	{
		if (a[j] < a[min_elem])
		{
			min_elem = j;
		}
	}
	return min_elem;
}
// Функция сортировки выбором
void selection_sort(int a[], size_t a_size)
{
	size_t min_elem = 0;
	int tmp_elem = 0;
	for (size_t i = 0; i < a_size; i++)
	{
		min_elem = find_min_elem(a, i, a_size);
		tmp_elem = a[i];
		a[i] = a[min_elem];
		a[min_elem] = tmp_elem;
	}
}

int main(void)
{
	int a[N];
	size_t a_size = 0;
	
	int error = input(a, &a_size);
	if (error != OK && error != OK_MAX)
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
	
	selection_sort(a, a_size);
	
	print(a, a_size);
	if (error == 100)
		printf("Return code\n");
	return error;
}
