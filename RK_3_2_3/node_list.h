#ifndef NODE_LIST_H__

#define NODE_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"

#define ARG_READ 1

node_t *node_list_read_from_file(FILE *f, bool *is_empty);

void node_list_print(node_t **head);

void node_list_add_elem_to_end(node_t **head, int value);

node_t *node_list_merge(node_t **l1, node_t **l2);

void node_list_free(node_t **head);

#endif