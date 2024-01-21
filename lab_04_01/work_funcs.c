#include "work_funcs.h"

bool find_symbol(const char *str, int ch, size_t *i)
{
    (*i) = 0;
    while (str[(*i)] != '\0')
    {
        if (str[(*i)] == ch)
            return true;
        (*i)++;
    }
    return false;
}

char *my_strpbrk(const char *str1, const char *str2)
{
    size_t i = 0;
    while (str1[i] != '\0')
    {
        // size_t j = 0;
        // while (str2[j] != '\0')
        // {
        //     if (str1[i] == str2[j])
        //         return (char*)&(str1[i]);
        //     j++;
        // }
        // i++;
        size_t index = 0;
        if (find_symbol(str2, str1[i], &index))
            return (char*)&(str1[i]);
        i++;
    }
    return NULL;
}

size_t my_strspn(const char *str1, const char *str2)
{
    size_t n = 0;
    size_t i = 0;
    while (str1[i] != '\0')
    {
        // size_t j = 0;
        // while (str2[j] != '\0' && str1[i] != str2[j])
        // {
        //     j++;
        // }
        size_t index = 0;
        find_symbol(str2, str1[i], &index);

        if (str1[i] != str2[index])
        {
            return n;
        }
        n++;
        i++;
    }
    return n;
}

size_t my_strcspn(const char *str1, const char *str2)
{
    size_t n = 0;
    size_t i = 0;
    while (str1[i] != '\0')
    {
        // size_t j = 0;
        // while (str2[j] != '\0')
        // {
        //     if (str1[i] == str2[j])
        //         return n;
        //     j++;
        // }
        size_t index = 0;
        if (find_symbol(str2, str1[i], &index))
            return n;
        n++;
        i++;
    }
    return n;
}

char *my_strchr(const char *str, int ch)
{
    // size_t i = 0;
    // while (str[i] != '\0')
    // {
    //     if (str[i] == ch)
    //         return (char*)&str[i];
    //     i++;
    // }
    size_t index = 0;
    if (find_symbol(str, ch, &index))
        return (char*)&str[index];
    if (ch == '\0')
        return (char*)&str[index];
    return NULL;
}

char *my_strrchr(const char *str, int ch)
{
    // В данной функции не получится заменить цикл на find_symbol,
    // так как strrchr предполагает поиск элемента с конца, а не с начала
    size_t i = 0;
    char *p = NULL;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
            p = (char*)&str[i];
        i++;
    }
    // char *p = NULL;
    // for (size_t i = siz)
    // size_t index = 0;
    // if (find_symbol(str, ch, &index))
    // {
    //     p = (char*)&str[index];
    // }
    if (ch == '\0')
        return (char*)&str[i];
    return p;
}

