#include "node_default_funcs.h"
#include <stdlib.h>
#include <stdbool.h>

#include <inttypes.h>

void node_list_free(node_t **head)
{
    node_t *current = *head;
    while (current != NULL)
    {
        node_t *next = current->next;
        node_free(current);
        current = next;
    }
    *head = NULL;
}

int node_list_is_empty(node_t *head)
{
    return head == NULL;
}

void node_list_push(node_t **head, int coefficient, int power)
{
    node_t *new_node = node_create(coefficient, power);
    if (new_node == NULL)
        return;
    if (node_list_is_empty(*head))
        *head = new_node;
    else
    {
        node_t *current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void node_list_pop_last(node_t **head)
{
    if (node_list_is_empty(*head))
        return;
    if ((*head)->next == NULL)
    {
        node_free(*head); 
        *head = NULL;
        return;
    }
    node_t *current = *head;
    while (current->next->next != NULL)
        current = current->next;
    node_free(current->next);
    current->next = NULL;
}

void node_list_pop_after(node_t *prev)
{
    if (prev == NULL || prev->next == NULL)
        return; // Нечего удалять
    node_t *temp = prev->next;
    prev->next = temp->next;
    node_free(temp);
}

void node_list_print(const node_t *head)
{
    const node_t *current = head;
    while (current != NULL)
    {
        int coefficient = current->coefficient;
        int power = current->power;
        printf("%d %d ", coefficient, power);
        current = current->next;
    }
    printf("L\n");
}

node_t *node_list_input()
{
    node_t *head = NULL;
    int rc = OK;
    int coefficient = 0;
    int power = INT32_MAX;
    while (rc == OK)
    {
        if (scanf("%d %d ", &coefficient, &power) != 2 * ARG_READ)
            rc = ERR_IO;
        node_list_push(&head, coefficient, power);
        if (power == 0)
            rc = ERR_IO;
    }
    if (rc == ERR_IO && head != NULL)
    {
        const node_t *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        if (current->power == 0)
            rc = OK;
    }
    if (rc != OK)
    {
        node_list_free(&head);
        head = NULL;
    }
    return head;
}
