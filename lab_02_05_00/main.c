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
	if ((*n) <= 1 || (*n) > N)
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
// Найти максимальную сумму по правилу
int get_max(int *const pb, int *const pe)
{
	int max = (*pb + *(pe - 1));
	int *pbeg = pb;
	int *pend = pe - 1;
	while (pbeg <= pend)
	{
		if (max < (*pbeg + *pend))
			max = (*pbeg + *pend);
		pbeg++;
		pend--;
	}
	return max;
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
	int max = get_max(pb, pe);
	printf("%d\n", max);
	
	return OK;
}
