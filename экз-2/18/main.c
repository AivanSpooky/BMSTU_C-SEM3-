#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Массив – последовательность элементов одного типа, расположенных в памяти друг за другом.
Преимущества и недостатки массива объясняются стратегией выделения памяти: память под все элементы выделяется в одном блоке.
«+»
Простота использования.
Константное время доступа к любому элементу.
Не тратят лишние ресурсы.
Хорошо сочетаются с двоичным поиском.
“–”
Хранение меняющегося набора значений.

Особенности использования.
• Удвоение размера массива при каждом вызове realloc сохраняет средние «ожидаемые» затраты на копирование элемента.
• Поскольку адрес массива может измениться, программа должна обращаться к элементам массива по индексам.
• Благодаря маленькому начальному размеру массива, программа сразу же «проверяет» код, реализующий выделение памяти.
Почему при добавлении нового элемента память необходимо выделять блоками, а не под один элемент?
• Для уменьшения потерь при распределении памяти изменение размера должно происходить относительно крупными блоками.
#endif

#ifdef OK // Функции
typedef struct {
    int *data;
    size_t capacity;
    size_t size;
} DynamicArray;

int init_dynamic_array(DynamicArray *arr, size_t initial_capacity) {
    arr->data = malloc(initial_capacity * sizeof(int));
    if (!arr->data)
        return ERR;
    arr->capacity = initial_capacity;
    arr->size = 0;
    return OK;
}

int append_to_dynamic_array(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        int *tmp = realloc(arr->data, arr->capacity * sizeof(int));
        if (!tmp)
            return ERR;
        arr->data = tmp;
    }
    arr->data[arr->size] = value;
    arr->size++;
    return OK;
}

void free_dynamic_array(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->capacity = 0;
    arr->size = 0;
}

int remove_at_dynamic_array(DynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        return ERR;
    }
    memmove(arr->data + index, arr->data + index + 1, (arr->size - index - 1) * sizeof(int));
    arr->size--;
    return OK;
}
#endif


int main(void)
{
    return OK;
}