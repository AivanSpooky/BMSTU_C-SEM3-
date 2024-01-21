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

int form_rev_str(char words[][WORD_LEN], size_t words_size, size_t indexes[], char *new_str)
{
    size_t str_size = 0;
    for (int i = (words_size - 1); i >= 0; i--)
    {
        if (str_size >= STR_LEN)
            return ERR_RANGE;
        if (indexes[i] == OK)
        {
            strcat(new_str, " ");
            strcat(new_str, words[i]);
            str_size += strlen(words[i]) + 1;
        }
    }
    return OK;
}

int print_reverse(char words[][WORD_LEN], size_t words_size, size_t indexes[], char *str)
{
    // Здесь все сработало
    char new_str[STR_LEN];// = { 0 };
    new_str[0] = '\0';
    if (form_rev_str(words, words_size, indexes, new_str) != OK)
        return ERR_RANGE;
    strcpy(str, new_str);
    return OK;
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
        case ERR_NOT_ENOUGH_WORDS:
            printf("ERR_NOT_ENOUGH_WORDS\n");
            return true;
        case ERR_EQUAL_LAST:
            printf("ERR_EQUAL_LAST\n");
            return ERR_EQUAL_LAST;
        default:
            if (rc != OK)
            {
                printf("UNKNOWN ERROR CODE!\n");
                return true;
            }
            return false;
    }
}

