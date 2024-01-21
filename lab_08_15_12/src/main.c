#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "mtr_io.h"
#include "mtr_alloc.h"
#include "mtr_op.h"

#include "consts.h"
#include "err_codes.h"

int main(int argc, char **argv)
{
    // Проверка на введенные аргументы
    if (argc < 4 || argc > 5)
    {
        return ERR_ARGS;
    }
    char op = argv[1][0];
    if ((strlen(argv[1]) > 1) || (op != PLUS && op != MULT && op != OPER))
        return ERR_ARGS;
    if (((op == PLUS || op == MULT) && argc != 5) || (op == OPER && argc != 4))
        return ERR_ARGS;

    // Открываем in-файл
    FILE *fin = fopen(argv[2], "r");
    if (!fin)
    {
        return ERR_IO;
    }

    // Считываем матрицу из файла
    int rc = OK;
    mtr_t mtr;
    mtr.ptr = NULL;

    rc = matrix_input(fin, &mtr);
    fclose(fin);
    
    mtr_t mtr1;
    mtr1.ptr = NULL;
    mtr1.n = 0;
    if (rc == OK)
    {
        // Для определенных операций считываем вторую матрицу из другого файла
        if (op == PLUS || op == MULT)
        {
            FILE *fin = fopen(argv[3], "r");
            if (!fin)
            {
                rc = ERR_IO;
            }
            else
            {
                rc = matrix_input(fin, &mtr1);
                fclose(fin);
            }
        }
    }
    
    // Выполняем операцию
    mtr_t res;
    res.ptr = NULL;
    res.n = 0;
    if (rc == OK)
    {
        switch (op)
        {
            case PLUS:
                res = matrix_addition(&mtr, &mtr1);
                if (res.ptr == NULL)
                    rc = ERR_RANGE;
                break;
            case MULT:
                res = matrix_multiplication(&mtr, &mtr1);
                if (res.ptr == NULL)
                    rc = ERR_RANGE;
                break;
            case OPER:
                res = matrix_inverse(&mtr);
                if (res.ptr == NULL)
                    rc = ERR_RANGE;
                break;
            default:
                res.ptr = NULL;
                res.n = 0;
                res.m = 0;
                rc = ERR_ARGS;
                break;
        }
    }
    //if (rc != ERR_CORRUPTED_DATA)
    matrix_free(mtr.ptr, mtr.n);

    FILE *fout = NULL;
    if (op == OPER)
    {
        if (rc == OK)
            fout = fopen(argv[3], "w");
    }
    else
    {
        if (rc == OK)
            fout = fopen(argv[4], "w");
    }
    matrix_free(mtr1.ptr, mtr1.n);
    if (rc == OK)
        if (!fout)
            rc = ERR_IO;
        
    if (rc == OK)
    {
        matrix_output(fout, &res);
        fclose(fout);
    }
    matrix_free(res.ptr, res.n);

    return rc;
}
