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

    rc = split_line(str, words, &words_size);
    if (print_error(rc))
        return rc;

    // Если нет слов - ошибка
    if (words_size == 0)
    {
        rc = ERR_NO_WORDS;
        print_error(rc);
        return rc;
    }

    size_t indexes[ARR_LEN]; // Признак вывода каждого (по индексу) слова  (0 - выводим, 1 - не выводим)
    rc = check_words(words, words_size, indexes);
    if (print_error(rc))
        return rc;

    char n_str[STR_LEN];
    rc = print_reverse(words, (words_size - 1), indexes, n_str);
    if (rc == OK)
        printf("Result:%s", n_str);
    return rc;
}
