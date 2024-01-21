#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "product_t.h"

#include "file_bin.h"
#include "file_text.h"

#include "consts.h"
#include "err_codes.h"

/**
 * @brief Функция проверяет целостность файла (корректность данных)
 * @param FILE *file - файл
 * @param char *mode - тип файла (текстовый/бинарный)
 * @return Функция возвращает код ошибки
*/
int check_file(FILE *file, char *mode)
{
    if (fseek(file, 0, SEEK_END) != OK)
    {
        return ERR_FILE_RANGE;
    }

    long file_size = ftell(file);
    //fprintf(stderr, "%ld", file_size);
    if (file_size < 0 || (file_size == 0 && strcoll(mode, "ft") == 0))
    {
        return ERR_FILE;
    }
    
    size_t is_struct_file = file_size % sizeof(product_t);
    if (strcoll(mode, "ab") == 0 && is_struct_file != 0)
    {
        //printf("No products found in file\n");
        return ERR_FILE_RANGE;
    }
    rewind(file);
    return OK;
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4 || (strcmp(argv[1], "ft") != 0 && strcmp(argv[1], "ab") != 0))
    {
        //fprintf(stderr, "Wrong command combination\n");
        return ERR;
    }
    
    
    if (argc == 4 && (strcmp(argv[1], "ft") == OK))
    {
        if (strlen(argv[3]) == 0 || strlen(argv[3]) > 30)
            return ERR_DATA;
        FILE *file = fopen(argv[2], "r");
        if (!file)
        {
            //fprintf(stderr, "Failed to open file '%s' for reading and writing\n", argv[2]);
            return ERR_FILE;
        }
        if (check_file(file, argv[1]) != OK)
        {
            fclose(file);
            return ERR_FILE;
        }
        // /*
        // Игорь Владимирович. Я просто без понятия, как сделать эту задачу без динам. массива
        // В условии сказано, что при обработке текстового файла данные надо записать в массив
        // А как заранее, не зная количество продуктов в файле, узнать их? Даже если узнать, сколько
        // структур хранится в текстовом файле, то gcc не дает право использовать переменную в качестве размера массива.
        // Флаг -Wvla, кстати, не ругается.
        // */
        // P.S. - Исправил заменой на большую константу.
        // Лучше такой момент зафиксировать в условии задания (сказать максимальное кол-во продуктов).
        size_t cnt = 0;
        product_t products[MAX_PRODUCTS_COUNT];
        memset(&products, 0, sizeof(products));

        if (fill_parray(file, products, &cnt) != OK)
        {
            //fprintf(stderr, "Failed to fill array\n");
            fclose(file);
            return ERR_FILE_RANGE;
        }

        if (print_products(products, cnt, argv[3]) != OK)
        {
            fclose(file);
            return ERR_DATA;
        }
        
        // if (ferror(file))
        // {
        //     //fprintf(stderr, "Error occurred while reading file '%s'\n", argv[2]);
        //     fclose(file);
        //     return ERR_FILE;
        // }
        fclose(file);
    }
    else if (argc == 3 && (strcmp(argv[1], "ab") == OK))
    {
        FILE *file = fopen(argv[2], "rb+");
        if (!file)
        {
            //fprintf(stderr, "Failed to open file '%s' for reading and writing\n", argv[2]);
            return ERR_FILE;
        }
        if (check_file(file, argv[1]) != OK)
            return ERR_FILE;

        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        size_t count = file_size / sizeof(product_t);
        rewind(file);

        if (add_product(file, count) != OK)
        {
            fclose(file);
            return ERR_FILE_RANGE;
        }
        fclose(file);
    }
    else 
    {
        return ERR;
    }

    return OK;
}
