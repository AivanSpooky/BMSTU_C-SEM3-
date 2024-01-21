#include "sort.h"

int selection_sort_numbers_in_file(FILE* file)
{
    if (file_size_check(file) != OK)
        return ERR_FILE_READ;
    
    if (fseek(file, 0, SEEK_END) != OK)
        return ERR_RANGE;
    size_t count = ftell(file) / sizeof(number_t);
    if (fseek(file, 0, SEEK_SET) != OK)
        return ERR_RANGE;
        
    for (size_t i = 0; i < count - 1; ++i)
    {
        size_t min_idx = i;
        number_t min_val = get_number_by_pos(file, i);

        for (size_t j = i + 1; j < count; ++j)
        {
            number_t val = get_number_by_pos(file, j);
            if (val < min_val)
            {
                min_idx = j;
                min_val = val;
            }
        }

        if (min_idx != i)
        {
            number_t tmp = get_number_by_pos(file, i);
            if (put_number_by_pos(file, min_val, i) != OK)
                return ERR_RANGE;
            if (put_number_by_pos(file, tmp, min_idx) != OK)
                return ERR_RANGE;
        }
    }
    return OK;
}

number_t get_number_by_pos(FILE* file, size_t pos)
{
    fseek(file, pos * sizeof(number_t), SEEK_SET);
    number_t num;
    fread(&num, sizeof(num), 1, file);
    return num;
}

int put_number_by_pos(FILE* file, number_t num, size_t pos)
{
    fseek(file, pos * sizeof(number_t), SEEK_SET);
    if (fwrite(&num, sizeof(num), 1, file) != 1)
    {
        return ERR_FILE_WRITE;
    }
    return OK;
}
