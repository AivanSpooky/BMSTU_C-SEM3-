#include "input_output.h"

int get_line(char *str, size_t *str_size)
{
    char buf[STR_LEN+1];
    char end = '\n';
    printf("Input string: ");
    char *p = fgets(buf, STR_LEN + 1, stdin);
    if (p == NULL)
        return ERR_IO;
    if (buf[0] == end)
        return ERR_BUF_TOO_SMALL;
    if ((strlen(buf) == STR_LEN) && (buf[strlen(buf) - 1] != end))
        return ERR_RANGE;
    if (buf[strlen(buf) - 1] == end)
        buf[strlen(buf) - 1] = '\0';
    strcpy(str, buf);
    (*str_size) = strlen(buf) - 1;
    return OK;  
}

void print(char words[][WORD_LEN], size_t words_size)
{
    printf("Result: ");
    for (size_t i = 0; i < words_size; i++)
        printf("%s ", words[i]);
}

bool print_error(int rc)
{
    switch (rc)
    {
        case ERR_IO:
            printf("ERR_IO\n");
            return true;
        case ERR_BUF_TOO_SMALL:
            printf("ERR_BUF_TOO_SMALL\n");
            return true;
        case ERR_RANGE:
            printf("ERR_RANGE\n");
            return true;
        case ERR_WORD_RANGE:
            printf("ERR_WORD_RANGE\n");
            return true;
        case ERR_NO_WORDS:
            printf("ERR_NO_WORDS\n");
            return true;
        default:
            if (rc != OK)
            {
                printf("UNKNOWN ERROR CODE!\n");
                return true;
            }
            return false;
    }
}
