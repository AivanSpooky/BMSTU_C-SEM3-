#include "node.h"

node_t *node_create(char *str)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node)
    {
        new_node->str = malloc(sizeof(char) * (MAX_LEN + 1));
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
        strcpy(new_node->str, str);
        new_node->next = NULL;
    }
    return new_node;
}

void node_free(node_t *node)
{
    free(node->str);
    free(node);
}

int get_next_str(char *str)
{
    char tmp[MAX_LEN + 2];
    if (!fgets(tmp, MAX_LEN + 2, stdin))
        return STR_ERR_IO;
    size_t len = strlen(tmp);
    if (tmp[len - 1] == '\n')
        tmp[--len] = '\0';
    if (!len || len > MAX_LEN - 1)
        return STR_ERR_LEN;
    strcpy(str, tmp);
    return STR_OK;
}

void reverse_str(char *str, char *buf)
{
    size_t len = strlen(str);
    for (int i = len - 1; i >= 0; i--)
    {
        buf[len - i - 1] = str[i];
    }
}