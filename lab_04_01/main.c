#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "work_funcs.h"
#include "err_codes.h"

int main(void)
{
	char str1_arr[ARR_LEN][WORD_LEN] = { "", "1232", "a1b2c3", "abcdefghijklmno" };
	char str2_arr[ARR_LEN][WORD_LEN] = { "", "32", "abc", "iklpc" };
	int ch_arr[ARR_LEN] = { 'r', '2', 'a', 'p' };
	size_t counter = 0;
	for (size_t i = 0; i < (sizeof(str1_arr) / sizeof(str1_arr[0])); i++)
	{
		if (my_strpbrk(str1_arr[i], str2_arr[i]) != strpbrk(str1_arr[i], str2_arr[i]))
			counter++;
		if (my_strspn(str1_arr[i], str2_arr[i]) != strspn(str1_arr[i], str2_arr[i]))
			counter++;
		if (my_strcspn(str1_arr[i], str2_arr[i]) != strcspn(str1_arr[i], str2_arr[i]))
			counter++;
		if (my_strchr(str1_arr[i], ch_arr[i]) != strchr(str1_arr[i], ch_arr[i]))
			counter++;
		if (my_strrchr(str1_arr[i], ch_arr[i]) != strrchr(str1_arr[i], ch_arr[i]))
			counter++;
	}
	printf("Errors count: %zu\n", counter);
	return OK;
}
