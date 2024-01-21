#ifndef NODE_LIST_H__

#define NODE_LIST_H__

#include <stdio.h>
#include "node.h"
#include <stdbool.h>

// void node_list_add(node_t **head, char *str);
void node_list_add(node_t **head, int num);

node_t *node_list_read(FILE *f, bool *is_f_empty);

node_t *objedinenie(node_t *l1, node_t *l2);

node_t *peresechenie(node_t *l1, node_t *l2);
// int node_list_merge_every_second(node_t **head);
void sortLinkedList(node_t **head);

void node_list_free(node_t **head);

void node_list_print(node_t **head);

#endif