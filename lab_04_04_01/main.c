#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "input_output.h"
#include "work_funcs.h"
#include "err_codes.h"

int main(void)
{
    char str[STR_LEN];
    size_t str_size;
    /*
    char words[ARR_LEN][WORD_LEN];
    size_t words_size = 0;
    */
    int rc = get_line(str, &str_size);
    if (rc != OK)
        return rc;
    if (str[0] == '\0')
    {
        printf("NO\n");
        return OK;
    }
    rc = find_num(str, str_size);
    if (rc == ERR_NO_WORDS)
    {
        printf("NO\n");
        return OK;
    }
    if (is_regex_found(str))
        printf("YES\n");
    else
        printf("NO\n");
    return OK;
}
