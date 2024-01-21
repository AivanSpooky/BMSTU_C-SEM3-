#include "work_funcs.h"

int split_line(const char *str, size_t str_size, char words[][WORD_LEN], size_t *words_size)
{
    char word[WORD_LEN];
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
        {
            if ((*words_size) >= ARR_LEN)
                return ERR_RANGE;
            word[len_word++] = str[i];
        }
        else
            return ERR_WORD_RANGE;
    }
    if (len_word > 0)
    {
        word[len_word] = '\0';
        strcpy(words[(*words_size)++], word);
        len_word = 0;
    }
    return OK;
}

// void delete_word(char words[][WORD_LEN], size_t *words_size, size_t index)
// {
//     for (size_t i = index; i < (*words_size) - 1; i++)
//     {
//         strcpy(words[i], words[i + 1]);
//     }
//     (*words_size)--;
// }

size_t cnt_word_in_array(char *word, char words[][WORD_LEN], size_t words_size, size_t ind)
{
    size_t cnt = 0;
    for (size_t i = ind; i < words_size; i++)
        if (strcmp(word, words[i]) == 0)
            cnt++;
    return cnt;
}

void make_array_equal(char words[][WORD_LEN], size_t words_size, char uwords[][WORD_LEN], size_t *uwords_size)
{
    size_t i = 0;
    (*uwords_size) = 0;
    while (i < words_size)
    {
        if (cnt_word_in_array(words[i], words, words_size, i) == 1)
        {
            strcpy(uwords[(*uwords_size)++], words[i]);
        }
        i++;
    }
}
// void delete_equal(char words[][WORD_LEN], size_t *words_size)
// {
//     size_t words_cnt = (*words_size);
//     size_t i = 0;
//     while (i < words_cnt - 1)
//     {
//         size_t j = (i + 1);
//         while (j < words_cnt)
//         {
//             // Если слова одинаковые - удаляем слово words[j]
//             if (strcmp(words[i], words[j]) == 0)
//                 delete_word(words, &words_cnt, j);
//             else
//                 j++;
//         }
//         i++;
//     }
//     (*words_size) = words_cnt;
// }

void sort(char words[][WORD_LEN], size_t words_size)
{
    size_t min_elem = 0;
    char tmp_elem[WORD_LEN];
    char tmp_elem_1[WORD_LEN];
    for (size_t i = 0; i < (words_size - 1); i++)
    {
        min_elem = i;
        for (size_t j = (i + 1); j < words_size; j++)
        {
            if (strcmp(words[j], words[min_elem]) < 0)
            {
                min_elem = j;
            }
        }
        strcpy(tmp_elem, words[min_elem]);
        strcpy(tmp_elem_1, words[i]);
        strcpy(words[i], tmp_elem);
        strcpy(words[min_elem], tmp_elem_1);
    }
}
