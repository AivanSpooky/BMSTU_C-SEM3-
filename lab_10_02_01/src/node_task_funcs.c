#include "node_task_funcs.h"
#include <string.h>
#include <stdbool.h>

int input_key_word(char *word)
{
    size_t len;
    if (!fgets(word, MAX_WORD_LEN + 2, stdin))
    {
        return ERR_EMPTY;
    }
    len = strlen(word);
    if (word[len - 1] == '\n')
        word[--len] = '\0';
    if (!len)
        return ERR_IO;
    if (len > MAX_WORD_LEN)
        return ERR_RANGE;
    return OK;
}

int node_list_calc_val(node_t *head, int a)
{
    int result = 0;
    node_t *current = head;
    while (current != NULL)
    {
        result += current->coefficient * (int)pow(a, current->power);
        current = current->next;
    }
    return result;
}

void node_list_calc_ddx(node_t *head)
{
    node_t *current = head;
    node_t *prev = NULL;
    bool went_through_loop = false;
    while (current != NULL)
    {
        current->coefficient *= current->power;
        current->power--;
        // Если степень получилась меньше 0
        if (current->power < 0)
        {
            // Если полином состоит из одного элемента степени 0 - его производная 0.
            // Если в полиноме есть элемент степени больше, чем 0 - в ответе не выводим производную от свободного члена (0)
            if (!went_through_loop)
            {
                current->power = 0;
                current = current->next;
            }
            else
            {
                current = current->next;
                node_list_pop_after(prev);
            }
        }
        else
        {
            prev = current;
            current = current->next;
        }
        went_through_loop = true;
    }
}

node_t *node_list_add_lists(node_t *poly1, node_t *poly2)
{
    node_t *result = NULL;
    while (poly1 != NULL && poly2 != NULL)
    {
        if (poly1->power > poly2->power)
        {
            // Добавляем узел из poly1 в результат
            node_list_push(&result, poly1->coefficient, poly1->power);
            poly1 = poly1->next;
        }
        else if (poly1->power < poly2->power)
        {
            // Добавляем узел из poly2 в результат
            node_list_push(&result, poly2->coefficient, poly2->power);
            poly2 = poly2->next;
        }
        else
        {
            // Складываем коэффициенты и добавляем узел с результатом
            node_list_push(&result, poly1->coefficient + poly2->coefficient, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    // Добавляем оставшиеся узлы из poly1 и poly2 в результат, если они есть
    if (poly1 == NULL)
    {
        node_t *current = poly2;
        while (current != NULL)
        {
            node_list_push(&result, current->coefficient, current->power);
            current = current->next;
        }
    }
    else if (poly2 == NULL)
    {
        node_t *current = poly1;
        while (current != NULL)
        {
            node_list_push(&result, current->coefficient, current->power);
            current = current->next;
        }
    }
    return result;
}

void node_list_split_lists(node_t *head, node_t **even, node_t **odd)
{
    node_t *current = head;
    while (current != NULL)
    {
        if (current->power % 2 == 0)
        {
            // Добавляем узел в список четных степеней
            node_list_push(even, current->coefficient, current->power);
        }
        else
        {
            // Добавляем узел в список нечетных степеней
            node_list_push(odd, current->coefficient, current->power);
        }
        current = current->next;
    }
}
