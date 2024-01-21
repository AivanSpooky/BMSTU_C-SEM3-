/*
Задание:
На вход пользователь вводит строки, длины не больше 50 символов.
На их основе формируется список, конец ввода - строка "end".
Необходимо дописать справа от каждой строки "развернутую" следующую.
К последней строке приписать "развернутую первую строку".
Вывести каждую строку на отдельной строке.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node_list.h"

#define OK 0

int main(void)
{
    int rc = OK;
    char str[MAX_LEN + 1] = "defa";
    node_t *head = NULL;
    while (strcmp(str, "end") != 0)
    {
        rc = get_next_str(str);
        if (rc != OK)
        {
            node_list_free(&head);
            return rc;
        }
        if (strcmp(str, "end") == 0)
            break;
        rc = node_list_add(&head, str);
        if (rc != OK)
        {
            node_list_free(&head);
            return rc;
        }
    }
    if (rc == OK)
    {
        printf("\n");
        node_list_print(&head);
    }
    node_list_free(&head);
    return rc;
}