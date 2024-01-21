#include "input_output.h"

int get_line(char *str, size_t *str_size)
{
    char buf[STR_LEN+1];
    char end = '\n';
    char *p = fgets(buf, STR_LEN + 1, stdin);
    if (p == NULL)
        return ERR_IO;
    if ((strlen(buf) == STR_LEN) && (buf[strlen(buf) - 1] != end))
        return ERR_RANGE;
    if (strchr(SEPARATORS, buf[strlen(buf) - 1]) != NULL)
        buf[strlen(buf) - 1] = '\0';
    strcpy(str, buf);
    (*str_size) = strlen(buf) - 1;
    return OK;  
}
