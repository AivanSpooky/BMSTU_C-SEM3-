#ifndef NODE_H__

#define NODE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 127

typedef struct node {
    int data;
    struct node *next;
} node_t;

// node_t *node_create(char *str);
node_t *node_create(int num);

void node_free(node_t **node);



#endif