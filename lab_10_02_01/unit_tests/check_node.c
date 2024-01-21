#include "check_node.h"

int ck_assert_node_list_eq(const node_t *l, const node_t *r)
{
    int eq = UNIT_OK;
    const node_t *cl = l;
    const node_t *cr = r;
    while (eq == UNIT_OK && (cl != NULL || cr != NULL))
    {
        if (cl->coefficient != cr->coefficient || cl->power != cr->power)
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

void node_list_create_from_array(node_t **head, int *coef, int *pow, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        node_list_push(head, coef[i], pow[i]);
    }
}
