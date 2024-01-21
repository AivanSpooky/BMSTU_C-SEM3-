#include "node.h"

node_t *node_create(int value)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node)
    {
        new_node->data = value;
        new_node->next = NULL;
    }
    return new_node;
}

void node_free(node_t *node)
{
    free(node);
}