#include "node.h"

// node_t *node_create(char *str)
// {
//     node_t *node = malloc(sizeof(node_t));
//     if (node)
//     {
//         node->str = malloc(sizeof(char) * 129);
//         if (!node->str)
//         {
//             free(node);
//             node = NULL;
//         }
//         else
//         {
//             strcpy(node->str, str);
//             node->next = NULL;
//         }
//     }
//     return node;
// }

node_t *node_create(int num)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->data = num;
        node->next = NULL;
    }
    return node;
}

void node_free(node_t **node)
{
    free(*node);
}
