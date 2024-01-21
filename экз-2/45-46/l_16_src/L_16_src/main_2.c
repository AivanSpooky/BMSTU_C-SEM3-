#include <stdlib.h>
#include <stdio.h>
#include "list.h"


struct data
{
    int num;

    struct list_head list;
};


int main(void)
{
    //
    // Определение переменной для "адресации" списка
    //

    struct data num_list;

    INIT_LIST_HEAD(&num_list.list);

    //
    // Добавление элементов в список
    //

    struct data *item;

    for (int i = 0; i < 10; i++)
    {
        // 1. Выделение памяти для данных
        item = malloc(sizeof(*item));
        if (!item)
            break;

        // 2. Инициализация данных

        item->num = i;

        INIT_LIST_HEAD(&item->list);
        // Этот "вызов" можно опустить, потому что поля next и prev 
        // инициализируются в функции list_add

        // 3. Добавление нового элемента item к списку элементов внутри num_list
        list_add(&(item->list), &num_list.list);

        // Можно было бы использовать и list_add_tail
    }

    //
    // Обработка (печать) элементов списка
    //

    struct list_head *iter;

    list_for_each(iter, &num_list.list)
    {
        item = list_entry(iter, struct data, list);

        printf("[LIST] %d\n", item->num);
    }

    printf("\n");

    list_for_each_entry(item, &num_list.list, list)
        printf("[LIST] %d\n", item->num);

    printf("\n");

    //
    // Освобождение
    //

    struct list_head *iter_safe;

    list_for_each_safe(iter, iter_safe, &num_list.list)
    {
        item = list_entry(iter, struct data, list);
        // Удаляем элемент списка
        list_del(iter);

        free(item);
    }

    return 0;
}
