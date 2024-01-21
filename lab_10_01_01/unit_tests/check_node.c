#include "check_node.h"

int ck_assert_node_list_eq(const node_t *l, const node_t *r, cmp_t comparator)
{
    int eq = UNIT_OK;
    const node_t *cl = l;
    const node_t *cr = r;
    while (cl != NULL || cr != NULL)
    {
        if (comparator(cl->data, cr->data) != 0)
        {
            eq = UNIT_ERR_DATA_NOT_EQUAL;
        }
        cl = cl->next;
        cr = cr->next;
    }
    if (cl == NULL && cr == NULL && eq == UNIT_OK)
        eq = UNIT_OK;
    else if (eq != UNIT_ERR_DATA_NOT_EQUAL)
        eq = UNIT_ERR_LENGHT_NOT_EQUAL;
    return eq;
}

void node_list_create_from_array(node_t **head, void *arr, size_t size, size_t data_size)
{
    char *pcur = (char *)arr;
    for (size_t i = 0; i < size; i++)
    {
        node_list_push(head, pcur, data_size);
        pcur += data_size;
    }
}
