#include "work_funcs.h"

int split_line(char *str, char words[][WORD_LEN], size_t *words_size)
{
    char *istr;

    istr = strtok(str, SEPARATORS);

    while (istr != NULL)
    {
        if ((*words_size) >= ARR_LEN)
            return ERR_RANGE;
        if (strlen(istr) > WORD_LEN)
            return ERR_WORD_RANGE;
        else
        {
            strcpy(words[(*words_size)++], istr);
        }
        istr = strtok(NULL, SEPARATORS);
    }
    /*
    size_t len_word = 0;
    for (size_t i = 0; i <= str_size; i++)
    {
        // Если до разделителя зафиксированы буквы - запоминаем слово
        if (strchr(SEPARATORS, str[i]))
        {
            if (len_word > 0)
            {
                word[len_word] = '\0';
                strcpy(words[(*words_size)++], word);
                len_word = 0;
            }
        }
        // Пока длина слова в пределе допустимых значений - заполняем буфер слова
        else if (len_word < WORD_LEN - 1)
            word[len_word++] = str[i];
        else
            return ERR_WORD_RANGE;
    }
    if (len_word > 0)
    {
        word[len_word] = '\0';
        strcpy(words[(*words_size)++], word);
        len_word = 0;
    }
    */
    return OK;
}

void make_set_letters(char *str)
{
    // Смог исправить через memset, как в 5ой лр
    char new_str[WORD_LEN];
    memset(new_str, 0, sizeof(new_str));
    size_t str_len = 0;
    new_str[0] = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
        if (strchr(new_str, str[i]) == NULL)
            new_str[str_len++] = str[i];
    strcpy(str, new_str);
}

int check_words(char words[][WORD_LEN], size_t words_size, size_t *indexes)
{
    size_t count = 0; // Количество слов, схожих с последним
    for (size_t i = 0; i < (words_size - 1); i++)
        if (strcmp(words[i], words[words_size - 1]) == 0)
        {
            count++;
            indexes[i] = 1;
        }
        else
        {
            make_set_letters(words[i]);
            indexes[i] = 0;
        }
    if (words_size == 1)
    {
        printf("ERR_NOT_ENOUGH_WORDS\n");
        return ERR_NOT_ENOUGH_WORDS;
    }
    if (count == (words_size - 1))
    {
        printf("ERR_EQUAL_LAST\n");
        return ERR_EQUAL_LAST;
    }
    return OK;
}
