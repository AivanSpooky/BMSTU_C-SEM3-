#include "file_check.h"

int file_size_check(FILE *file)
{
    if (fseek(file, 0, SEEK_END) != OK)
        return ERR_RANGE;
    long size = ftell(file);
    if (size < 0)
        return ERR_RANGE;
    //printf("%li |%zu", ftell(file), sizeof(number_t));
    if ((unsigned long)size % sizeof(number_t) != 0 || (unsigned long)size / sizeof(number_t) == 0)
        return ERR_FILE_OPEN;
    if (fseek(file, 0, SEEK_SET) != OK)
        return ERR_RANGE;

    return OK;
}
