#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "associative_array.h"

#define CAPACITY 100
#define NOT_FOUND -1

typedef struct
{
    char *key;
    int value;
} pair_t;

typedef struct assoc_array_type
{
    size_t capacity;
    size_t size;
    pair_t *data;
} assoc_array_type;

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(assoc_array_type));
    if (!arr)
        return NULL;
    arr->data = malloc(sizeof(pair_t) * CAPACITY);
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->capacity = CAPACITY;
    arr->size = 0;
    
    return arr;
}

void assoc_array_data_elem_clean(assoc_array_t arr, size_t i)
{
    free(arr->data[i].key);
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || !(*arr))
        return;

    for (size_t i = 0; i < (*arr)->size; i++)
        assoc_array_data_elem_clean(*arr, i);
    
    free((*arr)->data);
    free(*arr);
    *arr = NULL;
    arr = NULL;
}

int find_key_index(const assoc_array_t arr, const char *key)
{
    for (size_t i = 0; i < arr->size; i++)
        if (strcmp(arr->data[i].key, key) == 0)
            return (int)i;

    return NOT_FOUND;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !arr->data || !key || strlen(key) == 0)
        return (assoc_array_error_t)ASSOC_ARRAY_INVALID_PARAM;
    if (find_key_index(arr, key) != NOT_FOUND)
        return ASSOC_ARRAY_KEY_EXISTS;
    if (arr->size >= arr->capacity)
    {
        size_t new_capacity = arr->capacity * 2;
        pair_t *new_data = realloc(arr->data, sizeof(pair_t) * new_capacity);
        if (!new_data)
            return ASSOC_ARRAY_MEM;

        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    char *tmp = strdup(key);
    if (!tmp)
        return ASSOC_ARRAY_MEM;
    arr->data[arr->size].key = tmp;
    arr->data[arr->size].value = num;
    arr->size++;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !arr->data || !key || !num || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int index = find_key_index(arr, key);
    if (index == NOT_FOUND)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &(arr->data[index].value);
    return ASSOC_ARRAY_OK;
}

void assoc_array_swap_elems(pair_t *p1, pair_t *p2)
{
    pair_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !arr->data || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int index = find_key_index(arr, key);
    if (index == NOT_FOUND)
        return ASSOC_ARRAY_NOT_FOUND;

    assoc_array_swap_elems(&arr->data[index], &arr->data[arr->size - 1]);
    assoc_array_data_elem_clean(arr, arr->size - 1);
    arr->size--;
    
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = arr->size - 1; i >= 0; i--)
    {
        assoc_array_data_elem_clean(arr, i);
    }
    arr->size = 0;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_cmp_values(const assoc_array_t arr, int *values, size_t cnt)
{
    if (cnt != arr->size)
        return ASSOC_ARRAY_INVALID_PARAM;
    for (size_t i = 0; i < arr->size; i++)
    {
        //printf("%d - %d\n", arr->data[i].value, values[i]);
        if (arr->data[i].value != values[i])
            return ASSOC_ARRAY_NOT_FOUND;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !arr->data || !action || !param)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
        action(arr->data[i].key, &(arr->data[i].value), param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !arr->data || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    int min_index = 0;
    for (size_t i = 1; i < arr->size; i++)
        if (strcmp(arr->data[i].key, arr->data[min_index].key) < 0)
            min_index = i;


    *num = &(arr->data[min_index].value);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !arr->data || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    int max_index = 0;
    for (size_t i = 1; i < arr->size; i++)
        if (strcmp(arr->data[i].key, arr->data[max_index].key) > 0)
            max_index = i;

    *num = &(arr->data[max_index].value);
    return ASSOC_ARRAY_OK;
}