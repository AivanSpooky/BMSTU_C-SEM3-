#include <stdio.h>
#include <string.h>
#define OK 0
#define ERR 1

enum var_type {
    INT,
    STR,
    DOUBLE,
    OTHER
};

//"Описание функций memcpy memmove memcmp memset"
#if OK == ERR
Все функции импортируются из <string.h>
memcpy: 
    Копирует последовательность байтов из одной области памяти в другую.
    Прототип функции: void *memcpy(void *destination, const void *source, size_t num).
memmove:
    Копирует последовательность байтов из одной области памяти в другую, даже если области перекрываются.
    Прототип функции: void *memmove(void *destination, const void *source, size_t num).
memcmp:
    Сравнивает две последовательности байтов.
    Прототип функции: int memcmp(const void *ptr1, const void *ptr2, size_t num).
memset:
    Заполняет последовательность байтов определенным значением.
    Прототип функции: void *memset(void *ptr, int value, size_t num).
#endif

int print_var(void *ptr, enum var_type type)
{
    switch (type) {
        case INT:
            printf("INT %d\n", *(int *)ptr);
            break;
        case STR:
            printf("CHAR %s\n", (char *)ptr);
            break;
        case DOUBLE:
            printf("DOUBLE %lf\n", *(double *)ptr);
            break;
        default:
            printf("ERROR\n");
            return ERR;
    }
    return OK;
}

void sayHello() {
    printf("Hello, World!\n");
}

int main(void)
{
    // "Использование void * в функциях"
    {
        int a = 1;
        char *str = "string-type";
        double b = 1.9;
        // Вызов функции на разных типах данных
        print_var(&a, INT);
        print_var(str, STR);
        print_var(&b, DOUBLE);
        print_var(&a, OTHER);
    }

    //"Использование memmove для передвижения области памяти влево при перекрытии"
    {
        char data[] = "Hello, World!";
        void *src = data + 6;  // Указатель на область, которую мы хотим переместить
        void *dest = data + 1; // Указатель на место, куда мы хотим переместить данные
        size_t numBytes = 13;   // Количество байтов для перемещения (в данном случае 13 - максимум)
        memmove(dest, src, numBytes);

        printf("Результат: %s\n", data); // Выведет "HWorld! World!"
    }

    // Приведение указателя на void к указателю на функцию и вызов функции
    {
        // ВАЖНО! ПРЕОБРАЗОВАНИЕ ВОЗМОЖНО ТОЛЬКО БЕЗ КЛЮЧА pedantic (см. вопрос 4)
        // Объявление указателя на функцию
        void (*funcPtr)();

        // Приведение указателя на функцию к указателю на void
        void *voidPtr = (void *)sayHello;

        // Приведение указателя на void к указателю на функцию и вызов функции
        funcPtr = (void (*)())voidPtr;
        funcPtr();
    }
    
    return OK;
}