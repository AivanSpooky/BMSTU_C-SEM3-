#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node_list.h"

#define OK 0

int main(void)
{
    int rc = OK;
    node_t *l1 = NULL;
    node_t *l2 = NULL;
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) == 3)
    {
        if (b == c)
            rc = node_list_add(&l2, a, b, c);
        else
            rc = node_list_add(&l1, a, b, c);
        if (rc != OK)
            break;
    }
    node_list_print(&l1);
    node_list_print(&l2);
    if (rc == OK)
    {
        node_t *l3 = NULL;
        node_list_cat(&l3, &l2);
        node_list_cat(&l3, &l1);
        node_list_print(&l3);
        node_list_free(&l3);
    }
    node_list_free(&l1);
    node_list_free(&l2);
    return rc;
}