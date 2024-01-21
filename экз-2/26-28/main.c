#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Происхождение термина «куча».
Согласно Дональду Кнуту, «Several authors began about 1975 to call the pool of available memory a "heap."».

Для хранения данных используется «куча».
Создать переменную в «куче» нельзя, но можно выделить память под нее.
“+”
Все «минусы» локальных переменных.
“-”
Ручное управление временем жизни.

Свойства области памяти, которая выделяется динамически
• malloc выделяет по крайней мере указанное количество байт (меньше нельзя, больше можно).
• Указатель, возвращенный malloc, указывает на выделенную область (т.е. область, в которую программа может писать и из которой может читать данные).
• Ни один другой вызов malloc не может выделить эту область или ее часть, если только она не была освобождена с помощью free.
Как организована куча?
• Зависит от аллокатора. 

Алгоритм работы функции malloc.
Выделение области памяти (malloc)
i. Просмотреть список занятых/свободных областей памяти в поисках свободной области подходящего размера.
ii. Если область имеет точно такой размер, как запрашивается, пометить найденную область как занятую и вернуть указатель на начало области памяти.
iii. Если область имеет больший размер, разделить ее на части, одна из которых будет занята (выделена), а другая останется в свободной.
iv. Если область не найдена, вернуть нулевой указатель.

Какие сведения об области нам нужны?
• Размер.
• Состояния (выделена/свободна).
• Где находится следующая область?

• Алгоритм работы функции free
Освобождение области памяти (free)
v. Просмотреть список занятых/свободных областей памяти в поисках указанной области.
vi. Пометить найденную область как свободную.
vii. Если освобожденная область вплотную граничит со свободной областью с какой-либо из двух сторон, то объединить их в единую область большего размера.

Какие гарантии относительно выделенного блока памяти даются программисту?
• Ей размер такой же или больше запрашиваемого, другие вызовы malloc не могут ещё раз выделить эту же область памяти
Что значит "освободить блок памяти" с точки зрения функции free?
• Пометить освобождаемый блок как свободный. 

Что такое фрагментация памяти?
• Это когда большая часть вашей памяти выделяется в большом количестве несмежных блоков или блоков,
оставляя хороший процент вашей общей памяти нераспределенной, но непригодной для большинства типичных сценариев.

Выравнивание блока памяти, выделенного динамически.
• Для хранения произвольных объектов блок должен быть правильно выровнен.
В каждой системе есть самый «требовательный» тип данных – если элемент этого типа можно поместить по некоторому адресу,
то любые другие элементы тоже можно поместить туда.
#endif

#ifdef OK // Функции

struct block_t
{
    size_t size;
    int free;
    struct block_t *next; 
};

#define MY_HEAP_SIZE 1000000
// пространство под "кучу"
static char my_heap[MY_HEAP_SIZE];

// список свободных/занятых областей
static struct block_t *free_list = (struct block_t*) my_heap;

// начальная инициализация списка свободных/занятых областей
static void initialize(void)
{
    free_list->size = sizeof(my_heap) - sizeof(struct block_t);
    free_list->free = 1;
    free_list->next = NULL;
}

static void split_block(struct block_t *block, size_t size)
{
    size_t rest = block->size - size;
    
    if (rest > sizeof(struct block_t))
    {
        struct block_t *new = (void*)((char*)block + size + sizeof(struct block_t));
    
        new->size = block->size - size - sizeof(struct block_t);
        new->free = 1;
        new->next = block->next;
    
        block->size = size;
        block->free = 0;
        block->next = new;
    }
    else
        block->free = 0;
}

void *my_malloc(size_t size)
{
    struct block_t *cur;
    void *result;

    if (!free_list->size)
        initialize();
    
    cur = free_list;
    while (cur && (cur->free == 0 ||
                       cur->size < size))
        cur = cur->next;

    if (!cur)
    {
        result = NULL;
        printf("Out of memory\n");
    } 
    else if (cur->size == size)
    {
        cur->free = 0;
        result = (void*) (++cur);
    }
    else
    {
        split_block(cur, size);
        result = (void*) (++cur);
    } 
    return result;
}

void my_free(void *ptr)
{
    if (my_heap <= (char*) ptr && (char*) ptr < my_heap + sizeof(my_heap))
    {
        struct block_t *cur = ptr;
        
        --cur;
        cur->free = 1;
        
        merge_blocks();
    }
    else
        printf("Wrong pointer\n");
}

static void merge_blocks(void)
{
    struct block_t *cur = free_list;
    
    while (cur && cur->next != NULL)
    {
        if (cur->free && cur->next->free)
        {
            cur->size += cur->next->size + sizeof(struct block_t);
            cur->next = cur->next->next;
        }
        else
            cur = cur->next;
    }
}


#if OK == ERR
 // По Кернигану, Ритчи
typedef long align_t;

union block_t
{
    struct
    {
        size_t size;
        int free;
        union block_t *next; 
    } block;
 
    align_t x;
};


// Запрашиваемый размер области обычно округляется до размера кратного размеру заголовка.
n_blocks = (size + sizeof(union block_t) – 1) /
                           sizeof(union block_t) + 1; 

alloc_size = n_blocks*sizeof(sizeof(union block_t));
#endif

#endif




int main(void)
{
    
    return OK;
}