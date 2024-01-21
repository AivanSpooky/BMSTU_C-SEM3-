#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

#include "err_codes.h"

int main(void)
{
    int rc = OK;
    char key_word[MAX_WORD_LEN + 1];
    rc = input_key_word(key_word);
    if (rc != OK)
        return rc;
    node_t *head = NULL;
    if (strcmp(key_word, KEY_VAL) == 0)
    {
        head = node_list_input();
        if (head == NULL)
            return ERR_DATA;
        int a;
        if (scanf("%d", &a) != ARG_READ)
            rc = ERR_IO;
        if (rc == OK)
        {
            int res = node_list_calc_val(head, a);
            printf("%d\n", res);
        }
    }
    else if (strcmp(key_word, KEY_DDX) == 0)
    {
        head = node_list_input();
        if (head == NULL)
            return ERR_DATA;
        node_list_calc_ddx(head);
        node_list_print(head);
    }
    else if (strcmp(key_word, KEY_SUM) == 0)
    {
        head = node_list_input();
        if (head == NULL)
            return ERR_DATA;
        node_t *second = node_list_input();
        if (second == NULL)
            rc = ERR_DATA;
        if (rc == OK)
        {
            node_t *result = node_list_add_lists(head, second);
            node_list_print(result);
            node_list_free(&second);
            node_list_free(&result);
        }
    }
    else if (strcmp(key_word, KEY_DVD) == 0)
    {
        head = node_list_input();
        if (head == NULL)
            return ERR_DATA;
        node_t *even = NULL;
        node_t *odd = NULL;
        node_list_split_lists(head, &even, &odd);
        node_list_print(even);
        node_list_print(odd);
        node_list_free(&even);
        node_list_free(&odd);
    }
    else
    {
        rc = ERR_ARGS;
        return rc;
    }
    node_list_free(&head);
    return rc;
}
