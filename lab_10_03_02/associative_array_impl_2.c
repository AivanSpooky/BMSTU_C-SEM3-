#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "associative_array.h"


typedef struct node_t
{
    char *key;
    int value;
    struct node_t *next;
} node_t;

typedef struct assoc_array_type
{
    node_t *head;
} assoc_array_type;

void assoc_array_node_key_free(node_t *node)
{
    free(node->key);
}

void assoc_array_node_free(node_t *node)
{
    free(node);
}

bool is_list_empty(assoc_array_t arr)
{
    return (arr == NULL);
}

bool is_node_empty(node_t *node)
{
    return (node == NULL);
}

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(assoc_array_type));
    if (is_list_empty(arr))
        return NULL;
    arr->head = NULL;
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || is_list_empty(*arr))
        return;

    node_t *current = (*arr)->head;
    while (!is_node_empty(current))
    {
        node_t *temp = current;
        current = current->next;
        assoc_array_node_key_free(temp);
        assoc_array_node_free(temp);
    }
    free(*arr);
    *arr = NULL;
    arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (is_list_empty(arr) || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;
    while (!is_node_empty(current))
    {
        if (strcmp(current->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;

        current = current->next;
    }

    node_t *newnode_t = malloc(sizeof(node_t));
    if (!newnode_t)
        return ASSOC_ARRAY_MEM;

    char *tmp = strdup(key);
    if (!tmp)
        return ASSOC_ARRAY_MEM;
    newnode_t->key = tmp;
    newnode_t->value = num;
    newnode_t->next = arr->head;
    arr->head = newnode_t;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (is_list_empty(arr) || !key || strlen(key) == 0 || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;
    while (!is_node_empty(current))
    {
        if (strcmp(current->key, key) == 0)
        {
            *num = &(current->value);
            return ASSOC_ARRAY_OK;
        }
        current = current->next;
    }
    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (is_list_empty(arr) || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;
    node_t *prev = NULL;
    while (!is_node_empty(current))
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                arr->head = current->next;
    
            assoc_array_node_key_free(current);
            assoc_array_node_free(current);
            return ASSOC_ARRAY_OK;
        }
        prev = current;
        current = current->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (is_list_empty(arr))
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;
    while (!is_node_empty(current))
    {
        node_t *temp = current;
        current = current->next;
        assoc_array_node_key_free(temp);
        assoc_array_node_free(temp);
    }
    arr->head = NULL;

    return ASSOC_ARRAY_OK;
}

size_t find_size(const assoc_array_t arr)
{
    size_t cnt = 0;
    node_t *current = arr->head;
    while (!is_node_empty(current))
    {
        cnt++;
        current = current->next;
    }
    return cnt;
}

assoc_array_error_t assoc_array_cmp_values(const assoc_array_t arr, int *values, size_t cnt)
{
    if (cnt != find_size(arr))
        return ASSOC_ARRAY_INVALID_PARAM;
    node_t *current = arr->head;
    size_t i = cnt - 1;
    while (!is_node_empty(current))
    {
        //printf("%d - %d\n", current->value, values[i]);
        if (current->value != values[i])
            return ASSOC_ARRAY_NOT_FOUND;
        current = current->next;
        i--;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (is_list_empty(arr) || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;
    while (!is_node_empty(current))
    {
        action(current->key, &(current->value), param);
        current = current->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (is_list_empty(arr) || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (is_node_empty(arr->head))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *current = arr->head;
    int *min_value = &current->value;
    char *min_key = current->key;
    while (!is_node_empty(current))
    {
        //printf("%d\n", current->value);
        if (strcmp(current->key, min_key) < 0)
        {
            min_value = &current->value;
            min_key = current->key;
        }

        current = current->next;
    }

    *num = min_value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (is_list_empty(arr) || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (is_node_empty(arr->head))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *current = arr->head;
    int *max_value = &current->value;
    char *max_key = current->key;
    while (!is_node_empty(current))
    {
        if (strcmp(current->key, max_key) > 0)
        {
            max_value = &current->value;
            max_key = current->key;
        }

        current = current->next;
    }

    *num = max_value;

    return ASSOC_ARRAY_OK;
}
