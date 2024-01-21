#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "consts.h"
#include "err_codes.h"

#include "sort.h"
#include "file_opt.h"

/**
 * @details Выбранный целочисленный тип - number_t (по сути int32_t занимает ровно 4 байта)
 * @details Выбранный алгоритм сортировки - сортировка выбором
 * @details Выбранное направление упорядочивания - по возрастанию
*/
int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        //fprintf(stderr, "Use: %s [c(number)|p|s] filename\n", argv[0]);
        return ERR_INVALID_ARGS;
    }

    char *filename;
    FILE *file;

    if (strcmp(argv[1], "c") == 0 && argc == 4)
    {
        if (strspn(argv[2], DIGITS) != strlen(argv[2]) || strcmp(argv[2], "0") == 0)
        {
            //fprintf(stderr, "%s - is not a number! (or equal zero)\n", argv[2]);
            return ERR_INVALID_ARGS;
        }
        size_t count = atoi(argv[2]);
        filename = argv[3];

        file = fopen(filename, "wb");
        if (file == NULL)
        {
            //fprintf(stderr, "Failed to open file!\n");
            return ERR_FILE_OPEN;
        }

        if (fill_file_with_rand(file, count) != OK)
        {
            //fprintf(stderr, "Failed to create file!\n");
            fclose(file);
            return ERR_FILE_WRITE;
        }
    }
    else if (strcmp(argv[1], "p") == 0 && argc == 3)
    {
        filename = argv[2];

        file = fopen(filename, "rb");
        if (file == NULL)
        {
            //fprintf(stderr, "Failed to open file!\n");
            return ERR_FILE_OPEN;
        }

        if (output_numbers_from_file(file) != OK)
        {
            //fprintf(stderr, "File size error!\n");
            fclose(file);
            return ERR_RANGE;
        }
    }
    else if (strcmp(argv[1], "s") == 0 && argc == 3)
    {
        filename = argv[2];

        file = fopen(filename, "r+b");
        if (file == NULL)
        {
            //fprintf(stderr, "Failed to open file!\n");
            return ERR_FILE_OPEN;
        }
        
        if (selection_sort_numbers_in_file(file) != OK)
        {
            //fprintf(stderr, "File range error!\n");
            fclose(file);
            return ERR_RANGE;
        }
    }
    else
    {
        //fprintf(stderr, "Invalid command combination!\n");
        return ERR_INVALID_ARGS;
    }
    fclose(file);
    return OK;
}
