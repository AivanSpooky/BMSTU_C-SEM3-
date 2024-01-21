#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Узел (элемент списка) – единица хранения данных, несущая в себе ссылки на связанные с ней узлы.
Узел обычно состоит из двух частей
• информационная часть (данные);
• ссылочная часть (связь с другими узлами).

Связный список – это набор элементов, причем каждый из них является частью узла, который также содержит ссылку на следующий и/или предыдущий узел списка.
Связный список, как и массив, хранит набор элементов одного типа, но использует абсолютно другую стратегию выделения памяти:
память под каждый элемент выделяется отдельно и лишь тогда, когда это нужно.

Линейный односвязный список – структура данных, состоящая из узлов, каждый из которых ссылается на следующий узел списка.

Сравните массив и линейный односвязный список.
• Основное преимущество связных списков перед массивами заключается в возможности эффективного изменения расположения элементов.
• За эту гибкость приходиться жертвовать скоростью доступа к произвольному элементу списка, поскольку единственный способ получения
элемента состоит в отслеживании связей от начала списка.

ВО ВСЕХ ВОПРОСАХ ДОЛЖНО ПРИСУТСВОВАТЬ ОСВОБОЖДЕНИЕ ПАМЯТИ ИЗ ПОД ЛИН. ОДНОСВ. СПИСКА

Функции, которые изменяют список, часто возвращают указатель на голову списка, потому что это позволяет обновлять указатель на голову списка в вызывающем коде.
Если список изменяется внутри функции, исходный указатель на голову списка может стать недействительным или указывать на новую голову списка после изменений.
#endif

#ifdef OK // Функции
typedef struct node
{
    const char *name;
    int year;
    struct node *next;
} node_t;

node_t *node_create(const char *name, int year) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node) {
        new_node->name = name;
        new_node->year = year;
        new_node->next = NULL;
    }
    return new_node;
}

void node_free(node_t *node) {
    free(node);
}

// Добавление в начало без возврата указателя на голову 
void list_add_front_usual(node_t **head, node_t *pers)
{
    pers->next = *head;
    *head = pers;
}
// Функции, изменяющие список, должны возвращать указатель на новый первый элемент.
// Добавление в начало с возвратом новой головы 
node_t *list_add_front(node_t *head, node_t *pers)
{
    pers->next = head;
    return pers;
}
// Функция добавления элемента в конец
node_t *list_add_end(node_t *head, node_t *pers)
{
    node_t *cur = head;
    if (!head)
        return pers;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = pers;
    return head;
}

// Удаление по имени или по другому полю
// НЕЛЬЗЯ УДАЛЯТЬ ПО УСЛОВНОМУ ИНДЕКСУ ТАК КАК СМЫСЛ ПРЕДСТАВЛЕНИЯ КАК СПИСОК ТЕРЯЕТСЯ
node_t *del_by_name(node_t *head, const char *name)
{
    node_t *cur = head, *prev = NULL;
    while (cur != NULL)
    {
        if (strcmp(cur->name, name) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;
            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}

void add_age(node_t *head, void *age) {
    const int *a = age;
    head->year += *a;
}
// Обход списка
// f: указатель на функцию, которая применяется к каждому элементу списка
void list_apply(node_t *head, void (*f)(node_t *, void *), void *arg)
{
    while (head != NULL)
    {
        f(head, arg);
        head = head->next;
    }
}

// Удаление памяти из-под всего списка.
void list_free_all(node_t *head)
{
    node_t *next;
    while (head != NULL)
    {
        next = head->next;
        node_free(head);
        head = next;
    }
}
// После освобождения узла списка и перехода к новому узлу, происходит обращения к полю NULL, что невозможно
#endif




int main(void)
{
    node_t *list = node_create("first", 100);
    node_t *sec = node_create("second", 50);
    node_t *third = node_create("zero", 10);
    list = list_add_end(list, sec);
    list = list_add_front(list, third);
    node_t *cur = list;
    while (cur != NULL) {
        printf("%d ", cur->year);
        cur = cur->next;
    }
    printf("\n");

    int age = 100;
    list_apply(list, add_age, &age);
    cur = list;
    while (cur != NULL) {
        printf("%d ", cur->year);
        cur = cur->next;
    }
    printf("\n");
    list_free_all(list);

    return OK;
}