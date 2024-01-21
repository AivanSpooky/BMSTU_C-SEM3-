#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "node_io.h"
#include "node_default_funcs.h"
#include "node_task_funcs.h"

#include "err_codes.h"

/*
ЗАДАНИЕ.
На вход аргументов командной строки поступает файл, в котором на каждой строке написано среднее значение температуры за определенный день.
Температура хранится в виде вещественного числа с точностью до одной десятой. Необходимо вывести, присутсвует ли в файле значение температуры 0. 
Если присутсвует - на экран печатается "YES", иначе "NO".
Также необходимо вывести на экран в порядке понижения температуры все значения температур из файла, которые ниже 0.
Если таких значений не оказалось, необходимо вывести на экран сообщение "Not found!"
*/
int main(int argc, char **argv)
{
    // Проверка на введенные аргументы
    if (argc != 2)
    {
        return ERR_ARGS;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        return ERR_IO;

    int rc = OK;
    node_t *head = node_list_read_from_file(file, node_read_double);
    if (head == NULL)
        rc = ERR_READ;

    if (rc == OK)
    {
        double find_value = 0.0;
        if (find(head, &find_value, node_cmp_double) != NULL)
            printf("YES!\n");
        else
            printf("NO!\n");

        head = sort(head, node_cmp_double);
        head = reverse(head);
        while (*(double *)head->data > -EPS)
        {
            pop_front(&head);
        }
        node_print_data(head, node_print_double);
        node_list_free(&head);
    }
    fclose(file);
    return rc;
}