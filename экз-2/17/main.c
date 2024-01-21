#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
7. Структуры переменного размера. Приведите примеры.
TLV (Type (или Tag) Length Value) - схема кодирования произвольных данных в некоторых телекоммуникационных протоколах.
Type – описание назначения данных.
Length – размер данных (обычно в байтах).
Value – данные.
Первые два поля имеют фиксированный размер.

Что такое «flexible array member»? Какие особенности использование есть у этих полей? Для чего они нужны? Приведите примеры
struct {int n, double d[]};
Подобное поле должно быть последним. Нельзя создать массив структур с таким полем.
Структура с таким полем не может использоваться как член в «середине» другой структуры.
Операция sizeof не учитывает размер этого поля (возможно, за исключением выравнивания).
Если в этом массиве нет элементов, то обращение к его элементам – неопределённое поведение.

struct s* create_s(int n, const double *d)
{
    assert(n >= 0);
    struct s *elem = malloc(sizeof(struct s) + n * sizeof(double));
    if (elem)
    {
        elem->n = n;
        memmove(elem->d, d, n * sizeof(double));
    }
    return elem;
}

Flexible array member до C99.
struct s
{
    int n;
    double d[1];
};


struct s* create_s(int n, const double *d)
{
    assert(n >= 0);
    struct s *elem = calloc(sizeof(struct s) +
                    (n > 1 ? (n - 1) * sizeof(double) : 0), 1);
    if (elem)
    {
        elem->n = n;
        memmove(elem->d, d, n * sizeof(double));
    }


    return elem;
}

Flexible array member vs поле-указатель.
Экономия памяти. Локальность данных (data locality). Атомарность выделения памяти. Не требует «глубокого» копирования и освобождения.
#endif

#ifdef OK // Функции

#endif


int main(void)
{
    return OK;
}