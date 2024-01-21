#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Два способа создания массива
int *arr = malloc(10 * sizeof(int));
int *arr = calloc(10, sizeof(int));
Если выделить char *str с помощью calloс, то str будет заполнена символами "\0"

Типичные ошибки при работе с динамической памятью
• Неверный расчёт количества выделяемой памяти
• Отсутствие проверки успешности выделения памяти
• Утечки памяти
(возникают в основном из-за неосвобождения памяти из под данных, выделенных malloc, calloc.)
• Логические ошибки
a. Дикий указатель: использование непроинициализированного указателя.
int *ptr;
*ptr = 5; // Использование непроинициализированного указателя
b. Висящий указатель: использование указателя сразу после освобождения памяти.
int *ptr = malloc(sizeof(int));
free(ptr);
int value = *ptr; // Использование указателя сразу после освобождения памяти
c. Изменение указателя, который вернула функция выделения памяти.
int *ptr = malloc(5 * sizeof(int));
ptr = malloc(10 * sizeof(int)); // Переопределение указателя без освобождения предыдущей памяти
d. Двойное освобождение памяти.
int *ptr = malloc(sizeof(int));
free(ptr);
free(ptr); // Попытка освободить уже освобожденную память
e. Освобождение невыделенной или нединамической памяти.
int x = 5;
free(&x); // Попытка освободить нединамическую память
f. Выход за границы динамического массива.
int *ptr = malloc(5 * sizeof(int));
*(ptr + 10) = 20; // Неправильное использование указателя, запись за пределы выделенной памяти

Подходы к обработке ситуации отсутствия свободной памяти при выделении
• Возвращение ошибки (Подход, который используем мы)
• Ошибка сегментации (Обратная сторона - проблемы с безопасностью)
• Аварийное завершение (Идея принадлежит Кёрнигану и Ритчи (xmalloc))
• Восстановление (попробовать высвободить память) (xmalloc из git)

#endif

#ifdef OK // Функции
void print_int_arr(int *arr, size_t cnt) {
    printf("Array:\n");
    for (size_t i = 0; i < cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *create_rising_nums_1(size_t n) {
    size_t cur = 1;
    int *arr = malloc(n * sizeof(int));
    if (arr != NULL) {
        while (cur <= n) {
            arr[cur - 1] = cur;
            cur++;
        }
    }
    return arr;
}

void create_rising_nums_2(int **arr, size_t n) {
    size_t cur = 1;
    *arr = malloc(n * sizeof(int));
    if (*arr != NULL) {
        while (cur <= n) {
            (*arr)[cur - 1] = cur;
            cur++;
        }
    }
}
#endif


int main(void)
{
    // Примеры на возвращения массива из функций
    // Способ 1: Возвращаемое значение
    {
        int *nums = NULL;
        size_t count = 10;
        nums = create_rising_nums_1(count);
        print_int_arr(nums, count);
        free(nums); // Освобождение памяти
    }
    
    // Способ 2: Через параметры функции
    {
        int *nums = NULL;
        size_t count = 10;
        create_rising_nums_2(&nums, count);
        print_int_arr(nums, count);
        free(nums); // Освобождение памяти
    }
    return OK;
}