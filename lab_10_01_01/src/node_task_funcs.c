#include "node_task_funcs.h"

node_t *find(node_t *head, const void *data, cmp_t comparator)
{
    node_t *current = head;
    while (current != NULL)
    {
        if (comparator(current->data, data) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void *pop_front(node_t **head)
{
    if (head == NULL || node_list_is_empty(*head))
        return NULL;
    node_t *temp = *head;
    void *data = temp->data;
    *head = (*head)->next;
    free(temp);
    return data;
}

node_t *reverse(node_t *head)
{
    node_t *prev = NULL;
    node_t *current = head;
    node_t *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void sorted_insert(node_t **head, node_t *element, cmp_t comparator)
{
    if (*head == NULL || comparator((*head)->data, element->data) > 0)
    {
        element->next = *head;
        *head = element;
    }
    else
    {
        node_t *current = *head;
        while (current->next != NULL && comparator(current->next->data, element->data) < 0)
            current = current->next;
        element->next = current->next;
        current->next = element;
    }
}

node_t *sort(node_t *head, cmp_t comparator)
{
    node_t *sorted = NULL;
    node_t *current = head;
    while (current != NULL)
    {
        node_t *next = current->next;
        sorted_insert(&sorted, current, comparator);
        current = next;
    }
    return sorted;
}
