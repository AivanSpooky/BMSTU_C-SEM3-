#include "file_funcs.h"

// EXTINCTION FUNCS
int file_check_data(FILE *file)
{
	fseek(file, 0, SEEK_END);
	if ((size_t)ftell(file) % sizeof(double) != 0)
		return ERR_DATA;
	fseek(file, 0, SEEK_SET);
	return OK;
}

size_t get_file_size(FILE *file)
{
	fseek(file, 0, SEEK_END);
	long pos = ftell(file);
	fseek(file, 0, SEEK_SET);
	return (size_t)(pos / sizeof(double));
}

double read_d_by_pos(FILE *file, size_t pos)
{
	double number;
	fseek(file, pos*sizeof(double), SEEK_SET);
	fread(&number, sizeof(number), ARG_READ, file);
	fseek(file, 0, SEEK_SET);
	return number;
}

void put_d_by_pos(FILE *file, double d, size_t pos)
{
	
	fseek(file, pos*sizeof(double), SEEK_SET);
	fwrite(&d, sizeof(double), ARG_READ, file);
	fseek(file, 0, SEEK_SET);
}
//

// MAIN FUNCS
void insert_d(FILE *file, double num, size_t pos)
{
	size_t size = get_file_size(file);
	for (size_t i = size; i > pos; i--)
	{
		double tmp = read_d_by_pos(file, i - 1);
		put_d_by_pos(file, tmp, i);
	}
	put_d_by_pos(file, num, pos);
}

int fill_file(FILE *file)
{
	double number;
	rewind(file);
	while (fscanf(stdin, "%lf", &number) == ARG_READ)
	{
		if (fwrite(&number, sizeof(number), ARG_READ, file) != ARG_READ)
			return ERR_FILE_WRITE;	
	}
	return OK;
}

int print_file(FILE *file)
{
	double number;
	rewind(file);
	// CHECK FOR CORRECT DATA
	if (file_check_data(file) != OK)
		return ERR_DATA;
	//
	size_t cnt = fread(&number, sizeof(number), ARG_READ, file);
	while (cnt == ARG_READ)
	{
		printf("%f\n", number);
		cnt = fread(&number, sizeof(number), ARG_READ, file);
	}
	return OK;
}

int union_files(FILE *file1, FILE *file2)
{
	size_t pos1 = 0;
	size_t pos2 = 0;
	// CHECK FOR CORRECT DATA
	if (file_check_data(file1) != OK)
		return ERR_DATA;
	//
	// CHECK FOR CORRECT DATA
	if (file_check_data(file2) != OK)
		return ERR_DATA;
	//
	size_t size1 = get_file_size(file1);
	size_t size2 = get_file_size(file2);
	while ((get_file_size(file1) == pos1 && pos2 < size2) || (pos1 + pos2 + 2) <= (size1 + size2))
	{
		if (get_file_size(file1) == pos1)
		{
			double num2 = read_d_by_pos(file2, pos2);
			//printf("%lf", num2);
			insert_d(file1, num2, pos1);
			pos1++;
			pos2++;
		}
		else
		{
			double num1 = read_d_by_pos(file1, pos1);
			double num2 = read_d_by_pos(file2, pos2);
			if (num2 < num1)
			{
				insert_d(file1, num2, pos1);
				pos2++;
			}
			else
			{
				if ((pos1 + pos2 + 2) == (size1 + size2))
				{
					insert_d(file1, num2, (pos1+pos2+1));
				}
				pos1++;
			}
		}
	}
	return OK;
}
//
