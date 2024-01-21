#include "node_default_funcs.h"
#include <stdlib.h>

void node_list_free(node_t **head)
{
    node_t *current = *head;
    while (current != NULL)
    {
        node_t *next = current->next;
        node_free(current);
        current = next;
    }
    *head = NULL;
}

int node_list_is_empty(node_t *head)
{
    return head == NULL;
}

void node_list_push(node_t **head, void *data, size_t data_size)
{
    node_t *new_node = node_create(data, data_size);
    if (new_node == NULL)
        return;
    if (node_list_is_empty(*head))
        *head = new_node;
    else
    {
        node_t *current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void node_print_data(const node_t *head, print_data_t print_func)
{
    print_func(head);
}

void node_print_int(const node_t *head)
{
    const node_t *current = head;
    printf("List:\n");
    while (current != NULL)
    {
        int *num = current->data;
        printf("%d ", *num);
        current = current->next;
    }
    printf("\n");
}

void node_print_double(const node_t *head)
{
    const node_t *current = head;
    printf("List:\n");
    while (current != NULL)
    {
        double *num = current->data;
        printf("%lf ", *num);
        current = current->next;
    }
    printf("\n");
}

void node_print_str(const node_t *head)
{
    const node_t *current = head;
    printf("List:\n");
    while (current != NULL)
    {
        const char *num = current->data;
        printf("%s ", num);
        current = current->next;
    }
    printf("\n");
}

node_t *node_list_read_from_file(FILE *file, read_data_t read_func)
{
    node_t *head = NULL;
    // Чтение данных из файла и добавление их в список
    int rc = OK;
    double *value;
    size_t cnt = 0;
    while (rc == OK)
    {
        value = read_func(file);
        // printf("a%lf\n", *value);
        if (value == NULL)
            rc = ERR_DATA;
        else
        {
            cnt++;
            node_list_push(&head, value, sizeof(double));
            free(value);
        }
    }
    if (cnt == 0)
        return NULL;
    if (feof(file) && rc == ERR_DATA && cnt > 0)
    {
        (void) head;
    }
    else
    {
        node_list_free(&head);
        head = NULL;
    }
    return head;
}

void *node_read_int(FILE *file)
{
    int *num = malloc(sizeof(int));
    if (!num)
        return NULL;
    if (fscanf(file, "%d\n", num) != ARG_READ)
    {
        free(num);
        return NULL;
    }
    return num;
}

void *node_read_double(FILE *file)
{
    double *num = malloc(sizeof(double));
    if (!num)
        return NULL;
    if (fscanf(file, "%lf\n", num) != ARG_READ)
    {
        free(num);
        return NULL;
    }
    return num;
}

void *node_read_str(FILE *file)
{
    char *name = NULL;
    size_t buf_size = 0;
    ssize_t read;

    int rc = OK;
    read = getline(&name, &buf_size, file);
    if (read == STRING_IO_ERR)
    {
        rc = ERR_EMPTY;
    }
    else if (read == 1)
    {
        free(name);
        rc = ERR_DATA;
    }
    if (rc == OK)
    {
        if (name[read - 1] == '\n')
        {
            name[read - 1] = '\0';
        }
        return name;
    }
    return NULL;
}
