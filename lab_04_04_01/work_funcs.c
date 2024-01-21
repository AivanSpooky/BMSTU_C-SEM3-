#include "work_funcs.h"

// Функция удаляет пробельные символы в конце строки
void del_end_spaces(char *word, size_t len_word)
{
    for (size_t i = (len_word - 1); i > 0; i--)
    {
        if (isspace(word[i]) == 0)
        {
            break;
        }
        else
        {
            word[i] = '\0';
        }
    }
}

int find_num(char *str, size_t str_size)
{
    char word[STR_LEN];
    size_t len_word = 0;
    bool beg = true;
    for (size_t i = 0; i <= str_size; i++)
    {
        if (isspace(str[i]) == 0 && beg)
        {
            beg = false;
        }
        // Пока длина слова в пределе допустимых значений - заполняем буфер слова
        if ((len_word < STR_LEN - 1) && (!beg))
            word[len_word++] = str[i]; 
    }
    if (len_word > 0)
        word[len_word] = '\0';
    else
        return ERR_NO_WORDS;
    del_end_spaces(word, len_word);
    strcpy(str, word);
    return OK;
}

// bool is_integer(char *str)
// {
//     // Если нет цифр - не число
//     if (strpbrk(str, DIGITS) == NULL)
//         return false;
//     for (size_t i = 0; str[i] != '\0'; i++)
//     {
//         // Если очередной элемент не цифра
//         if (str[i] < '0' || str[i] > '9')
//         {
//             // В целом числе кроме чисел может быть + или - на нулевом индексе
//             if (i != 0)
//                 return false;
//             else if (str[i] != '+' && str[i] != '-')
//                 return false;
//         }
//     }
//     return true;
// }

// bool is_integer_no_sign(char *str)
// {
//     for (size_t i = 0; str[i] != '\0'; i++)
//     {
//         // Если очередной элемент не цифра
//         if (str[i] < '0' || str[i] > '9')
//         {
//             return false;
//         }
//     }
//     return true;
// }

// bool is_integer_or_sign(char *str)
// {
//     for (size_t i = 0; str[i] != '\0'; i++)
//     {
//         // Если очередной элемент не цифра
//         if (str[i] < '0' || str[i] > '9')
//         {
//             // В целом числе кроме чисел может быть + или - на нулевом индексе
//             if (i != 0)
//                 return false;
//             else if (str[i] != '+' && str[i] != '-')
//                 return false;
//         }
//     }
//     return true;
// }

// bool is_real(char *str)
// {
//     // Если число целое, то оно и входит во множество вещественных
//     if (is_integer(str))
//         return true;
//     // Если число - просто знак, то не число
//     if (is_integer_or_sign(str))
//         return false;
//     // Если точек несколько - не число
//     if (strchr(str, '.') != strrchr(str, '.'))
//         return false;
//     // Заводим вспомогательную переменную parts, в которой хранятся 2 части числа - до и после точки
//     // Далее идет алгоритм разбития по точке
//     char parts[PARTS][STR_LEN];
//     char part[STR_LEN];
//     size_t len_part = 0;
//     size_t cur_part = 0;
//     for (size_t i = 0; str[i] != '\0'; i++)
//     {
//         if (str[i] == '.')
//         {
//             part[len_part] = '\0';
//             strcpy(parts[cur_part++], part);
//             len_part = 0;
//         }
//         else
//             part[len_part++] = str[i];
//     }
//     part[len_part] = '\0';
//     strcpy(parts[cur_part++], part);
//     len_part = 0;
//     // printf("PARTS: %s; %s", parts[0], parts[1]);
//     // Если часть до точки - целое число, а после - целое без знака, то число входит в область вещественных
//     // Цифры должны быть хотя бы по одну сторону от точки
//     if (strpbrk(parts[0], DIGITS) == NULL && isdigit(part[0]) == 0)
//         return false;
//     if (is_integer_or_sign(parts[0]) && is_integer_no_sign(parts[1]))
//         return true;
//     return false;
// }

// bool is_exponent(char *str)
// {
//     // Если число вещественное - то и выражено в экспоненциальной форме
//     if (is_real(str))
//         return true;
//     // Если букв е несколько (или букв Е), то это не число
//     if ((strchr(str, 'e') != strrchr(str, 'e')) || (strchr(str, 'E') != strrchr(str, 'E')))
//         return false;
//     // Заводим вспомогательную переменную parts, в которой хранятся 2 части числа - до и после точки
//     // Далее идет алгоритм разбития по символу split_symbol
//     char split_symbol = (strchr(str, 'e') != NULL) ? 'e' : 'E';
//     char parts[PARTS][STR_LEN];
//     char part[STR_LEN];
//     size_t len_part = 0;
//     size_t cur_part = 0;
//     for (size_t i = 0; str[i] != '\0'; i++)
//     {
//         if (str[i] == split_symbol)
//         {
//             part[len_part] = '\0';
//             strcpy(parts[cur_part++], part);
//             len_part = 0;
//         }
//         else
//             part[len_part++] = str[i];
//     }
//     part[len_part] = '\0';
//     strcpy(parts[cur_part++], part);
//     len_part = 0;
//     //printf("PARTS: %s; %s", parts[0], parts[1]);
//     // До и после буквы е(Е) обязаны быть цифры
//     if (parts[0][0] == '\0' || strlen(part) == 0)
//         return false;
//     // Часть до экспоненты должна быть вещественной, а после - целой
//     if (is_real(parts[0]) && is_integer(parts[1]))
//         return true;
//     return false;
// }

bool is_regex_found(char *str)
{
    if (*str == '+' || *str == '-')
        str++;
    bool any_digit = false;
    while (isdigit(*str))
    {
        any_digit = true;
        str++;
    }
    if (any_digit == false)
        if (!(*str == '.' && isdigit(*(str + 1))))
            return false;
    if (*str == '.')
        str++;
    while (isdigit(*str))
        str++;
    if (*str == 'e' || *str == 'E')
    {
        if (*(str + 1) == '\0')
            return false;
        str++;
        if (*str == '+' || *str == '-')
        {
            if (*(str + 1) == '\0')
                return false;
            str++;
        }
    }
    while (isdigit(*str))
        str++;
    if (*str == '\0')
        return true;
    return false;
}
