#include "node.h"

node_t *node_create(int a, int b, int c)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node)
    {
        new_node->a = a;
        new_node->b = b;
        new_node->c = c;
        new_node->next = NULL;
    }
    return new_node;
}

void node_free(node_t *node)
{
    free(node);
}
