#include "file_op.h"

int find_count(FILE *file, size_t *n)
{
    int num;
    size_t cnt = 0;
    while (fscanf(file, "%d", &num) == ARG_READ)
        cnt++;
    if (!feof(file))
        return ERR_IO;
    (*n) = cnt;
    return OK;
}

int array_fill(FILE *file, int *pbeg, int *pend)
{
    int *pcur = pbeg;
    while (pcur < pend)
    {
        if (fscanf(file, "%d", pcur) != ARG_READ)
            return ERR_IO;
        pcur++;
    }
    return OK;
}

void print_arr_to_file(FILE *file, const int *pbeg, const int *pend)
{
    const int *pcur = pbeg;
    while (pcur < pend)
    {
        fprintf(file, "%d ", *pcur);
        pcur++;
    }
    fprintf(file, "\n");
}

int print_sorted_arr_to_outfile(char *filename, int *ptr, const size_t n)
{
    int rc = OK;
    // Сортируем массив
    mysort(ptr, n, sizeof(int), int_cmp);
    // Выводим полученный массив в файл
    FILE *fout = fopen(filename, "w");
    if (fout)
    {
        print_arr_to_file(fout, ptr, ptr + n);
        fclose(fout);
    }
    else
    {
        rc = ERR_IO;
    }
    return rc;
}
