#include "file_opt.h"

int fill_file_with_rand(FILE* file, size_t count)
{
    if (count == 0)
        return ERR_RANGE;
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < count; ++i)
    {
        number_t num = rand() % MAX_INT;
        if (fwrite(&num, sizeof(num), 1, file) != 1)
        {
            return ERR_FILE_WRITE;
        }
    }

    return OK;
}

int output_numbers_from_file(FILE* file)
{
    number_t num;
    size_t n = 0;

    if (file_size_check(file) != OK)
        return ERR_FILE_READ;

    while (fread(&num, sizeof(num), 1, file) == 1)
    {
        printf("%" PRId32 "\n", num);
        n++;
    }

    if (n == 0)
        return ERR_RANGE;

    return OK;
}
