#ifndef NODE_LIST_H__
#define NODE_LIST_H__

#include <stdlib.h>
#include <string.h>
#include "node.h"

#define OK 0
#define ERR_IO 1
#define ERR_MEM 2
#define ERR_RANGE 3

int node_list_add(node_t **head, char *str);

void node_list_free(node_t **head);

//int node_list_merge(node_t **head);

void node_list_print(node_t **head);

#endif