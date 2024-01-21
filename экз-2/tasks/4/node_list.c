#include "node_list.h"

int node_list_add(node_t **head, int a, int b, int c)
{
    node_t *new_node = node_create(a, b, c);
    if (!new_node)
        return ERR_MEM;
    if (*head == NULL)
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

void node_list_print(node_t **head)
{
    node_t *cur = *head;
    while (cur != NULL)
    {
        printf("%d %d %d \n", cur->a, cur->b, cur->c);
        cur = cur->next;
    }
}

void node_list_del(node_t **head)
{
    while (*head != NULL && ((*head)->b <= 0 || (*head)->c < 0))
    {
        node_t *temp = *head;
        *head = (*head)->next;
        node_free(temp);
    }

    node_t *cur = *head;
    node_t *prev = NULL;

    while (cur != NULL)
    {
        if (cur->b <= 0 || cur->c < 0)
        {
            prev->next = cur->next;
            node_t *temp = cur;
            cur = cur->next;
            node_free(temp);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}