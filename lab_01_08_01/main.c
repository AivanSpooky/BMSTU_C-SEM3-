#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

void bin_print(uint32_t u)
{
	printf("Result: ");
	size_t nbits = sizeof(u) * CHAR_BIT;
	uint32_t mask = (uint32_t)1 << (nbits - 1);
	
	for (size_t i = 0; i < nbits; i++)
	{
		if (u & mask)
			printf("1");
		else
			printf("0");
		mask >>= 1;
	}
	printf(" ");
}

void unpacked_print(uint8_t u)
{
	printf("%" PRIu32 " ", u);
}

uint32_t pack(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
	uint32_t u = b1;
	u <<= CHAR_BIT;
	u |= b2;
	u <<= CHAR_BIT;
	u |= b3;
	u <<= CHAR_BIT;
	u |= b4;
	return u;
}

uint8_t unpack(uint32_t u, int i)
{
	uint32_t tmp = u;
	tmp >>= CHAR_BIT * (sizeof(u) - i - 1);
	return tmp;
}

int main(void)
{
	uint8_t byte1, byte2, byte3, byte4;

	printf("Введите значения четырех байт:\n");
	if (scanf("%" SCNu8 "%" SCNu8 "%" SCNu8 "%" SCNu8,  &byte1, &byte2, &byte3, &byte4) != 4)
	{
		printf("Error: IO");
		return ERR_IO;
	}

	uint32_t packed_int = pack(byte1, byte2, byte3, byte4);
	bin_print(packed_int);
	
	for (unsigned long i = 0; i < sizeof(packed_int); i++)
	{
		uint8_t unpacked_byte = unpack(packed_int, i);
		unpacked_print(unpacked_byte);
	}
	printf("\n");

	return OK;
}
