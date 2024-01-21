#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Структуры с полями указателями и особенности их использования
В Си определена операция присваивания для структурных переменных одного типа.
Эта операция фактически эквивалента копированию области памяти, занимаемой одной переменной, в область памяти, которую занимает другая.
При этом реализуется стратегия так называемого «поверхностного копирования», при котором копируется содержимое структурной переменной,
но не копируется то, на что могут ссылать поля структуры.

Структуры с полями указателями и особенности их использования
Стратегия так называемого «глубокого копирования» подразумевает создание копий объектов, на которые ссылаются поля структуры.

«Рекурсивное» освобождение памяти для структур с динамическими полями.
Сначалаосвобождается память из под объектов структуры, а потом из самой структуры

#endif

#ifdef OK // Функции

typedef struct {
    char *name;
    int age;
} Person;

void print_p(Person *p) {
    printf("Person:\n\tName: %s\n\tAge: %d\n", p->name, p->age);
}

Person *deep_copy_person(const Person *src) {
    Person *new_person = malloc(sizeof(Person));
    if (new_person) {
        new_person->age = src->age;
        char *buf = strdup(src->name); // глубокое копирование строки
        if (!buf) {
            free(new_person);
            return NULL;
        }
        new_person->name = buf;
    }
    return new_person;
}

void free_person(Person *person) {
    if (person) {
        free(person->name); // освобождаем память под строкой
        free(person); // освобождаем память под самой структурой
    }
}

#endif


int main(void)
{
    // Поверхностное копирование (операция присваивания)
    Person first;
    first.name = "Vanya";
    first.age = 19;
    Person second;
    second.name = "Darova";
    second.age = 20;
    print_p(&first);
    first = second;
    print_p(&first);

    // Глубокое копирование (побитовое)
    Person *first_1 = malloc(sizeof(Person));
    first_1->name = strdup("Vanya");
    first_1->age = 19;
    Person *first_2 = malloc(sizeof(Person));
    first_2->name = strdup("Darova");
    first_2->age = 20;

    print_p(first_1);
    first_1 = deep_copy_person(first_2);
    print_p(first_1);
    
    free_person(first_2);
    free_person(first_1);

    return OK;
}