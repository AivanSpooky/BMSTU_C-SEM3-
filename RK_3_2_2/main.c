#include <stdio.h>
#include <stdbool.h>

#include "node.h"
#include "node_list.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 3;
    FILE *f1 = fopen(argv[1], "r");
    if (!f1)
        return 4;
    FILE *f2 = fopen(argv[2], "r");
    if (!f2)
    {
        fclose(f1);
        return 4;
    }
    bool flag = false;
    node_t *l1 = node_list_read(f1, &flag);
    node_t *l2 = node_list_read(f2, &flag);
    fclose(f1);
    fclose(f2);
    int rc = 0;
    node_t *ob = objedinenie(l1, l2);
    node_t *pe = peresechenie(l1, l2);
    node_list_print(&ob);
    node_list_print(&pe);


    node_list_free(&ob);
    node_list_free(&pe);
    node_list_free(&l1);
    node_list_free(&l2);
    // if (head == NULL && flag == false)
    // {
    //     node_list_free(&head);
    //     rc = 10;
    // }
    // else
    // {
    //     rc = node_list_merge_every_second(&head);
    //     if (rc == 0)
    //         node_list_print(&head);
    //     node_list_free(&head);
    // }
    return rc;
}