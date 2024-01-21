#ifndef NODE_H__
#define NODE_H__

#define MAX_LEN 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_OK 0
#define STR_ERR_IO 1
#define STR_ERR_LEN 2


typedef struct node {
    int a;
    int b;
    int c;
    struct node *next;
} node_t;

node_t *node_create(int a, int b, int c);

void node_free(node_t *node);

#endif