#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

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
    // Загрузка библиотеки dyn_lib.so
    void *fileop_lib = dlopen("./out/dyn_lib.so", RTLD_LAZY);
    if (!fileop_lib)
        return ERR_LOAD_LIB;

    int rc = OK;
    int (*array_fill)(FILE *, int *, int *) = (int (*)(FILE *, int *, int *))dlsym(fileop_lib, "array_fill");
    if (!array_fill)
    {
        rc = ERR_LOAD_LIB_FUNC;
        goto end_fail_load_lib;
    }
    int (*find_count)(FILE *, size_t *) = (int (*)(FILE *, size_t *))dlsym(fileop_lib, "find_count");
    if (!find_count)
    {
        rc = ERR_LOAD_LIB_FUNC;
        goto end_fail_load_lib;
    }
    int (*print_sorted_arr_to_outfile)(char *, int *, const size_t) = (int (*)(char *, int *, const size_t))dlsym(fileop_lib, "print_sorted_arr_to_outfile");
    if (!print_sorted_arr_to_outfile)
    {
        rc = ERR_LOAD_LIB_FUNC;
        goto end_fail_load_lib;
    }
    int (*make_pre_key)(const int *, const int *) = (int (*)(const int *, const int *))dlsym(fileop_lib, "make_pre_key");
    if (!make_pre_key)
    {
        rc = ERR_LOAD_LIB_FUNC;
        goto end_fail_load_lib;
    }
    int (*key)(const int *, const int *, int **, int **, size_t) = (int (*)(const int *, const int *, int **, int **, size_t))dlsym(fileop_lib, "key");
    if (!key)
    {
        rc = ERR_LOAD_LIB_FUNC;
        goto end_fail_load_lib;
    }
    // Открываем in-файл
    FILE *fin = fopen(argv[1], "r");
    if (!fin)
    {
        rc = ERR_IO;
        goto end_fail_open_file;
    }
    // Считываем количество чисел из файла
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
                        {
                            rc = ERR_MEM;
                            goto end_fail_mem_alloc;
                        }
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
    end_fail_mem_alloc:
    fclose(fin);
    end_fail_open_file:
    end_fail_load_lib:
    dlclose(fileop_lib);
    return rc;
}