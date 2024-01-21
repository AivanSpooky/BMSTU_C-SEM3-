#include "node_list.h"

int node_list_add(node_t **head, char *str)
{
    node_t *new_node = node_create(str);
    if (!new_node)
        return ERR_MEM;
    else if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        node_t *cur = *head;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new_node;
    }
    return OK;
}

void node_list_free(node_t **head)
{
    node_t *cur = *head;
    node_t *tmp;
    while (cur != NULL)
    {
        tmp = cur;
        cur = cur->next;
        node_free(tmp);
    }
}

// int node_list_merge(node_t **head)
// {
//     char *first_str = (*head)->str;
//     node_t *cur = *head;
//     while (cur != NULL)
//     {
//         size_t cur_len = strlen(cur->str);
//         size_t next_len = 0;
//         if (cur->next == NULL)
//             next_len = strlen(first_str);
//         size_t sum_len = cur_len + next_len;
//         if (sum_len > MAX_LEN)
//             return ERR_RANGE;
//         if (cur->next == NULL)
//             cur_str = first_str;
//         else
//             cur_str = cur->next->str;
//         char *reversed = malloc(strlen(cur_str) + 1);
//         strcpy(reversed, cur_str);
//         reverse_str(cur_str, reversed);
//         strcat(cur->str, cur_str);
//         free(reversed);
//     }
//     return OK;
// }

void node_list_print(node_t **head)
{
    node_t *cur = *head;
    if (cur->next != NULL)
        node_list_print(&(cur->next));
    printf("%s\n", cur->str);
}