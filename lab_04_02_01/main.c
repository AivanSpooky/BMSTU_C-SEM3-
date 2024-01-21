#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "input_output.h"
#include "work_funcs.h"
#include "err_codes.h"

int main(void)
{
    char str[STR_LEN];
    size_t str_size;
    char words[ARR_LEN][WORD_LEN];
    size_t words_size = 0;

    int rc = get_line(str, &str_size);
    if (print_error(rc))
        return rc;

    rc = split_line(str, str_size, words, &words_size);
    if (print_error(rc))
        return rc;

    // Если нет слов - ошибка
    if (words_size == 0)
    {
        rc = ERR_NO_WORDS;
        print_error(rc);
        return rc;
    }

    if (print_error(rc))
        return rc;

    char uwords[ARR_LEN][WORD_LEN];
    size_t uwords_size = 0;

    make_array_equal(words, words_size, uwords, &uwords_size);

    sort(uwords, uwords_size);
    print(uwords, uwords_size);
    return OK;
}
