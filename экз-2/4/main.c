#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
С помощью указателей на функции в языке Си реализуются
• функции обратного вызова (англ., callback);
• таблицы переходов (англ., jump table);
• динамическое связывание (англ., binding).
Callback (функция обратного вызова) - передача исполняемого кода в качестве одного из параметров другого кода.
Функция обратного вызова — это "действие", передаваемое в функцию в качестве аргумента, которое обычно используется
• для обработки данных внутри функции (map);
• для того, чтобы «связываться» с тем, кто вызвал функции, при наступлении какого-то события.

Особенности использования указателей на функцию
Согласно C99 6.7.5.3 #8, выражение из имени функции неявно преобразуется в указатель на функцию.
Операция "&" для функции возвращает указатель на функцию, но из-за 6.7.5.3 #8 это лишняя операция.
Операция "*" для указателя на функцию возвращает саму функцию, которая неявно преобразуется в указатель на функцию.
Указатели на функции можно сравнивать. Указатель на функцию может быть типом возвращаемого значения функции.

Указатель на функцию и адресная арифметика - неприменима
Указателя на функцию и указатель на void.
Согласно C99 6.3.2.3 #1 и C99 6.3.2.3 #8, указатель на функцию не может быть преобразован к указателю на void и наоборот.
ОДНАКО БЕЗ КЛЮЧА pedantic преобразование ВОЗМОЖНО
#endif

#ifdef OK // Функции
// Функция сравнения для сортировки целых чисел по возрастанию
int int_cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

typedef int (*action_ptr)(int);

// Функция возведения в квадарат
int square(int x) {
    return x * x;
}

// Функция, которая применяет операцию ко всем элементам массива
void array_operation_1(int *a, size_t n, int (*action)(int)) {
    for (size_t i = 0; i < n; i++) {
        a[i] = action(a[i]);
    }
}

void array_operation_2(int *a, size_t n, action_ptr action) {
    for (size_t i = 0; i < n; i++) {
        a[i] = action(a[i]);
    }
}

void print_int_arr(int *arr, size_t cnt) {
    printf("Array:\n");
    for (size_t i = 0; i < cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int read_from_text_file(char *, int *a, size_t cnt) {
    return OK;
}

int read_from_bin_file(char *, int *a, size_t cnt) {
    return OK;
}

#endif


int main(void)
{
    // Пример использования qsort
    {
        int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        size_t n = sizeof(arr) / sizeof(arr[0]);

        qsort(arr, n, sizeof(int), int_cmp);

        printf("QSORT action:\n");
        print_int_arr(arr, n);
        printf("\n");
    }
    
    // Пример использования функций с параметром в виде указателя на функцию
    {
        int a[] = {1, 2, 3, 4, 5};
        size_t cnt = 5;
        print_int_arr(a, cnt);
        // Без использования typedef
        array_operation_1(a, cnt, square);
        print_int_arr(a, cnt);
        // С использованием typedef
        array_operation_2(a, cnt, square);
        print_int_arr(a, cnt);
    }
    
    // Пример на создание, инициализацию и использование указателя на функцию (имеет смысл вызывать через указатель на функцию)
    {
        int (*func_ptr)(char *, int *, size_t);
        size_t mode = 0;
        char *filename = "in.txt";
        int *a;
        size_t n;
        if (mode == 0) func_ptr = read_from_text_file;
        else func_ptr = read_from_bin_file;

        int rc = func_ptr(filename, a, n);
    }
    return OK;
}