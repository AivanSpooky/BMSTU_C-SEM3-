#include "funcs.h"

int find_sum(const int *pb, const int *pe)
{
    const int *pc = pb;
    int sum = 0;
    while (pc < pe)
    {
        sum += *pc;
        pc++;
    }
    return sum;
}

int int_cmp(const void *l, const void *r)
{
    const int *pl = l;
    const int *pr = r;
    return *pl - *pr;
}

int double_cmp(const void *l, const void *r)
{
    const double *left = (const double *)l;
    const double *right = (const double *)r;
    
    if (*left < *right)
    {
        return -1;
    }
    else if (*left > *right)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int string_cmp(const void *l, const void *r)
{
    const char *left = (const char *)l;
    const char *right = (const char *)r;
    return strcmp(left, right);
}

int make_pre_key(const int *pb1, const int *pe1)
{
    if (!pb1 || !pe1)
        return INT_ERR_FLAG;
    // Найдем сумму всех элементов
    int sum = find_sum(pb1, pe1);
    const int *pc1 = pb1;
    size_t n = 0;
    // Пока не обошли все числа массива, кроме последнего
    while (pc1 + 1 < pe1)
    {
        // Если текущий элемент больше суммы элементов справа от него, то элемент - подходит 
        if (*pc1 > sum - *pc1)
        {
            n++;
        }
        // Уменьшаем сумму на текущий элемент
        // Чтобы следующие элементы уже сравнивать со своей суммой справа
        sum -= *pc1;
        pc1++;
    }
    return (int)n;
}

int key(const int *pb1, const int *pe1, int **pb2, int **pe2, size_t n)
{
    if (!pb1 || !pe1 || !pb2 || !pe2)
        return ERR_EMPTY;

    
    // Если нет подходящих чисел
    if (n == ZERO)
        return ERR_RANGE;

    const int *pc1 = pb1;
    pc1 = pb1;
    int *pc2 = *pb2;
    // Снова находим сумму всех элементов
    int sum = find_sum(pb1, pe1);
    // Пока не заполнили полностью новый массив
    while (pc2 < *pe2)
    {
        // Если элемент подходит (см. первый цикл)
        // То записываем его в новый массив
        // У величиваем значение указателя на тек. эл. нового массива
        if (*pc1 > sum - *pc1)
        {
            *pc2 = *pc1;
            pc2++;
        }
        // Уменьшаем сумму на текущий элемент
        // Чтобы следующие элементы уже сравнивать со своей суммой справа
        sum -= *pc1;
        pc1++; 
    }
    return OK;
}

void swap(void *l, void *r, size_t elem_size)
{
    char tmp[elem_size];
    memcpy(tmp, l, elem_size);
    memcpy(l, r, elem_size);
    memcpy(r, tmp, elem_size);
}

// Сортировка выбором (защита)
void mysort(void *ptr, size_t cnt, size_t size, uni_cmp cmp)
{
    if (!ptr || !cnt)
        return;
    char *pbeg = ptr;
    char *pend = pbeg + (cnt) * size;

    char *pi = pbeg;
    while (pi < pend)
    {
        char *pmin = pi;
        char *pj = pi;
        while (pj < pend)
        {
            if (cmp(pj, pmin) <= 0)
            {
                pmin = pj;
            }
            pj += size;
        }
        swap(pmin, pi, size);
        pi += size;
    }
}
// // Сортировка пузырьком с флагом туда и обратно
// void mysort(void *ptr, size_t cnt, size_t size, uni_cmp cmp)
// {
//     if (!ptr || !cnt)
//         return;
//     char *pbeg = ptr;
//     char *pend = pbeg + (cnt - 1) * size;
//     size_t swapped = 1;

//     while (swapped)
//     {
//         swapped = 0;
//         for (char *pcur = pbeg; pcur < pend; pcur += size)
//             if (cmp(pcur, pcur + size) > 0)
//             {
//                 swap(pcur, pcur + size, size);
//                 swapped = 1;
//             } 

//         if (!swapped)
//             break;

//         swapped = 0;
//         pend -= size;

//         for (char *pcur = pend; pcur > pbeg; pcur -= size)
//         {
//             if (cmp(pcur, pcur - size) < 0)
//             {
//                 swap(pcur - size, pcur, size);
//                 swapped = 1;
//             } 
//         }  

//         pbeg += size;
//     }
//     // for (char *ptop = pend; ptop > pbeg + size; ptop -= size)
// }
