#include "node_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *node_create(void *data, size_t data_size)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL)
        return NULL;
    new_node->data = malloc(data_size);
    if (new_node->data == NULL)
    {
        free(new_node);
        return NULL;
    }
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    return new_node;
}

void node_free(node_t *node)
{
    free(node->data);
    free(node);
}

int node_cmp_int(const void *l, const void *r)
{
    const int *pl = l;
    const int *pr = r;
    return *pl - *pr;
}

int node_cmp_double(const void *l, const void *r)
{
    const double *pl = l;
    const double *pr = r;
    double diff = *pl - *pr;
    if (fabs(diff) < EPS)
        return 0;
    else if (diff < 0)
        return -1;
    else
        return 1;
}

int node_cmp_str(const void *l, const void *r)
{
    const char *pl = l;
    const char *pr = r;
    return strcmp(pl, pr);
}
