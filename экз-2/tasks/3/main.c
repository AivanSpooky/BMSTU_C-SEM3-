#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node_list.h"

#define OK 0

int main(void)
{
    int rc = OK;
    node_t *l = NULL;
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) == 3)
    {
        rc = node_list_add(&l, a, b, c);
        if (rc != OK)
            break;
    }
    if (rc == OK)
    {
        node_list_del(&l);
        node_list_print(&l);
    }
    node_list_free(&l);
    return rc;
}