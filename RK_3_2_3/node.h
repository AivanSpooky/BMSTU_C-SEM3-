#ifndef NODE_H__

#define NODE_H__

#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node_t;

node_t *node_create(int value);

void node_free(node_t *node);

#endif