#include "node_list.h"

node_t *node_list_read_from_file(FILE *f, bool *is_empty)
{
    node_t *head = NULL;
    int value;
    *is_empty = true;
    while (fscanf(f, "%d", &value) == ARG_READ)
    {
        *is_empty = false;
        node_list_add_elem_to_end(&head, value);
    }
    if (feof(f) || *is_empty)
        return head;
    node_list_free(&head);
    return NULL;
}

void node_list_print(node_t **head)
{
    node_t *current = *head;
    if (current == NULL)
        printf("Empty list");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void node_list_add_elem_to_end(node_t **head, int value)
{
    node_t *new_node = node_create(value);
    node_t *cur = *head;
    if (cur == NULL)
        *head = new_node;
    else
    {
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new_node;
    }      
}

// Вместо добавления элемента со значением cur_value 
// реализовано создание узла со значением cur_value 
// и добавление через простой проход по вспомогательному указателю
node_t *node_list_merge(node_t **l1, node_t **l2)
{
    node_t *head = NULL;
    node_t **cur_res = &head;
    node_t *cur_l1 = *l1;
    node_t *cur_l2 = *l2;

    while (cur_l1 != NULL || cur_l2 != NULL)
    {
        if (cur_l1 == NULL && cur_l2 != NULL)
        {
            *cur_res = cur_l2;
            cur_l2 = cur_l2->next;
        }
        else if (cur_l2 == NULL && cur_l1 != NULL)
        {
            *cur_res = cur_l1;
            cur_l1 = cur_l1->next;
        }
        else
        {
            if (cur_l1->data < cur_l2->data)
            {
                *cur_res = cur_l1;
                cur_l1 = cur_l1->next;
            }
            else
            {
                *cur_res = cur_l2;
                cur_l2 = cur_l2->next;
            }
        }
        cur_res = &((*cur_res)->next);
    }
    return head;
}

void node_list_free(node_t **head)
{
    node_t *current = *head;
    while (current != NULL)
    {
        node_t *next_node = current->next;
        node_free(current);
        current = next_node;
    }
}