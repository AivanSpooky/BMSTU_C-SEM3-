#include <stdio.h>
#include "node_list.h"
#include "err_codes.h"

#define ARGS_CNT 3

int main(int argc, char **argv)
{
    if (argc != ARGS_CNT)
        return ERR_ARGS;

    FILE *f1 = fopen(argv[1], "r");
    if (!f1)
        return ERR_OPEN_FILE;
    FILE *f2 = fopen(argv[2], "r");
    if (!f2)
    {
        fclose(f1);
        return ERR_OPEN_FILE;
    }

    bool is_empty;
    int rc = OK;
    node_t *l1 = NULL;
    node_t *l2 = NULL;

    l1 = node_list_read_from_file(f1, &is_empty);
    if (l1 == NULL && !is_empty)
    {
        rc = ERR_FILE_CORRUPTED_DATA;
    }
    if (rc == OK)
    {
        l2 = node_list_read_from_file(f2, &is_empty);
        if (l2 == NULL && !is_empty)
        {
            rc = ERR_FILE_CORRUPTED_DATA;
        }
    }
    fclose(f1);
    fclose(f2);
    if (rc == OK)
    {
        node_t *res = node_list_merge(&l1, &l2);
        node_list_print(&res);

        node_list_free(&res);
    }
    else
    {
        node_list_free(&l1);
        node_list_free(&l2);
    }
    return rc;
}