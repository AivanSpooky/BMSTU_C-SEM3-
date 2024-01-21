#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "file_op.h"
#include "funcs.h"

#include "consts.h"
#include "err_codes.h"

int main(int argc, char **argv)
{
    // Проверка на введенные аргументы
    if (argc < 3 || argc > 4)
    {
        return ERR_ARGS;
    }
    if (argc == 4)
    {
        if (strcmp(argv[3], FILTER) == OK && strlen(argv[3]) > MAX_FILTER_COUNT)
            return ERR_ARGS;
    }
    // Открываем in-файл
    FILE *fin = fopen(argv[1], "r");
    if (!fin)
    {
        return ERR_IO;
    }
    // Считываем количество чисел из файла
    int rc = OK;
    size_t n = 0;

    rc = find_count(fin, &n);
    rewind(fin);

    if (rc != OK)
    {
        rc = ERR_IO;
    }
    else if (n == ZERO)
    {
        rc = ERR_RANGE;
    }
    else
    {
        // Выделяем память для массива чисел и заполняем его
        int *a = NULL;
        a = malloc(sizeof(int) * n);
        if (a != NULL)
        {
            rc = array_fill(fin, a, a + n);
            if (rc == OK)
            {
                rewind(fin);
                // Работаем с соответствующим массивом (либо ИЗНАЧАЛЬНЫЙ, либо ВСПОМОГАТЕЛЬНЫЙ)
                if (argc == 4)
                {
                    int *arbeg = a;
                    int *arend = arbeg + n;
                    // Память выделяет вызывающая сторона
                    int n_new = make_pre_key(a, a + n);
                    if (n_new == INT_ERR_FLAG)
                        rc = ERR_RANGE;
                    if (rc == OK)
                    {
                        arbeg = malloc(sizeof(int) * n_new);
                        if (!arbeg)
                            return ERR_MEM;
                        arend = arbeg + n_new;

                        rc = key(a, a + n, &arbeg, &arend, n_new);
                        if (rc == OK)
                        {
                            print_sorted_arr_to_outfile(argv[2], arbeg, arend - arbeg);
                        }
                        free(arbeg);
                    }
                }
                else
                {
                    if (rc == OK)
                    {
                        print_sorted_arr_to_outfile(argv[2], a, n);
                    }
                }
            }
            free(a);
        }
    }
    fclose(fin);
    return rc;
}
