#include "node_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *node_create(int coefficient, int power)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL)
        return NULL;
    new_node->coefficient = coefficient;
    new_node->power = power;
    new_node->next = NULL;
    return new_node;
}

void node_free(node_t *node)
{
    free(node);
}
