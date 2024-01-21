#include "node_list.h"
#include <string.h>

// void node_list_add(node_t **head, char *str)
// {
//     node_t *new_node = node_create(str);
//     if (*head == NULL)
//     {
//         *head = new_node;
//     }
//     else
//     {
//         node_t *cur = *head;
//         while (cur->next != NULL)
//             cur = cur->next;
//         cur->next = new_node;
//     }
// }

void node_list_add(node_t **head, int num)
{
    node_t *new_node = node_create(num);
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        node_t *cur = *head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = new_node;
    }
}

void node_list_free(node_t **head)
{
    node_t *cur = *head;
    while (cur != NULL)
    {
        node_t *temp = cur;
        cur = cur->next;
        node_free(&temp);
    }
}

// node_t *node_list_read(FILE *f, bool *is_f_empty)
// {
//     node_t *head = NULL;
//     char tmp[MAX_LEN + 2];
//     *is_f_empty = true;
//     while (fgets(tmp, MAX_LEN + 2, f))
//     {
//         is_f_empty = false;
//         size_t len = strlen(tmp);
//         if (tmp[len - 1] == '\n')
//             tmp[--len] = '\0';
//         if (!len && len > MAX_LEN)
//         {
//             node_list_free(&head);
//             return NULL;
//         }
//         else
//         {
//             node_list_add(&head, tmp);
//         }
//     }
//     if (feof(f) || is_f_empty)
//     {
//         return head;
//     }
//     node_list_free(&head);
//     return NULL;
// }

node_t *node_list_read(FILE *f, bool *is_f_empty)
{
    node_t *head = NULL;
    *is_f_empty = true;
    int tmp;
    while (fscanf(f, "%d", &tmp) == 1)
    {
        node_list_add(&head, tmp);
    }
    if (feof(f) || is_f_empty)
    {
        return head;
    }
    node_list_free(&head);
    return NULL;
}

static void swap(int *p1, int *p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp; 
}

void sortLinkedList(node_t **head)
{
    node_t *current = *head, *index = NULL;

    if (*head == NULL)
        return;
    else
    {
        while (current != NULL)
        {
            index = current->next;
            while (index != NULL)
            {
                if (current->data > index->data)
                {
                    swap(&current->data, &index->data);
                }
                index = index->next;
            }
            current = current->next;
        }   
    }
}

bool is_elem_in_list(node_t *l, int elem)
{
    node_t *cur = l;
    while (cur != NULL)
    {
        if (cur->data == elem)
            return true;
        cur = cur->next;
    }
    return false;
}

node_t *objedinenie(node_t *l1, node_t *l2)
{
    node_t *head = NULL;
    node_t *tail = NULL;
    node_t *cur = l1;
    while (cur != NULL)
    {
        if (!is_elem_in_list(head, cur->data))
        {
            node_t *tmp = node_create(cur->data);
            if (head == NULL)
            {
                head = tmp;
                tail = tmp;
            }
            else
            {
                tail->next = tmp;
                tail = tmp;
            }      
        }
        cur = cur->next;
    }
    //node_list_print(&head);
    cur = l2;
    while (cur != NULL)
    {
        if (!is_elem_in_list(head, cur->data))
        {
            node_t *tmp = node_create(cur->data);
            if (head == NULL)
            {
                head = tmp;
                tail = tmp;
            }
            else
            {
                tail->next = tmp;
                tail = tmp;
            }      
        }
        cur = cur->next;
    }
    return head;
}

node_t *peresechenie(node_t *l1, node_t *l2)
{
    node_t *head = NULL;
    node_t *tail = NULL;
    node_t *cur = l1;
    while (cur != NULL)
    {
        if (is_elem_in_list(l2, cur->data))
        {
            node_t *tmp = node_create(cur->data);
            if (head == NULL)
            {
                head = tmp;
                tail = tmp;
            }
            else
            {
                tail->next = tmp;
                tail = tmp;
            }      
        }
        cur = cur->next;
    }
    return head;
}

// int node_list_merge_every_second(node_t **head)
// {
//     node_t *cur = *head;
//     node_t *prev = NULL;
//     int counter = 1;
//     while (cur != NULL)
//     {
//         if (counter % 2 == 0)
//         {
//             // kowmar
//             if (strlen(prev->str) + strlen(cur->str) + 1 > MAX_LEN)
//                 return 1;
//             strcat(prev->str, " ");
//             strcat(prev->str, cur->str);
//             prev->next = cur->next;
//             prev = cur;
//             cur = cur->next;
//             node_free(&prev);
//         }
//         else
//         {
//             prev = cur;
//             cur = cur->next;
//         }
//         counter++;
//     }
//     return 0;
// }

void node_list_print(node_t **head)
{
    node_t *cur = *head;
    if (cur == NULL)
        printf("Empty list\n");
    else
    {
        printf("list: ");
        while (cur != NULL)
        {
            printf("%d ", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
}