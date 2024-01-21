#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "err_codes.h"

#include "file_funcs.h"

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 4)
		return ERR_ARGS;
	
	
	if (argc == 3 && strcmp(argv[1], "c") == 0)
	{
		char *filename = argv[2];
		FILE *file = fopen(filename, "wb");
		if (file == NULL)
			return ERR_FILE; 
		if (fill_file(file) != OK)
		{
			fclose(file);
			return ERR_FILE_WRITE;
		}
	}
	else if (argc == 3 && strcmp(argv[1], "p") == 0)
	{
		char *filename = argv[2];
		FILE *file = fopen(filename, "rb");
		if (file == NULL)
			return ERR_FILE;
		if (print_file(file) != OK)
		{
			printf("ERR_DATA\n");
			fclose(file);
			return ERR_DATA;
		}
		fclose(file);
	}
	else if (argc == 4 && strcmp(argv[1], "m") == 0)
	{
		char *filename1 = argv[2];
		char *filename2 = argv[3];
		FILE *file1 = fopen(filename1, "rb+");
		FILE *file2 = fopen(filename2, "rb");
		if (union_files(file1, file2) != OK)
		{
			fclose(file1);
			fclose(file2);
			printf("ERR_DATA\n");
			return ERR_DATA;
		}
		fclose(file1);
		fclose(file2);
	}
	else
		return ERR_COMMAND;
	return OK;
}
