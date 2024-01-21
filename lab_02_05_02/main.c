#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define N 10
// Ввести n
int enter_n(size_t *n)
{
	printf("Input n: ");
	if (scanf("%zu", n) != 1)
		return ERR_IO;
	if ((*n) <= 0 || (*n) > N)
		return ERR_RANGE;
	return OK;
}
// Функция ввода списка
int input(int *const pb, const int *pe)
{
	printf("Input elements: ");
	int *pa = pb;
	while (pa < pe)
	{
		if (scanf("%d", pa) != 1)
			return ERR_IO;
		pa++;
	}
	return OK;
}
// Найти индекс первого отрицательного
int *find_neg_ind(int *const pb, const int *pe)
{
	int *pa = pb;
	while (pa < pe)
	{
		if (*pa < 0)
			return ++pa;
		pa++;
	}
	return pa;
}
// Посчитать сумму по условию
// A[0] + A[0]*A[1] + ... + (A[0]*A[1]*...*A[m])
// n - размер массива
// m - либо индекс первого отрицательного, либо n-1
// если отсутствуют отрицательные
void get_sum(int *pb, int *pm, int *sum)
{
	int res = 1;
	int *pa = pb;
	while (pa < pm)
	{
		res *= *pa;
		pa++;
		*sum += res;
	}
}

int main(void)
{
	size_t n;
	int error = enter_n(&n);
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

	int a[N];
	int *pb = a;
	int *pe = a + n;
	
	error = input(pb, pe);
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
	int *pm = find_neg_ind(pb, pe);
	int sum = 0;
	get_sum(pb, pm, &sum);
	printf("%d\n", sum);
	
	return OK;
}
